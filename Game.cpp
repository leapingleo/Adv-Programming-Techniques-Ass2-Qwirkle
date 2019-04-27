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

void Game::gameSetup(){
  //初始化牌堆
  for (int i = 1; i < 7; i++)
    for (int j = 0; j < 6; j++)
      tileBag->add(new Tile(converToColour(j), i));

  //Player 1先抽6张牌
  for (int i = 0; i < 6; i++){
    player1->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
  //Player 2再抽6张牌
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

  if (command.substr(0, 5) == "PLACE"){
    //PLACE XX AT XX
    std::string tileName = command.substr(6,2);
    int placeAtRow = letterToInt(command.substr(12,1));
    int placeAtCol = std::stoi(command.substr(13,2));

    if (player->getTilesOnHand()->has(tileName)) {
      Tile* tileToPlace = player->findTile(tileName);

      if (!board->isTileAlreadyAt(placeAtRow, placeAtCol)
        && isWithinBound(placeAtRow, placeAtCol, board->getRows(), board->getCols())){
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
  else if (command.substr(0, 7) == "REPLACE"){
    std::string tileToReplace = command.substr(8,2);

    if (player->getTilesOnHand()->has(tileToReplace)) {
      replaceTile(tileToReplace, player);
    } else {
      printError("ARE YOU SURE YOU HAVE THIS TILE???");
      makeAMove(player);
    }
  } else {
    printError("INVALID INPUT.");
    makeAMove(player);
  }
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
  //delete the withdrawn tile
  tileBag->deleteFront();
  board->store(tile, atRow, atCol);
  cout << std::endl;
}

void Game::save(){
  std::string s = board->boardHeaderToString();
  s += board->boardBodyToString();
  std::string fileName = "save.txt";

  std::ofstream ofile(fileName);
  if(!ofile.fail()){
    ofile << s;
  }
}
