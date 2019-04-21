
#ifndef ASSIGN2_LINKEDLIST_H
#define ASSIGN2_LINKEDLIST_H

#include "Node.h"

class LinkedList {
public:

   LinkedList();
   ~LinkedList();

   void add(Tile* tile);
   void show();
   void deleteFront();

   int count();

   Node* getNextNode();
private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
