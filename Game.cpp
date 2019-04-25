#include "Game.h"

Game::Game(){
  board = new Board();
  player1 = new Player("Leo");
  player2 = new Player("Tomas");
  list = new LinkedList();
  gameOver = false;
  currentPlayerName = player1->getName();
  gameSetup();
}

void Game::gameSetup(){
  //初始化牌堆
  for (int i = 1; i < 7; i++)
    for (int j = 0; j < 6; j++)
      list->add(new Tile(converToColour(j), i));

  //Player 1先抽6张牌
  for (int i = 0; i < 6; i++){
    player1->addTiles(list->getNext()->getTile());
    list->deleteFront();
  }
  //Player 2再抽6张牌
  for (int i = 0; i < 6; i++){
    player2->addTiles(list->getNext()->getTile());
    list->deleteFront();
  }
}

void Game::play(){
  while (!gameOver) {
    if (currentPlayerName == player1->getName()){
      makeAMove(player1);
      currentPlayerName = player2->getName();
    } else {
      makeAMove(player2);
      currentPlayerName = player1->getName();
    }
  }
}


void Game::makeAMove(Player* player){
  cout << player->getName() << ", it's your turn" << std::endl;
  board->printBoard();
  cout << endl;
  player->showTilesOnHand();
  cout << endl;
  std::string command;
  cout << "> ";
  std::getline(std::cin, command);
  std::string tileName = command.substr(6,2);
  int placeAtRow = std::stoi(command.substr(12,1));
  int placeAtCol = std::stoi(command.substr(13,1));
  Tile* tileToPlace = player->getTileToPlace(tileName);
  player->removeTile(tileName);
  player->addTiles(list->getNext()->getTile());
  list->deleteFront();

  board->store(tileToPlace, placeAtRow, placeAtCol);
  cout << std::endl;
}
