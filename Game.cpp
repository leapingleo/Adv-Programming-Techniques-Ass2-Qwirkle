#include "Game.h"

Game::Game(){
  board = new Board(boardRows, boardCols);

  player1 = new Player("Leo");
  player2 = new Player("Tomas");
  tileBag = new LinkedList();
  gameOver = false;
  currentPlayerName = player1->getName();
  gameSetup();
}

Game::~Game(){
  delete player1;
  delete player2;
  delete tileBag;
}

bool Game::isGameOver() {
  return tileBag->size() < 0
          && player1->getTilesOnHand()->size() < 0
          && player2->getTilesOnHand()->size() < 0;
}

void Game::AIMove(vector<vector<Tile*> > boardTiles){
  std::vector<std::string> possibleSpots;


  if (board->isFirstTileOnBoard()) {
    for (int i = 0; i < boardTiles.size(); i++)
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

    //try each tile on the hand at each possible spot...
    for (int i = 0; i < possibleSpots.size(); i++) {
      cout << possibleSpots[i] << endl;
      int atRow = std::stoi(possibleSpots[i].substr(0, 1));
      int atCol = std::stoi(possibleSpots[i].substr(1,1));

      Node* current = player2->getTilesOnHand()->getHead();

      while (current != nullptr) {
        Tile* tile = current->getTile();
        if (canPlace(boardTiles, atRow, atCol, tile)) {
          placeTile(tile, atRow, atCol, player2);
          break;
        }
        current = current->next;
      }
    }





  }







}

void Game::gameSetup(){
  //generate 2 randomized tile set
  generateRandomizedTileSet();
  generateRandomizedTileSet();

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
      //makeAMove(player2);
      givePlayerScore(player2);
      currentPlayerName = player1->getName();
    }

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

      if (!board->isTileAlreadyAt(placeAtRow, placeAtCol)
          && canPlace(currentTilesOnBoard, placeAtRow, placeAtCol, tileToPlace)){
        placeTile(tileToPlace, placeAtRow, placeAtCol, player);

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
    //make sure seed is different
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
    int colour = std::stoi(randomTileStringSet[i].substr(0,1));
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
    //update required counter based on the tile around the spot user tries to place
    if (atCol - 1 > 0 && boardTiles[atRow][atCol - 1] != nullptr)
      tileCheckRequired += 1;
    if (atCol + 1 < board->getCols() && boardTiles[atRow][atCol + 1] != nullptr)
      tileCheckRequired += 1;
    if (atRow - 1 > 0 && boardTiles[atRow - 1][atCol] != nullptr)
      tileCheckRequired += 1;
    if (atRow + 1 < board->getRows() && boardTiles[atRow + 1][atCol] != nullptr)
      tileCheckRequired += 1;

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
    int tileCount = 0;

    while (atCol > 0 && atCol < board->getCols() &&
      boardTiles[atRow][atCol] != nullptr) {
        if (boardTiles[atRow][atCol]->getColour() == tile->getColour()
            && boardTiles[atRow][atCol]->getShape() != tile->getShape()) {
            valid = true;
            tileCount++;
          }
        atCol += direction;
    }
    if (tileCount == 5)
      isQwirkle = true;

    scoreToGive += tileCount;
    return valid;
}

bool Game::matchVerticalTiles(vector<vector<Tile*> > boardTiles,
              int atRow, int atCol, Tile* tile, int direction) {
  bool valid = false;
  int tileCount = 0;

  while (atRow > 0 && atRow < board->getRows() &&
       boardTiles[atRow][atCol] != nullptr) {
    if (boardTiles[atRow][atCol]->getColour() != tile->getColour()
        && boardTiles[atRow][atCol]->getShape() == tile->getShape()) {
          valid = true;
          tileCount++;
        }
    atRow += direction;
  }
  if (tileCount == 5)
    isQwirkle = true;

  scoreToGive += tileCount;
  return valid;
}

void Game::givePlayerScore(Player* player) {
  player->addScore(scoreToGive);
  if (isQwirkle)
    cout << "QWIRKLE!!!" << endl;
  isQwirkle = false;
  scoreToGive = 0;
}

void Game::displayInfo(Player* player){
  cout << player->getName() << ", it's your turn\r\n" << endl;
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

    std::ofstream ofile(filename);
    if(!ofile.fail()){
        ofile << p1Name << "\r\n";
        ofile << p1Score << "\r\n";

        Node* current = p1Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        }

        ofile << p2Name << "\r\n";
        ofile << p2Score << "\r\n";

        current = p2Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        }

        ofile << fullBoard;

        current = this->tileBag->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        }

        ofile << currentPlayer << "\r\n";

        ofile.close();

        cout << "\r\nGame successfully saved\r\n" << endl;
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
    std::fstream loadG(filename, std::ios::in);
    if(!loadG.fail()){
      string loading;
      getline(loadG, loading);
      p1Name = loading;
      getline(loadG, loading);
      p1Score = std::stoi(loading);
      getline(loadG, loading);
      p1Tiles = loading;
      getline(loadG, loading);
      p2Name = loading;
      getline(loadG, loading);
      p2Score = std::stoi(loading);
      getline(loadG, loading);
      p2Tiles = loading;

      getline(loadG, loading);
      boardL = loading + "\r\n";
      getline(loadG, loading);
      boardL += loading + "\r\n";
      while(loading[2]!=','){
        getline(loadG, loading);
        if(loading[2]!=','){
          boardL += loading + "\r\n";
        } 
        else{
          tilesBagL = loading;
        }
      }
      getline(loadG, loading);
      currentPlayerName = loading;
      
//name, score
      player1->setName(p1Name);
      player2->setName(p2Name);
      player1->setScore(p1Score);
      player2->setScore(p2Score);

//tiles
      int i = 0;
      while(p1Tiles.substr(i+2, 1) == ","){
        int color = std::stoi(p1Tiles.substr(i, 1));
        int shape = std::stoi(p1Tiles.substr(i+1, 1));
        player1->addTiles(new Tile(converToColour(color), shape));
        i += 2;
      }
      i = 0;
      while(p2Tiles.substr(i+2, 1) == ","){
        int color = std::stoi(p2Tiles.substr(i, 1));
        int shape = std::stoi(p2Tiles.substr(i+1, 1));
        player2->addTiles(new Tile(converToColour(color), shape));
        i += 2;
      }
      i = 0;
      while(tilesBagL.substr(i+2, 1) == ","){
        int color = std::stoi(tilesBagL.substr(i, 1));
        int shape = std::stoi(tilesBagL.substr(i+1, 1));
        tileBag->add(new Tile(converToColour(color), shape));
        i += 2;
      }
      
//Board

    }
    else{
      cout << "No that file, please check the file name without '.txt'." << endl;
    }
    


}