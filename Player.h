#ifndef PLAYER_H
#define PLAYER_H

#include "TileCodes.h"
#include <iostream>
#include "LinkedList.h"
#include "Tile.h"

class Player {
public:
  Player(std::string name);

  ~Player();

  void setName(std::string name);

  void addTiles(Tile* tile);

  void addScore(int score);

  void removeTile(std::string name);

  void showTilesOnHand();

  LinkedList* getTilesOnHand();

  Tile* findTile(std::string name);

  std::string getName();

  int getScore();

  int setScore(int score);
private:
  std::string name;
  int score;
  LinkedList* tilesOnHand;
  Tile* tileToReplace;
};

#endif
