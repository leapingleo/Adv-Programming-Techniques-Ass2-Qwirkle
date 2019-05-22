#include "Game.h"

Game::Game(){
}

Game::~Game(){
  delete player1;
  delete player2;
  delete tileBag;
}

//return one of the end game condition, i.e no more tiles in the bag,
//one player got no more tiles
bool Game::isGameOver() {
  return tileBag->size() == 0 && (player1->getTilesOnHand()->size() == 0 ||
         player2->getTilesOnHand()->size() == 0);
}

//set up a new game with players, tile bags, and dive into play
void Game::newGame(string name1, string name2){
  board = new Board(boardRows, boardCols);
//  board = new Board(boardRows, boardCols);
  player1 = new Player(name1);
  player2 = new Player(name2);
  currentPlayerName = player1->getName();
  tileBag = new LinkedList();
  gameSetup();
  play();
}

//A.I trigger to call AIMove in play()
void Game::turnOnAI(){
  playingWithAI = true;
}

/* The AI stores all possible moves, and choose one and make a move
   it also can replace a tile where there's no possible moves */
void Game::AIMove(vector<vector<Tile*> > boardTiles, Player* player){
  std::vector<std::string> possibleSpots;
  Node* current = player->getTilesOnHand()->getHead();
  bool placed = false;
  bool canReplaceATile = true;

  if (!board->isFirstTileOnBoard()) {
    Tile* firstTile = player->getTilesOnHand()->getHead()->getTile();
    placeTile(firstTile, 4,3,player);
  }

  for (int i = 0; i < boardTiles.size(); i++) {
    for (int j = 0; j < boardTiles[i].size(); j++) {
      if (boardTiles[i][j] != nullptr) {
        if (j - 1 >= 0 && boardTiles[i][j - 1] == nullptr) {
          string spotString = letterForRows(i) + std::to_string(j - 1);
          possibleSpots.push_back(spotString);
        }
        if (j + 1 < board->getCols() && boardTiles[i][j + 1] == nullptr) {
          string spotString = letterForRows(i) + std::to_string(j + 1);
          possibleSpots.push_back(spotString);
        }
        if (i - 1 >= 0 && boardTiles[i - 1][j] == nullptr) {
          string spotString = letterForRows(i - 1) + std::to_string(j);
          possibleSpots.push_back(spotString);
        }
        if (i + 1 < board->getRows() && boardTiles[i + 1][j] == nullptr) {
          string spotString = letterForRows(i + 1)  + std::to_string(j);
          possibleSpots.push_back(spotString);
        }
      }
    }
  }

  //  try each tile on the hand at each possible spot...
  for (int i = 0; i < possibleSpots.size(); i++) {
    int atRow = letterToInt(possibleSpots[i].substr(0, 1));
    int atCol = std::stoi(possibleSpots[i].substr(1, 2));

    while (!placed && current != nullptr) {
      Tile* tile = current->getTile();

      if (board->isWithinBound(atRow, atCol) && canPlace(boardTiles, atRow, atCol, tile)
        && !board->isTileAlreadyAt(atRow, atCol)) {
        placeTile(tile, atRow, atCol, player);
        calculateScores(board->getTilesOnBoard(), atRow, atCol);
        placed = true;
      }
      current = current->next;
    }
    current = player->getTilesOnHand()->getHead();
   }

   //if a tile cannot be placed while there's more tiles in the bag, then replace
   if (!placed && tileBag->size() > 0) {
     string tileToReplace = player->getTilesOnHand()->getHead()->getTile()->toString();
     replaceTile(tileToReplace, player);
   } else
     canReplaceATile = false;

   //when tiles cannot be placed nor replaced, end the game
   if (!placed && !canReplaceATile) {
     noMorePossibleMoves = true;
     cout << "There's no more possible moves. The game ends" << endl;
   }
}

