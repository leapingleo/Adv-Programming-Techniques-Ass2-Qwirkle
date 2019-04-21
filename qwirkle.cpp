
#include "LinkedList.h"
#include "Tile.h"
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


   //testing... add 36 different kind of tiles to the list...
   for (int i = 1; i < 7; i++)
    for (int j = 0; j < 6; j++)
      list->add(new Tile(converToColour(j), i));

   list->show();
   cout << "bag initialised. " << list->count() << " tiles added." << endl;

   Tile* test = list->getNextNode()->getTile();
   cout << "1st withdraw: " << test->toString() << endl;
   Tile* test2 = list->getNextNode()->getTile();
   cout << "2nd withdraw: " << test2->toString() << endl;
   cout << "all left in bag now ";
   list->show();

   cout << "Now the bag has " << list->count() << " tiles. " << endl;

   delete list;
   return EXIT_SUCCESS;
}
