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
  return tileBag->size() < 0 &&
         player1->getTilesOnHand()->size() < 0 &&
         player2->getTilesOnHand()->size() < 0;
}

void Game::newGame(){
  board = new Board(boardRows, boardCols);
  player1 = new Player("Leo");
  player2 = new Player("Tomas");
  gameOver = false;
  currentPlayerName = player1->getName();
  tileBag = new LinkedList();
  gameSetup();
  play();
}

void Game::AIMove(vector<vector<Tile*> > boardTiles){
  std::vector<std::string> possibleSpots;

    for (int i = 0; i < boardTiles.size(); i++) {
      for (int j = 0; j < boardTiles[i].size(); j++) {
        if (boardTiles[i][j] != nullptr) {
          if (j - 1 > 0 && boardTiles[i][j - 1] == nullptr) {
            string spotString = std::to_string(i) + std::to_string(j - 1);
            possibleSpots.push_back(spotString);
          }
          if (j + 1 < board->getCols() && boardTiles[i][j + 1] == nullptr) {
            string spotString = std::to_string(i) + std::to_string(j + 1);
            possibleSpots.push_back(spotString);
          }
          if (i - 1 > 0 && boardTiles[i - 1][j] == nullptr) {
            string spotString = std::to_string(i - 1) + std::to_string(j);
            possibleSpots.push_back(spotString);
          }
          if (i + 1 < board->getRows() && boardTiles[i + 1][j] == nullptr) {
            string spotString = std::to_string(i + 1) + std::to_string(j);
            possibleSpots.push_back(spotString);
          }
        }
      }
    }
  //  int n = 0;
    Node* current = player2->getTilesOnHand()->getHead();
    bool placed = false;
  //  try each tile on the hand at each possible spot...
    for (int i = 0; i < possibleSpots.size(); i++) {
      int atRow = std::stoi(possibleSpots[i].substr(0, 1));
      int atCol = std::stoi(possibleSpots[i].substr(1,1));

      while (!placed && current != nullptr) {
        Tile* tile = current->getTile();

        if (canPlace(boardTiles, atRow, atCol, tile)
          && !board->isTileAlreadyAt(atRow, atCol)) {
          placeTile(tile, atRow, atCol, player2);
          calculateScores(board->getTilesOnBoard(), atRow, atCol);
          placed = true;
        }
        current = current->next;
      }
      current = player2->getTilesOnHand()->getHead();
     }

   if (!placed) {
     string tileToReplace = player2->getTilesOnHand()->getHead()->getTile()->toString();
     replaceTile(tileToReplace, player2);
  }
}

void Game::play(){
  while (!isGameOver()) {
    if (currentPlayerName == player1->getName()){
      displayInfo(player1);
      makeAMove(player1);
      givePlayerScore(player1);
      currentPlayerName = player2->getName();
    } else {
      displayInfo(player2);
      AIMove(board->getTilesOnBoard());
    //  makeAMove(player2);
      givePlayerScore(player2);
      currentPlayerName = player1->getName();
    }
  }
}

