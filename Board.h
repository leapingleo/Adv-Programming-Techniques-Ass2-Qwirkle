#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H


#include "Tile.h"
#include <iostream>
#include <vector>


using std::vector;
using std::string;

class Board {
public:

  Board(int rows, int cols);

  bool canPlace(int atRow, int atCol);

  void store(Tile* tile, int row, int col);

  void printBoard();

  string boardHeaderToString();

  string boardBodyToString();

  bool isTileAlreadyAt(int row, int col);

//  bool isBoardEmpty();
  //string letterForRows(int rowNumber);

  vector<vector<Tile*> > tilesOnBoard;

  int getRows();

  int getCols();

  int rows = 0;
  int cols = 0;

  bool isFirstTilePlaced;
};

#endif
