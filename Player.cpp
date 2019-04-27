#include "Player.h"

Player::Player(std::string name){
  tilesOnHand = new LinkedList();
  tileToReplace = nullptr;
  this->name = name;
}

void Player::addTiles(Tile* tile){
  tilesOnHand->add(tile);
}

void Player::showTilesOnHand(){
  Node* current = tilesOnHand->getHead();
  std::cout << "Your hand is, " << std::endl;

  while (current != nullptr){
    if (current->next != nullptr)
      std::cout << current->getTile()->toString() << ", ";
    else
      std::cout << current->getTile()->toString();
    current = current->next;
  }
  std::cout << std::endl;
}

void Player::replaceTile(std::string name){
  if (tilesOnHand->has(name)){
    tileToReplace = tilesOnHand->findNode(name)->getTile();
    tilesOnHand->remove(name);
  }
}

void Player::removeTile(std::string name){
  if (tilesOnHand->has(name))
    tilesOnHand->remove(name);
}

Tile* Player::findTile(std::string name){
  Tile* tile = nullptr;

  if (tilesOnHand->has(name))
    tile = tilesOnHand->findNode(name)->getTile();
  return tile;
}

Tile* Player::getToBeReplacedTile(){
  Tile* tile = nullptr;

  if (tilesOnHand->has(name))
    tile = tilesOnHand->findNode(name)->getTile();

  return tile;
}

LinkedList* Player::getTilesOnHand(){
  return tilesOnHand;
}

std::string Player::getName(){
  return name;
}

int Player::getScore(){
  return score;
}
