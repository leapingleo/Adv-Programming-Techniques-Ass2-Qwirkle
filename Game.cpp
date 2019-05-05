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

void Game::gameSetup(){
  //initialize the tile bag, not randomized just yet!
  for (int i = 1; i < 7; i++)
    for (int j = 0; j < 6; j++)
      tileBag->add(new Tile(converToColour(j), i));

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
  while (!gameOver) {
    if (currentPlayerName == player1->getName()){
      displayInfo(player1);
      makeAMove(player1);
      currentPlayerName = player2->getName();
    } else {
      displayInfo(player2);
      makeAMove(player2);
      currentPlayerName = player1->getName();
    }
  }
}

void Game::displayInfo(Player* player){
  cout << player->getName() << ", it's your turn" << std::endl;
  board->printBoard();
  cout << endl;
  player->showTilesOnHand();
  cout << endl;
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
        printError("SPOT NOT AVAILABLE! TRY AGAIN!");
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
    saveGame(player1->getTilesOnHand(), player2->getTilesOnHand(), player1->getName(), player2->getName() );
  }
  else {
    printError("Invalid input. Check input format. If not sure, type 'HELP'");
    makeAMove(player);
  }
}

bool Game::canPlace(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile) {
  int leftward = -1;
  int rightward = 1;
  int upward = -1;
  int downward = 1;
  bool validMove = false;
  int twoWayMatchCounter = 0;
  int currentMatch = 0;

  if (!board->isFirstTileOnBoard())
    validMove = true;
  else {
    if (boardTiles[atRow][atCol - 1] != nullptr)
      twoWayMatchCounter += 1;
    if (boardTiles[atRow][atCol + 1] != nullptr)
      twoWayMatchCounter += 1;
    if (boardTiles[atRow - 1][atCol] != nullptr)
      twoWayMatchCounter += 1;
    if (boardTiles[atRow + 1][atCol] != nullptr)
      twoWayMatchCounter += 1;

    if (matchHorizontalTiles(boardTiles, atRow, atCol - 1, tile, leftward))
      currentMatch += 1;
    if (matchHorizontalTiles(boardTiles, atRow, atCol + 1, tile, rightward))
      currentMatch += 1;
    if (matchVerticalTiles(boardTiles, atRow - 1, atCol, tile, upward))
      currentMatch += 1;
    if (matchVerticalTiles(boardTiles, atRow + 1, atCol, tile, downward))
      currentMatch += 1;
  }

  if (currentMatch == twoWayMatchCounter)
    validMove = true;

  return validMove;
}


bool Game::matchHorizontalTiles(vector<vector<Tile*> > boardTiles,
  int atRow, int atCol, Tile* tile, int direction) {
    bool valid = false;

    if (atCol > 0 && atCol < board->getCols())
      while (boardTiles[atRow][atCol] != nullptr) {
        if (boardTiles[atRow][atCol]->getColour() == tile->getColour()
            && boardTiles[atRow][atCol]->getShape() != tile->getShape()) {
            valid = true;
          }
        atCol += direction;
    }
    return valid;
}

bool Game::matchVerticalTiles(vector<vector<Tile*> > boardTiles,
              int atRow, int atCol, Tile* tile, int direction) {
  bool valid = false;

  if (atRow > 0 && atRow < board->getRows()) {
    while (boardTiles[atRow][atCol] != nullptr) {
      if (boardTiles[atRow][atCol]->getColour() != tile->getColour()
          && boardTiles[atRow][atCol]->getShape() == tile->getShape()) {
            valid = true;
          }
      atRow += direction;
    }
  }
  return valid;
}

void Game::replaceTile(std::string tileName, Player* player){
  player->removeTile(tileName);
  player->addTiles(tileBag->getNext()->getTile());
  tileBag->deleteFront();
  cout << std::endl;
}

void Game::placeTile(Tile* tile, int atRow, int atCol, Player* player){
  player->removeTile(tile->toString());
  //draw a new tile
  player->addTiles(tileBag->getNext()->getTile());
  //delete the withdrawn tile, which is always the head tile/node
  tileBag->deleteFront();
  board->store(tile, atRow, atCol);
  cout << std::endl;
}

void Game::saveGame(LinkedList* p1Hand, LinkedList* p2Hand, string p1Name, string p2Name /*int p1Score, int p2Score, */)
{
    std::string fullBoard = board->boardHeaderToString();
    fullBoard += board->boardBodyToString();

    std::ofstream ofile(filename);
    if(!ofile.fail()){
        ofile << p1Name << "\r\n";
/*        ofile << p1Score << "\r\n";
*/
        Node* current = p1Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        }

        ofile << p2Name << "\r\n";
/*        ofile << p2Score << "\r\n";
*/
        current = p2Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        }

        ofile << fullBoard << "\r\n";

        current = this->tileBag->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        }

        ofile << "which player" << "\r\n";

        ofile.close();

        cout << "Game successfully saved" << endl;
    }
}