void Game::play(){
    while (!isGameOver() && !exitDuringGame && !noMorePossibleMoves) {
      if (currentPlayerName == player1->getName()) {
        displayInfo(player1);
        AIMove(board->getTilesOnBoard(), player1);
      //  makeAMove(player1);
        givePlayerScore(player1);
        currentPlayerName = player2->getName();
     } else {
       displayInfo(player2);
       if (playingWithAI)
         AIMove(board->getTilesOnBoard(), player2);
       else
         makeAMove(player2);
       givePlayerScore(player2);
       currentPlayerName = player1->getName();
     }
  //  std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
  if (!exitDuringGame)
    showResult();
}

//set up the game, set up a randomized tile bag and assign 6 tiles to each player
void Game::gameSetup(){
  //generate 2 randomized tile set
  generateRandomizedTileSet();
  generateRandomizedTileSet();
  //generateRandomizedTileSet();

   //same color diferent shape initially
  for (int i = 1; i < 3; i++)
    for (int j = 0; j < 6; j++)
      tileBag->add(new Tile(converToColour(i), j+1));

   //same shape different colour
  for (int i = 0; i < 6; i++)
    for (int j = 1; j < 7; j++)
      tileBag->add(new Tile(converToColour(j), i+1));

  //Player 1 get 6 tiles
  for (int i = 0; i < 6; i++){
    player1->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }

  //Player 2 get 6 tiles
  for (int i = 0; i < 6; i++){
    player2->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
}

//read and validate a command, and turn it into an action
void Game::makeAMove(Player* player){
  std::string command = getInput("> ");
  transform(command.begin(),command.end(),command.begin(),::toupper);
  //get row and col from player's command

  //check if the command matches the format
  if (command.substr(0, 6) == "PLACE " && command.length() > 13
        && command.substr(8, 1) == " " && command.substr(11,1) == " "){
    std::string tileName = command.substr(6,2);
    int placeAtRow = letterToInt(command.substr(12,1));
    int placeAtCol = std::stoi(command.substr(13,2));

    //if player has tile to place
    if (player->getTilesOnHand()->has(tileName)) {
      Tile* tileToPlace = player->findTile(tileName);
      vector<vector<Tile*> > currentTilesOnBoard = board->getTilesOnBoard();

      //check tile is within the board boundary and no tile already at the spot
      if (board->isWithinBound(placeAtRow, placeAtCol) &&
          !board->isTileAlreadyAt(placeAtRow, placeAtCol)){
        //check tile placement against the rules
        if (canPlace(currentTilesOnBoard, placeAtRow, placeAtCol, tileToPlace)) {
          placeTile(tileToPlace, placeAtRow, placeAtCol, player);
          calculateScores(currentTilesOnBoard,placeAtRow, placeAtCol);
        } else {
          printError("CANT PLACE HERE! It does not match the rules! Try Again!");
          makeAMove(player);
        }
      } else {
        printError("Either the spot is already taken or the spot is beyond the game board boundary. Try Again.");
        makeAMove(player);
      }
    } else {
      printError("YOU DON'T HAVE THAT TILE, DO YOU???");
      makeAMove(player);
    }
  }
  else if (command.substr(0, 8) == "REPLACE "){
    std::string tileToReplace = command.substr(8,2);
    if (player->getTilesOnHand()->has(tileToReplace)) {
      replaceTile(tileToReplace, player);
    } else {
      printError("Cannot replace such tile for you. WHY? Because you do not have it?");
      makeAMove(player);
    }
  }
  else if (command.substr(0, 5) == "SAVE "){
    filename = command.substr(5);
    filename += ".txt";
    saveGame(player1->getTilesOnHand(), player2->getTilesOnHand(),
          player1->getName(), player2->getName(),
          player1->getScore(), player2->getScore(), currentPlayerName);
    makeAMove(player);
  }
  else if (cin.eof()){
    exitDuringGame = true;
  }
  else {
    printError("Invalid Input");
    makeAMove(player);
  }
}

/*
  tiles generated through the number representation. e.g "1" represents ORANGE
  and CIRCLE.
  each distinct shape and color is both represented by an integer
  1. generate 36 different randomized "integer" strings(color + shape),
     and put them into a string vector
  2. futhur randomization(shuffle) for the string vector
  3. retrieve and parse each string element to integer color and shape,
     and add each to the tile bag
  **The usual nestted for-loop generates a randomized but predictable pattern,
    i.e. each outter loop produces same integer with inner loop, e.g 12, 13, 14, 16, 15, 11
*/
void Game::generateRandomizedTileSet(){
  //initial randomization for both colour and shape
  std::vector<int> colourSet = randomSet(1,6);
  std::vector<int> shapeSet = randomSet(1,6);
  std::vector<std::string> randomTileStringSet;

  for (int i = 0; i < colourSet.size(); i++){
    //make sure seed is different at each i
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
    //further randomization for each column loop
    shapeSet = randomSet(1,6);

    for (int j = 0; j < shapeSet.size(); j++) {
      std::string tileString = std::to_string(colourSet[i]) + std::to_string(shapeSet[j]);
      randomTileStringSet.push_back(tileString);
    }
  }

  //using seed based on the current time
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(randomTileStringSet.begin(), randomTileStringSet.end(),
          std::default_random_engine(seed));

  //retrieve each string element and parse to int, create a tile and add to tile bag
  for (int i = 0; i < randomTileStringSet.size(); i++) {
    char colour = std::stoi(randomTileStringSet[i].substr(0,1));
    int shape = std::stoi(randomTileStringSet[i].substr(1,1));
    tileBag->add(new Tile(converToColour(colour), shape));
  }
}

/* check if a tile can be placed based on the rules, it calls isMatchingTilesAround() for
   further validation */
bool Game::canPlace(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile) {
  bool validMove = false;

  //first tile can place anywhere
  if (!board->isFirstTileOnBoard()) {
    validMove = true;
    scoreToGive = 1;
  }
  else{
    if (isMatchingTilesAround(boardTiles, atRow, atCol, tile))
      validMove = true;
  }

  return validMove;
}
/* check if a to-be-placed tile matching horizontal and vertical tiles around it
   also checks if the tiles on its left and tiles on its right are all unique
   and same for tiles on its above and the tiles below it  */
bool Game::isMatchingTilesAround(vector<vector<Tile*> > boardTiles,
                        int atRow, int atCol, Tile* tile) {
    bool valid = false;
    bool endCheck = false;
    int towardsLeft = atCol - 1;
    int towardsRight = atCol + 1;
    int towardsUp = atRow - 1;
    int towardsDown = atRow + 1;
    std::vector<Tile*> horizontalTiles;
    std::vector<Tile*> verticalTiles;
    std::vector<Tile*> leftTiles;
    std::vector<Tile*> rightTiles;
    std::vector<Tile*> upTiles;
    std::vector<Tile*> downTiles;
    bool horizontalCheckPassed = false;
    bool verticalCheckPassed = false;

    //adding tiles to left, right, up and down tile vectors
    while (towardsLeft >= 0 &&
      boardTiles[atRow][towardsLeft] != nullptr) {
        leftTiles.push_back(boardTiles[atRow][towardsLeft]);
        horizontalTiles.push_back(boardTiles[atRow][towardsLeft]);
        towardsLeft--;
    }
    while (boardTiles[atRow][towardsRight] != nullptr && towardsRight < board->getCols()) {
        rightTiles.push_back(boardTiles[atRow][towardsRight]);
        horizontalTiles.push_back(boardTiles[atRow][towardsRight]);
        towardsRight++;
    }
    while (towardsUp >= 0 &&
         boardTiles[towardsUp][atCol] != nullptr) {
      upTiles.push_back(boardTiles[towardsUp][atCol]);
      verticalTiles.push_back(boardTiles[towardsUp][atCol]);
      towardsUp -= 1;
    }
    while (towardsDown < board->getRows() &&
         boardTiles[towardsDown][atCol] != nullptr) {
      downTiles.push_back(boardTiles[towardsDown][atCol]);
      verticalTiles.push_back(boardTiles[towardsDown][atCol]);
      towardsDown += 1;
    }

    //check if a tile matching the horizontal rule, i.e same colour & diff shape
    for (int i = 0; i < horizontalTiles.size(); i++){
      if (horizontalTiles[i]->getColour() == tile->getColour() &&
          horizontalTiles[i]->getShape() != tile->getShape() && !endCheck) {
             horizontalCheckPassed = true;
           }
      else {
        horizontalCheckPassed = false;
        endCheck = true;
      }
    }

    //check if a tile matching the vertical rule, i.e same shape & diff colour
    for (int i = 0; i < verticalTiles.size(); i++){
      if (verticalTiles[i]->getColour() != tile->getColour() &&
          verticalTiles[i]->getShape() == tile->getShape() && !endCheck) {
             verticalCheckPassed = true;
           }
      else{
        verticalCheckPassed = false;
        endCheck = true;
      }
    }

    //check tiles on its left and on its right are unique
    for (int i = 0; i < leftTiles.size(); i++) {
      for (int j = 0; j < rightTiles.size(); j++) {
        if (leftTiles[i]->toString() == rightTiles[j]->toString() && !endCheck) {
          endCheck = true;
          horizontalCheckPassed = false;
        }
      }
    }

    //check tiles at its above and tiles below it are unique
    for (int i = 0; i < upTiles.size(); i++){
      for (int j = 0; j < downTiles.size(); j++) {
        if (upTiles[i]->toString() == downTiles[j]->toString() && !endCheck){
          endCheck = true;
          verticalCheckPassed = false;
        }
      }
    }

    //if no "above" and "below" tiles around it
    if (verticalTiles.empty() && horizontalCheckPassed){
      valid = true;
    }
    //if no left and right tiles around it
    if (horizontalTiles.empty() && verticalCheckPassed) {
      valid = true;
    }
    //if both horizontal and vertical tiles around it
    if (!horizontalTiles.empty() && !horizontalTiles.empty()) {
      if (horizontalCheckPassed && verticalCheckPassed)
        valid = true;
    }

    return valid;
}

/* counting the number of tiles around the spot the player placed a tile, and
   add up scores */
void Game::calculateScores(vector<vector<Tile*> > boardTiles,int atRow, int atCol) {
   if (atCol >= 0 && boardTiles[atRow][atCol - 1] != nullptr)
     scoreToGive += countColTiles(boardTiles, atRow, atCol - 1, -1);
   if (atCol < board->getCols() && boardTiles[atRow][atCol + 1] != nullptr)
     scoreToGive += countColTiles(boardTiles, atRow, atCol + 1, 1);
   if (atRow - 1 >= 0 && boardTiles[atRow - 1][atCol] != nullptr)
     scoreToGive += countRowTiles(boardTiles, atRow - 1, atCol, -1);
   if (atRow + 1 < board->getRows() - 1 && boardTiles[atRow + 1][atCol] != nullptr)
     scoreToGive += countRowTiles(boardTiles, atRow + 1, atCol, +1);
}

//count the number of tiles horizontally at a spot
int Game::countColTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction) {
  int tileCount = 0;

  while (atCol >= 0 && atCol < board->getCols() &&
      boardTiles[atRow][atCol] != nullptr) {
    tileCount++;
    atCol += direction;
  }

  //if there's 5 already plus the tile placed makes a QWIRKLE
  if (tileCount == 5)
    isQwirkle = true;
  return tileCount;
}

//count the number of tiles vertically at a spot
int Game::countRowTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction) {
  int tileCount = 0;
  while (atRow >= 0 && atRow < board->getRows() &&
            boardTiles[atRow][atCol] != nullptr) {
    tileCount++;
    atRow += direction;
  }

  if (tileCount == 5)
    isQwirkle = true;
  return tileCount;
}

