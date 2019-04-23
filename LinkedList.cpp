
#include "LinkedList.h"

LinkedList::LinkedList() {
   head = nullptr;
}

LinkedList::~LinkedList() {
}

//add a tile to the end of the list
void LinkedList::add(Tile* tile){
  Node* newNode = new Node(tile, nullptr);
  Node* current = head;

  if (current == nullptr) {
    head = newNode;
  } else {
    while (current->next != nullptr) {
      current = current->next;
    }
    current->next = newNode;
  }
}

void LinkedList::show(){
  Node* current = head;

  while (current != nullptr){
    std::cout << current->getTile()->toString() << std::endl;
    current = current->next;
  }
}

//get next node
Node* LinkedList::getNext(){
  Node* node = head;
  deleteFront();

  return node;
}

//delete front node
void LinkedList::deleteFront(){
  if (this->head != nullptr) {
    Node* toDelete = this->head;
    this->head = toDelete->next;
    delete toDelete;
  }
}

//return the size of the list
int LinkedList::size(){
  int count = 0;
  Node* current = head;

  while (current != nullptr){
    count++;
    current = current->next;
  }
  return count;
}

//if a node is found in the list
bool LinkedList::has(std::string name){
  bool found = false;
  Node* current = head;

  while (current != nullptr){
    if (name == current->getTile()->toString() && !found)
      found = true;
    current = current->next;
  }
  return found;
}

void LinkedList::remove(std::string name){
  Node* current = head;
  Node* prev = nullptr;
  bool removed = false;

  while (current != nullptr){
    if (current->getTile()->toString() == name && !removed){
      Node* copyCurrent = current;
      delete current;
      prev->next = copyCurrent->next;
      removed = true;
    } else {
      prev = current;
      current = current->next;
    }
  }
}

//returns a matching node
Node* LinkedList::findNode(std::string name){
  Node* matchingNode = nullptr;
  bool found = false;
  Node* current = head;

  while (current != nullptr){
    if (current->getTile()->toString() == name && !found) {
      matchingNode = current;
      found = true;
    }
    current = current->next;
  }
  return matchingNode;
}
