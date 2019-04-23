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

  void store(Tile* tile, int row, int col);

  string boardBodyToString();

  string letterForRows(int rowNumber);

  vector<vector<Tile*> > boardRows;

  int getRows();

  int getCols();

  int rows = 0;
  int cols = 0;
};

#endif
