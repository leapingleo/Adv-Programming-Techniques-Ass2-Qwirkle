#include "Game.h"

Game::Game(){
  /*board = new Board(boardRows, boardCols);
  player1 = new Player("Leo");
  player2 = new Player("Tomas");
  gameOver = false;
  currentPlayerName = player1->getName();
  gameSetup();*/
}

Game::~Game(){
  delete player1;
  delete player2;
  delete tileBag;
}

bool Game::isGameOver() {
  return tileBag->size() == 0 &&
         player1->getTilesOnHand()->size() == 0 &&
         player2->getTilesOnHand()->size() == 0;
}

void Game::newGame(string name1, string name2){
  board = new Board(boardRows, boardCols);
  player1 = new Player(name1);
  player2 = new Player(name2);
  currentPlayerName = player1->getName();
  tileBag = new LinkedList();
  gameSetup();
  play();
}

void Game::AIMove(vector<vector<Tile*> > boardTiles, Player* player){
  std::vector<std::string> possibleSpots;

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
  //  int n = 0;
    Node* current = player->getTilesOnHand()->getHead();
    bool placed = false;
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

   if (!placed && tileBag->size() > 0) {
     string tileToReplace = player->getTilesOnHand()->getHead()->getTile()->toString();
     replaceTile(tileToReplace, player);
  }
}

void Game::play(){
    while (!isGameOver()) {
    if (currentPlayerName == player1->getName()){

      displayInfo(player1);
      AIMove(board->getTilesOnBoard(), player1);
    //  makeAMove(player1);
      givePlayerScore(player1);
      currentPlayerName = player2->getName();
      cout << "player 1: " << player1->getTilesOnHand()->size() << " tiles left" << endl;
    } else {
      displayInfo(player2);
      AIMove(board->getTilesOnBoard(), player2);
  //  makeAMove(player2);
      givePlayerScore(player2);
      currentPlayerName = player1->getName();
      cout << "player 2: " << player2->getTilesOnHand()->size() << " tiles left" << endl;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(130));
  }
  endGameInfo(player1, player2);
}

