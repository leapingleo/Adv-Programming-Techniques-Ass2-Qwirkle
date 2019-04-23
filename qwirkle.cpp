
#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include <iostream>

#define EXIT_SUCCESS    0

using std::cout;
using std::endl;


int main(void) {
   LinkedList* list = new LinkedList();
   //手动下棋测试
   Board* board = new Board();
   Player* player1 = new Player("Leo");
   player1->canTakeTurn(true);
   Player* player2 = new Player("Tomas");
   player2->canTakeTurn(false);
   //初始化牌堆
   for (int i = 1; i < 7; i++)
     for (int j = 0; j < 6; j++)
       list->add(new Tile(converToColour(j), i));

   //Player 1先抽6张牌
   for (int i = 0; i < 6; i++){
     player1->addTiles(list->getNext()->getTile());
     list->deleteFront();
   }
   player1->showTilesOnHand();
   //Player 2再抽6张牌
   for (int i = 0; i < 6; i++){
     player2->addTiles(list->getNext()->getTile());
     list->deleteFront();
   }
   player2->showTilesOnHand();

   while (true){
   player1->showTilesOnHand();
   std::string command;
   cout << "> ";
   std::getline(std::cin, command);
   cout<<"the command is " << command << std::endl;
   std::string tileName = command.substr(6,2);
   int placeAtRow = std::stoi(command.substr(12,1));
   int placeAtCol = std::stoi(command.substr(13,1));
   Tile* tileToPlace = player1->getTileToPlace(tileName);
   player1->removeTile(tileName);
  // char tileColor = ;
  // int tileShape = ;
   //std::cout << placeAtRow << std::endl;
   //Tile* tile2 = new Tile(ORANGE, 3);
   board->store(tileToPlace, placeAtRow, placeAtCol);
   board->printBoard();
 }
   delete list;
   delete player1;
   delete player2;
   return EXIT_SUCCESS;
}



//TESTING ARCHIVE...
/*
Player* player1 = new Player();
Player* player2 = new Player();
// player1->showTilesOnHand();

//testing... add 36 different kind of tiles to the list...


 for (int i = 0; i < 6; i++)
   player1->addTiles(list->getNext()->getTile());

 cout << "Player 1 has " << endl;

 player1->replaceTile("O1");
 list->add(player1->getToBeReplacedTile());
 player1->addTiles(list->getNext()->getTile());

 player1->replaceTile("G1");
 player1->addTiles(list->getNext()->getTile());
 list->add(player1->getToBeReplacedTile());
 player1->showTilesOnHand();
 cout << endl;

 for (int i = 0; i < 6; i++)
   player2->addTiles(list->getNext()->getTile());
 cout << "Player 2 has " << endl;
 player2->showTilesOnHand();
 cout << endl;

//  cout << "after giving out tiles to the players. Now the bag has" << endl;
//  list->show();


 list->remove("R4");
 list->remove("Y6");
 //list->show();
// cout << "bag initialised. " << list->count() << " tiles added." << endl;
//
// Tile* test = list->getNextNode()->getTile();
// cout << "1st withdraw: " << test->toString() << endl;
// Tile* test2 = list->getNextNode()->getTile();
// cout << "2nd withdraw: " << test2->toString() << endl;
// cout << "all left in bag now ";
 list->show();
//
 cout << "Now the bag has " << list->size() << " tiles. " << endl;
*/
