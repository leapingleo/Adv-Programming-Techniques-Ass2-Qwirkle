#include "Player.h"

Player::Player(){
  tilesOnHand = new LinkedList();
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