void Game::gameSetup(){
  //generate 2 randomized tile set
   generateRandomizedTileSet();
   generateRandomizedTileSet();
  // generateRandomizedTileSet();
  //same color diferent shape initially
   // for (int i = 1; i < 7; i++)
   //   for (int j = 0; j < 6; j++){
   //     //tileBag->add(new Tile(converToColour(j), i));
   //     tileBag->add(new Tile(converToColour(i), j+1));
   //     tileBag->add(new Tile(converToColour(i), j+1));
   //   }

  //same shape different colour
     // for (int i = 0; i < 6; i++)
     //   for (int j = 1; j < 7; j++){
     //     //tileBag->add(new Tile(converToColour(j), i));
     //     tileBag->add(new Tile(converToColour(j), i+1));
     //     tileBag->add(new Tile(converToColour(j), i+1));
     //   }

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

void Game::makeAMove(Player* player){
  std::string command = getInput("> ");
  transform(command.begin(),command.end(),command.begin(),::toupper);
  //get row and col from player's command

  if (command.substr(0, 6) == "PLACE " && command.length() > 6
        && command.substr(8, 1) == " " && command.substr(11,1) == " "){
    std::string tileName = command.substr(6,2);
    int placeAtRow = letterToInt(command.substr(12,1));
    int placeAtCol = std::stoi(command.substr(13,2));

    if (player->getTilesOnHand()->has(tileName)) {
      Tile* tileToPlace = player->findTile(tileName);
      vector<vector<Tile*> > currentTilesOnBoard = board->getTilesOnBoard();

      if (board->isWithinBound(placeAtRow, placeAtCol) &&
          !board->isTileAlreadyAt(placeAtRow, placeAtCol)){
        if (canPlace(currentTilesOnBoard, placeAtRow, placeAtCol, tileToPlace)) {
          placeTile(tileToPlace, placeAtRow, placeAtCol, player);
          calculateScores(currentTilesOnBoard,placeAtRow, placeAtCol);
        } else {
          printError("CANT PLACE HERE");
          makeAMove(player);
        }
      } else {
        printError("Either the spot is already taken or not a valid spot by the game rules. Think Again.");
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
      printError("ARE YOU SURE YOU HAVE THIS TILE???");
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
  else {
    printError("Invalid input. Check input format. If not sure, type 'HELP'");
    makeAMove(player);
  }
}

/*
  generate 36 different types of tile, i.e. 6 shapes * 6 colors
  shape and color are both represented as int from 1 to 6
  1. generate 36 different strings(color + shape), and put them into
     a random string set
  2. randomize the string set
  3. retrieve and parse each string as color and shape, and add each to the
     tile bag
  **The usual nestted for-loop generates a predictable pattern, so the above
    is used instead.
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
  unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
  shuffle(randomTileStringSet.begin(), randomTileStringSet.end(),
          std::default_random_engine(seed));

  for (int i = 0; i < randomTileStringSet.size(); i++) {
    char colour = std::stoi(randomTileStringSet[i].substr(0,1));
    int shape = std::stoi(randomTileStringSet[i].substr(1,1));
    tileBag->add(new Tile(converToColour(colour), shape));
  }
}


//check if a tile can be placed based on the rules
bool Game::canPlace(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile) {
  // int leftward = -1;
  // int rightward = 1;
  // int upward = -1;
  // int downward = 1;
//  cout << " gonna print at " << atRow << ", " << atCol << endl;
  bool validMove = false;
//  int tileCheckRequired = 0;
//  int currentCheckPassed = 0;

  if (!board->isFirstTileOnBoard()) {
    validMove = true;
    scoreToGive = 1;
  }
  // else {
  //   //make sure it does not check at indexs outside the game board boundaries
  //   //row or column type check is required whenever there are tiles around the spot
  //   //that user tries to place the tile so that a tile satisfies both row and column rules
  //   if (atCol - 1 >= 0 && boardTiles[atRow][atCol - 1] != nullptr)
  //     tileCheckRequired += 1;
  //   if (atCol + 1 < board->getCols() && boardTiles[atRow][atCol + 1] != nullptr)
  //     tileCheckRequired += 1;
  //   if (atRow - 1 >= 0 && boardTiles[atRow - 1][atCol] != nullptr)
  //     tileCheckRequired += 1;
  //   if (atRow + 1 < board->getRows() && boardTiles[atRow + 1][atCol] != nullptr)
  //     tileCheckRequired += 1;
  //   //  cout << "check required: " << tileCheckRequired << endl;
  //   if (matchHorizontalTiles(boardTiles, atRow, atCol - 1, tile, leftward))
  //     currentCheckPassed += 1;
  //   if (matchHorizontalTiles(boardTiles, atRow, atCol + 1, tile, rightward))
  //     currentCheckPassed += 1;
  //   if (matchVerticalTiles(boardTiles, atRow - 1, atCol, tile, upward))
  //     currentCheckPassed += 1;
  //   if (matchVerticalTiles(boardTiles, atRow + 1, atCol, tile, downward))
  //     currentCheckPassed += 1;
  // }
  //matched all tile types around the spot that player tries to place
//  if (currentCheckPassed == tileCheckRequired)
//    validMove = true;
  else{
  if (matchHorizontalTiles(boardTiles, atRow, atCol, tile, 1))
    validMove = true;
  }
  //no tiles around the spot that player tries to place
//  if (tileCheckRequired == 0 && board->isFirstTileOnBoard()) {
//    validMove = false;
//  }

  return validMove;
}

bool Game::matchHorizontalTiles(vector<vector<Tile*> > boardTiles,
  int atRow, int atCol, Tile* tile, int direction) {
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
    bool horizontalCheck = false;
    bool verticalCheck = false;

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

    for (int i = 0; i < horizontalTiles.size(); i++){
      if (horizontalTiles[i]->getColour() == tile->getColour()
           && horizontalTiles[i]->getShape() != tile->getShape() && !endCheck) {
             horizontalCheck = true;
           }
      else {
        horizontalCheck = false;
        endCheck = true;
      }
    }

    for (int i = 0; i < verticalTiles.size(); i++){
      if (verticalTiles[i]->getColour() != tile->getColour()
           && verticalTiles[i]->getShape() == tile->getShape() && !endCheck) {
             verticalCheck = true;
           }
      else{
        verticalCheck = false;
        endCheck = true;
      }
    }

    for (int i = 0; i < leftTiles.size(); i++){
      for (int j = 0; j < rightTiles.size(); j++)
        if (leftTiles[i]->toString() == rightTiles[j]->toString() && !endCheck){
          endCheck = true;
          horizontalCheck = false;
        }
    }

    for (int i = 0; i < upTiles.size(); i++){
      for (int j = 0; j < downTiles.size(); j++)
        if (upTiles[i]->toString() == downTiles[j]->toString() && !endCheck){
          endCheck = true;
          verticalCheck = false;
        }
    }


    if (verticalTiles.empty() && horizontalCheck){
      valid = true;
    }
    if (horizontalTiles.empty() && verticalCheck) {
      valid = true;
    }
    if (!horizontalTiles.empty() && !horizontalTiles.empty()) {
      if (horizontalCheck && verticalCheck)
        valid = true;
    }

    return valid;
}

bool Game::matchVerticalTiles(vector<vector<Tile*> > boardTiles,
              int atRow, int atCol, Tile* tile, int direction) {
  bool valid = false;
  bool endCheck = false;

  while (!endCheck && atRow >= 0 && atRow < board->getRows() &&
       boardTiles[atRow][atCol] != nullptr) {
    if (boardTiles[atRow][atCol]->getColour() != tile->getColour()
        && boardTiles[atRow][atCol]->getShape() == tile->getShape()) {
      valid = true;
      atRow += direction;
    } else {
      valid = false;
      endCheck = true;
    }
  }
  return valid;
}

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

int Game::countColTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction) {
  int tileCount = 0;

  while (atCol >= 0 && atCol < board->getCols() &&
      boardTiles[atRow][atCol] != nullptr) {
    tileCount++;
    atCol += direction;
  }

  if (tileCount == 5)
    isQwirkle = true;
  return tileCount;
}

int Game::countRowTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction) {
  int tileCount = 0;
  while (atRow >= 0 && atRow < board->getRows() &&
            boardTiles[atRow][atCol] != nullptr) {
    tileCount++;
    //cout << tileCount << endl;
    atRow += direction;
  }

  if (tileCount == 5)
    isQwirkle = true;
  return tileCount;
}



void Game::replaceTile(std::string tileName, Player* player){
  if (tileBag->size() > 0) {
    tileBag->add(player->findTile(tileName));
    player->removeTile(tileName);
    player->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
}

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

void Game::givePlayerScore(Player* player) {
  if (isQwirkle) {
    scoreToGive += 6;
    cout << "QWIRKLE!!!" << endl;
  }
  player->addScore(scoreToGive);
  isQwirkle = false;
  scoreToGive = 0;
}

void Game::displayInfo(Player* player){
  cout << player->getName() << ", it's your turn\n" << endl;
  cout << "Score for " << player1->getName() << ": " << player1->getScore() << endl;
  cout << "Score for " << player2->getName() << ": " << player2->getScore() << endl;
  cout << endl;
  board->printBoard();
  cout << endl;
  player->showTilesOnHand();
}

void Game::endGameInfo(Player* p1, Player* p2){
  board->printBoard();
  cout << "GAME OVER" << endl;
  cout << "Score for " << p1->getName() << ": " << p1->getScore() << endl;
  cout << "Score for " << p2->getName() << ": " << p2->getScore() << endl;
  if (p1->getScore() > p2->getScore())
    cout << "Player " << p1->getName() << " won!" << endl;
  else if (p1->getScore() < p2->getScore())
    cout << "Player " << p2->getName() << " won!" << endl;
  else
    cout << "DRAW! No winner!!" << endl;
  cout << "Goodbye" << endl;
}

// Save file function
void Game::saveGame(LinkedList* p1Hand, LinkedList* p2Hand, string p1Name,
                  string p2Name,int p1Score, int p2Score, string currentPlayer)
{
    // Make vector board to string
    string fullBoard = board->boardHeaderToString();
    fullBoard += board->boardBodyToString();

    // basic function to write in txt
    std::ofstream saveFile(filename);
    if(!saveFile.fail()){
        // Save player1's name and score
        saveFile << p1Name << "\n";
        saveFile << p1Score << "\n";

        // Tostring and Save player1's handtiles
        Node* current = p1Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                saveFile << current->getTile()->toString() << ", ";
            else
                saveFile << current->getTile()->toString() << "\n";
            current = current->next;
        }

        // Save player2's name and score
        saveFile << p2Name << "\n";
        saveFile << p2Score << "\n";

        // Tostring and Save player2's handtiles
        current = p2Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                saveFile << current->getTile()->toString() << ", ";
            else
                saveFile << current->getTile()->toString() << "\n";
            current = current->next;
        }

        // Save the board
        saveFile << fullBoard;

        // Tostring and Save tilebags
        current = this->tileBag->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                saveFile << current->getTile()->toString() << ", ";
            else
                saveFile << current->getTile()->toString() << "\n";
            current = current->next;
        }

        // Save the current Player name
        saveFile << currentPlayer << "\n";

        // close the stream
        saveFile.close();

        cout << "\nGame successfully saved\n" << endl;
    }
}


// Load file function
void Game::loadGame(){
    // Create some useful variable
    string p1Tiles;
    string p2Tiles;
    string tilesBagL;
    string boardL;
    string p1Name;
    string p2Name;
    int p1Score;
    int p2Score;

    // Get the file name
    string filename = getInput("Enter the filename from which load a game: ");
    filename += ".txt";
    cout << endl;

    // basic load from txt
    std::fstream loadFile(filename, std::ios::in);
    if (!loadFile.fail()) {
      //load information as string
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
      // add board title in one string
      getline(loadFile, loading);
      boardL = loading + "\n";
      getline(loadFile, loading);
      boardL += loading + "\n";

      // used to split board and tilebag
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

//implement the string of name and score to the program
      player1 = new Player(p1Name);
      player2 = new Player(p2Name);
      player1->setScore(p1Score);
      player2->setScore(p2Score);
      tileBag = new LinkedList();
      currentPlayerName = player1->getName();

//add player1 player2 and tilebags to different linkedlist
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

// use string board to create a new board and place tiles
      i = 0;
      while (boardL.substr(i + 3, 1) != " ") {
        i += 3;
      }
      // use mathematic way to get the column and rows of board
      boardCols = stoi(boardL.substr(i - 3, 1));
      boardCols = boardCols + 1;
      boardRows = boardL.length() / (i) - 2;
      board = new Board(boardRows, boardCols);
      
      // use mathematic way to get tiles in board and the position of tiles
      for (i = 1; i < boardL.length(); i++) {
        if (boardL.substr(i, 1) == "|" && boardL.substr(i - 1,1) != " ") {
          color = boardL[i - 2];
          shape = std::stoi(boardL.substr(i-1, 1));
          int tileCol = ((i - 2) % (3 * boardCols + 5)) / 3 - 1;
          int tileRow = ((i - 2) / (3 * boardCols + 5)) - 2;

          // place tiles
          board->store(new Tile(color, shape), tileRow, tileCol);
        }
      }
      // continue game
      play();
    }
    else{
      cout << "No such file, please check the file name!" << endl;
    }
}
