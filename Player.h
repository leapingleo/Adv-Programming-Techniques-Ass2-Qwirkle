#ifndef PLAYER_H
#define PLAYER_H

#include "TileCodes.h"
#include <iostream>
#include "LinkedList.h"
#include "Tile.h"
//PLAYER GOT:
//1. tiles on hand
//2. name and score
//
//PLAYER CAN:
//1. place a tile on board
//2. swap a tile
//
//checking methods:
//1. check if player has the particular tile so that the player makes
//   a valid move

class Player {
public:
  Player(std::string name);

  void setName(std::string name);

  void addTiles(Tile* tile);

  void removeTile(std::string name);

  void showTilesOnHand();

  void replaceTile(std::string name);

  void canTakeTurn(bool state);

  LinkedList* getTilesOnHand();

  Tile* getToBeReplacedTile();

  Tile* getTileToPlace(std::string name);

  bool isPlayersTurn();
private:
  std::string name;
  int score;
  LinkedList* tilesOnHand;
  Tile* tileToReplace;
  bool canPlay;
};

#endif
