#include "Player.h"

Player::Player(std::string name){
  tilesOnHand = new LinkedList();
  tileToReplace = nullptr;
  this->name = name;
}

Player::~Player(){
  delete tilesOnHand;
}

void Player::setName(std::string name){
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

void Player::addScore(int score){
  this->score += score;
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

int Player::setScore(int score){
  this->score = score;
  return score;
}
