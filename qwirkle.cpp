
#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include <iostream>

#define EXIT_SUCCESS    0

using std::cout;
using std::endl;

int main(void) {
   LinkedList* list = new LinkedList();

   //B1
   Tile* tile1 = new Tile(BLUE, CIRCLE);
   //B3
   Tile* tile2 = new Tile(BLUE, DIAMOND);
   //G6
   Tile* tile3 = new Tile(GREEN, CLOVER);
   //O5
   Tile* tile4 = new Tile(ORANGE, STAR_6);

   Player* player1 = new Player();
   Player* player2 = new Player();
  // player1->showTilesOnHand();


   //testing... add 36 different kind of tiles to the list...
    for (int i = 1; i < 7; i++)
     for (int j = 0; j < 6; j++)
       list->add(new Tile(converToColour(j), i));

    for (int i = 0; i < 6; i++)
      player1->addTiles(list->getNext()->getTile());
    cout << "Player 1 has ";
    player1->showTilesOnHand();
    cout << endl;
    for (int i = 0; i < 6; i++)
      player2->addTiles(list->getNext()->getTile());
    cout << "Player 2 has ";
    player2->showTilesOnHand();
    cout << endl;

    cout << "after giving out tiles to the players. Now the bag has" << endl;
    list->show();
    cout << "and the bag now has " << list->count() << " tiles. " << endl;

   // list->show();
   // cout << "bag initialised. " << list->count() << " tiles added." << endl;
   //
   // Tile* test = list->getNextNode()->getTile();
   // cout << "1st withdraw: " << test->toString() << endl;
   // Tile* test2 = list->getNextNode()->getTile();
   // cout << "2nd withdraw: " << test2->toString() << endl;
   // cout << "all left in bag now ";
   // list->show();
   //
   // cout << "Now the bag has " << list->count() << " tiles. " << endl;

   delete list;
   return EXIT_SUCCESS;
}