//replace a tile for player
void Game::replaceTile(std::string tileName, Player* player){
  if (tileBag->size() > 0) {
    tileBag->add(player->findTile(tileName));
    player->removeTile(tileName);
    player->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
}

//place a tile
void Game::placeTile(Tile* tile, int atRow, int atCol, Player* player){
  board->store(tile, atRow, atCol);
  player->removeTile(tile->toString());

  //draw a new tile
  if (tileBag->size() > 0) {
    player->addTiles(tileBag->getNext()->getTile());
    //delete the withdrawn tile, which is always the head tile/node
    tileBag->deleteFront();
  }
  cout << std::endl;
}

//assginment scores to the player
void Game::givePlayerScore(Player* player) {
  if (isQwirkle) {
    scoreToGive += 6;
    cout << "QWIRKLE!!!" << endl;
  }
  player->addScore(scoreToGive);
  isQwirkle = false;
  scoreToGive = 0;
}

//display player scores and print the board
void Game::displayInfo(Player* player){
  cout << player->getName() << ", it's your turn\n" << endl;
  cout << "Score for " << player1->getName() << ": " << player1->getScore() << endl;
  cout << "Score for " << player2->getName() << ": " << player2->getScore() << endl;
  cout << endl;
  board->printBoard();
  cout << endl;
  player->showTilesOnHand();
}

//show final scores and winner annoucement
void Game::showResult(){
  board->printBoard();
  cout << "GAME OVER" << endl;
  cout << "Score for " << player1->getName() << ": " << player1->getScore() << endl;
  cout << "Score for " << player2->getName() << ": " << player2->getScore() << endl;

  if (player1->getScore() > player2->getScore())
    cout << "Player " << player1->getName() << " won!" << endl;
  else if (player1->getScore() < player2->getScore())
    cout << "Player " << player2->getName() << " won!" << endl;
  else
    cout << "DRAW! No winner!!" << endl;

}

void Game::saveGame(LinkedList* p1Hand, LinkedList* p2Hand, string p1Name,
                  string p2Name,int p1Score, int p2Score, string currentPlayer)
{
    string fullBoard = board->boardHeaderToString();
    fullBoard += board->boardBodyToString();
    std::ofstream saveFile(filename);

    if(!saveFile.fail()){
        saveFile << p1Name << "\n";
        saveFile << p1Score << "\n";
        Node* current = p1Hand->getHead();

        while(current != nullptr){
            if(current -> next != nullptr)
                saveFile << current->getTile()->toString() << ", ";
            else
                saveFile << current->getTile()->toString() << "\n";
            current = current->next;
        }
        saveFile << p2Name << "\n";
        saveFile << p2Score << "\n";

        current = p2Hand->getHead();

        while(current != nullptr){
            if(current -> next != nullptr)
                saveFile << current->getTile()->toString() << ", ";
            else
                saveFile << current->getTile()->toString() << "\n";
            current = current->next;
        }
        saveFile << fullBoard;

        current = this->tileBag->getHead();

        while(current != nullptr){
            if(current -> next != nullptr)
                saveFile << current->getTile()->toString() << ", ";
            else
                saveFile << current->getTile()->toString() << "\n";
            current = current->next;
        }
        saveFile << currentPlayer << "\n";
        saveFile.close();

        cout << "\nGame successfully saved\n" << endl;
    }
}

void Game::loadGame(){
    string p1Tiles;
    string p2Tiles;
    string tilesBagL;
    string boardL;
    string p1Name;
    string p2Name;
    int p1Score;
    int p2Score;

    string filename = getInput("Enter the filename from which load a game: ");

    filename += ".txt";
    cout << endl;
    std::fstream loadFile(filename, std::ios::in);
    if (!loadFile.fail()) {
      string loading;
      getline(loadFile, loading);
      p1Name = loading;
      getline(loadFile, loading);
      p1Score = std::stoi(loading);
      getline(loadFile, loading);
      p1Tiles = loading;
      getline(loadFile, loading);
      p2Name = loading;
      getline(loadFile, loading);
      p2Score = std::stoi(loading);
      getline(loadFile, loading);
      p2Tiles = loading;

      getline(loadFile, loading);
      boardL = loading + "\n";
      getline(loadFile, loading);
      boardL += loading + "\n";

      while(loading[2] != ',') {
        getline(loadFile, loading);
        if(loading[2] != ','){
          boardL += loading + "\n";
        }
        else{
          tilesBagL = loading;
        }
      }
      getline(loadFile, loading);
      currentPlayerName = loading;

//name, score
      player1 = new Player(p1Name);
      player2 = new Player(p2Name);
      player1->setScore(p1Score);
      player2->setScore(p2Score);
      tileBag = new LinkedList();
      currentPlayerName = player1->getName();

//tiles
      int i = 0;
      while(p1Tiles.substr(i + 2, 1) == ","){
        char color = p1Tiles[i];
        int shape = std::stoi(p1Tiles.substr(i + 1, 1));
        player1->addTiles(new Tile(color, shape));
        i += 4;
      }
      char color = p1Tiles[i];
      int shape = std::stoi(p1Tiles.substr(i + 1, 1));
      player1->addTiles(new Tile(color, shape));

      i = 0;
      while (p2Tiles.substr(i + 2, 1) == ",") {
        char color = p2Tiles[i];
        int shape = std::stoi(p2Tiles.substr(i + 1, 1));
        player2->addTiles(new Tile(color, shape));
        i += 4;
      }
      color = p2Tiles[i];
      shape = std::stoi(p2Tiles.substr(i + 1, 1));
      player2->addTiles(new Tile(color, shape));

      i = 0;
      while (tilesBagL.substr(i + 2, 1) == ",") {
        char color = tilesBagL[i];
        int shape = std::stoi(tilesBagL.substr(i + 1, 1));
        tileBag->add(new Tile(color, shape));
        i += 4;
      }
      color = tilesBagL[i];
      shape = std::stoi(tilesBagL.substr(i + 1, 1));
      tileBag->add(new Tile(color, shape));

//Board
      i = 0;
      while (boardL.substr(i + 3, 1) != " ") {
        i += 3;
      }
      boardCols = stoi(boardL.substr(i - 3, 1));
      boardCols = boardCols + 1;
      boardRows = boardL.length() / (i) - 2;
      board = new Board(boardRows, boardCols);

      for (i = 1; i < boardL.length(); i++) {
        if (boardL.substr(i, 1) == "|" && boardL.substr(i - 1,1) != " ") {
          color = boardL[i - 2];
          shape = std::stoi(boardL.substr(i-1, 1));
          int tileCol = ((i - 2) % (3 * boardCols + 5)) / 3 - 1;
          int tileRow = ((i - 2) / (3 * boardCols + 5)) - 2;

          board->store(new Tile(color, shape), tileRow, tileCol);
        }
      }
      play();
    }
    else{
      cout << "No such file, please check the file name!" << endl;
    }
}
