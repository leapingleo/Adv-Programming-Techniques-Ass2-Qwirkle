
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
   Board* board = new Board();
   Tile* tile = new Tile(ORANGE, 1);
   board->store(tile, 2, 2);
   Tile* tile1 = new Tile(BLUE, 5);
   board->store(tile1, 3, 3);
   Tile* tile2 = new Tile(PURPLE, 3);
   board->store(tile2, 3, 3);
   cout << board->boardHeaderToString(6);
   cout << board->boardBodyToString();

   delete list;
   return EXIT_SUCCESS;
}

//TESTING ARCHIVE...
/*
Player* player1 = new Player();
Player* player2 = new Player();
// player1->showTilesOnHand();

//testing... add 36 different kind of tiles to the list...
 for (int i = 1; i < 7; i++)
  for (int j = 0; j < 6; j++)
    list->add(new Tile(converToColour(j), i));

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
