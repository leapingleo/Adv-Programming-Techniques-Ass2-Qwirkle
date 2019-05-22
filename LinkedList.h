
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

   void remove(std::string name);

   int size();

   bool has(std::string name);

   Node* getNext();
   
   Node* findNode(std::string name);

   Node* getHead();

private:
   Node* head;
};

#endif // ASSIGN2_LINKEDLIST_H