void Game::gameSetup(){
  //generate 2 randomized tile set
  // generateRandomizedTileSet();
  // generateRandomizedTileSet();
  //same color diferent shape initially
   // for (int i = 1; i < 7; i++)
   //   for (int j = 0; j < 6; j++){
   //     //tileBag->add(new Tile(converToColour(j), i));
   //     tileBag->add(new Tile(converToColour(i), j+1));
   //     tileBag->add(new Tile(converToColour(i), j+1));
   //   }

  //same shape different colour
     for (int i = 0; i < 6; i++)
       for (int j = 1; j < 7; j++){
         //tileBag->add(new Tile(converToColour(j), i));
         tileBag->add(new Tile(converToColour(j), i+1));
         tileBag->add(new Tile(converToColour(j), i+1));
       }

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

  if (command.substr(0, 6) == "PLACE "){
    std::string tileName = command.substr(6,2);
    int placeAtRow = letterToInt(command.substr(12,1));
    int placeAtCol = std::stoi(command.substr(13,2));

    if (player->getTilesOnHand()->has(tileName)) {
      Tile* tileToPlace = player->findTile(tileName);
      vector<vector<Tile*> > currentTilesOnBoard = board->getTilesOnBoard();

      if (!board->isTileAlreadyAt(placeAtRow, placeAtCol)){
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
  int leftward = -1;
  int rightward = 1;
  int upward = -1;
  int downward = 1;
  bool validMove = false;
  int tileCheckRequired = 0;
  int currentCheckPassed = 0;

  if (!board->isFirstTileOnBoard()) {
    validMove = true;
    scoreToGive = 1;
  }
  else {
    //make sure it does not check at indexs outside the game board boundaries
    //row or column type check is required whenever there are tiles around the spot
    //that user tries to place the tile so that a tile satisfies both row and column rules
    if (atCol - 1 >= 0 && boardTiles[atRow][atCol - 1] != nullptr)
      tileCheckRequired += 1;
    if (atCol + 1 < board->getCols() && boardTiles[atRow][atCol + 1] != nullptr)
      tileCheckRequired += 1;
    if (atRow - 1 >= 0 && boardTiles[atRow - 1][atCol] != nullptr)
      tileCheckRequired += 1;
    if (atRow + 1 < board->getRows() && boardTiles[atRow + 1][atCol] != nullptr)
      tileCheckRequired += 1;
      cout << "check required: " << tileCheckRequired << endl;
    if (matchHorizontalTiles(boardTiles, atRow, atCol - 1, tile, leftward))
      currentCheckPassed += 1;
    if (matchHorizontalTiles(boardTiles, atRow, atCol + 1, tile, rightward))
      currentCheckPassed += 1;
    if (matchVerticalTiles(boardTiles, atRow - 1, atCol, tile, upward))
      currentCheckPassed += 1;
    if (matchVerticalTiles(boardTiles, atRow + 1, atCol, tile, downward))
      currentCheckPassed += 1;
  }
  //matched all tile types around the spot that player tries to place
  if (currentCheckPassed == tileCheckRequired)
    validMove = true;
  //no tiles around the spot that player tries to place
  if (tileCheckRequired == 0 && board->isFirstTileOnBoard()) {
    validMove = false;
  }

  return validMove;
}

bool Game::matchHorizontalTiles(vector<vector<Tile*> > boardTiles,
  int atRow, int atCol, Tile* tile, int direction) {
    bool valid = false;
    bool endCheck = false;

    while (!endCheck && atCol >= 0 && atCol < board->getCols() &&
      boardTiles[atRow][atCol] != nullptr) {
        if (boardTiles[atRow][atCol]->getColour() == tile->getColour()
            && boardTiles[atRow][atCol]->getShape() != tile->getShape()) {
          valid = true;
          atCol += direction;
        } else {
          valid = false;
          endCheck = true;
        }
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
    cout << tileCount << endl;
    atRow += direction;
  }

  if (tileCount == 5)
    isQwirkle = true;
  return tileCount;
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
  cout << endl;
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

    string filename;
    cout << "Enter the filename from which load a game: " ;
    cin >> filename;
    filename += ".txt";
    cout << endl;
    std::fstream loadFile(filename, std::ios::in);
    if(!loadFile.fail()){
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
      while(loading[2]!=','){
        getline(loadFile, loading);
        if(loading[2]!=','){
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
      gameOver = false;
      tileBag = new LinkedList();
      currentPlayerName = player1->getName();

//tiles
      int i = 0;
      while(p1Tiles.substr(i+2, 1) == ","){
        char color = p1Tiles[i];
        int shape = std::stoi(p1Tiles.substr(i+1, 1));
        player1->addTiles(new Tile(color, shape));
        i += 4;
      }
      char color = p1Tiles[i];
      int shape = std::stoi(p1Tiles.substr(i+1, 1));
      player1->addTiles(new Tile(color, shape));


      i = 0;
      while(p2Tiles.substr(i+2, 1) == ","){
        char color = p2Tiles[i];
        int shape = std::stoi(p2Tiles.substr(i+1, 1));
        player2->addTiles(new Tile(color, shape));
        i += 4;
      }
      color = p2Tiles[i];
      shape = std::stoi(p2Tiles.substr(i+1, 1));
      player2->addTiles(new Tile(color, shape));


      i = 0;
      while(tilesBagL.substr(i+2, 1) == ","){
        char color = tilesBagL[i];
        int shape = std::stoi(tilesBagL.substr(i+1, 1));
        tileBag->add(new Tile(color, shape));
        i += 4;
      }
      color = tilesBagL[i];
      shape = std::stoi(tilesBagL.substr(i+1, 1));
      tileBag->add(new Tile(color, shape));

//Board
      i = 0;
      while(boardL.substr(i+3, 1) != " "){
        i += 3;
      }
      boardCols = stoi(boardL.substr(i-3, 1));
      boardCols = boardCols + 1;
      boardRows = boardL.length()/(i) - 2;
      board = new Board(boardRows, boardCols);

      for(i = 1; i < boardL.length(); i++){
        if(boardL.substr(i, 1) == "|" && boardL.substr(i-1,1) != " "){
          color = boardL[i-2];
          shape = std::stoi(boardL.substr(i-1, 1));
          int tileCol = ((i-2)%(3*boardCols+5))/3 - 1;
          int tileRow = ((i-2)/(3*boardCols+5))-2;

          board->store(new Tile(color, shape), tileRow, tileCol);
        }
      }

      play();



    }
    else{
      cout << "No that file, please check the file name without '.txt'." << endl;
    }


}
