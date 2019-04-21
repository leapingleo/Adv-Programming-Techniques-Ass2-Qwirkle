#ifndef PLAYER_H
#define PLAYER_H

#include "TileCodes.h"

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
  Player();

  void setName(std::string name);
private:
  std::string name;
  int score;

};

#endif
