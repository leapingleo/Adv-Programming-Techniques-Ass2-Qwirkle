
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

Node* LinkedList::getNext(){
  Node* node = head;
  deleteFront();

  return node;
}

void LinkedList::deleteFront(){
  Node* headNext = head->next;
  delete head;
  head = headNext;
}

int LinkedList::count(){
  int count = 0;
  Node* current = head;

  while (current != nullptr){
    count++;
    current = current->next;
  }
  return count;
}

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
