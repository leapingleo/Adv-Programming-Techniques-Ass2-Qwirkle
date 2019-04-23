#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H

#include "Tile.h"
#include <iostream>
#include <vector>

using std::vector;
using std::string;

class Board {
public:

  Board();

  string boardHeaderToString(int rows);

  void store(Tile* tile);

  string boardBodyToString();

  string letterForRows(int rowNumber);

  //vector<vector<Tile*> > board(6, vector<Tile*> a(6));

  int row;
  int col;
};

#endif
