#include "Player.h"

Player::Player(){
  tilesOnHand = new LinkedList();
  tileToReplace = nullptr;
}

void Player::addTiles(Tile* tile){
  tilesOnHand->add(tile);
}

void Player::showTilesOnHand(){
  tilesOnHand->show();
}

LinkedList* Player::getTilesOnHand(){
  return tilesOnHand;
}

void Player::replaceTile(std::string name){
  if (tilesOnHand->has(name)){
    tileToReplace = tilesOnHand->findNode(name)->getTile();
    tilesOnHand->remove(name);
  }
}

Tile* Player::getToBeReplacedTile(){
  return tileToReplace;
}
