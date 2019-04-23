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

  void store(Tile* tile, int row, int col);

  void printBoard();

  string boardHeaderToString();

  string boardBodyToString();

  string letterForRows(int rowNumber);

  vector<vector<Tile*> > boardRows;

  int getRows();

  int getCols();

  int rows = 0;
  int cols = 0;
};

#endif
