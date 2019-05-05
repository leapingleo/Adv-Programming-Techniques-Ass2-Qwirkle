#ifndef ASSIGN2_BOARD_H
#define ASSIGN2_BOARD_H


#include "Tile.h"
#include "Helper.h"
#include <iostream>
#include <vector>


using std::vector;
using std::string;

class Board {
public:

  Board(int rows, int cols);

  bool canPlace(int atRow, int atCol, Tile* tile);

  void store(Tile* tile, int row, int col);

  void printBoard();

  string boardHeaderToString();

  string boardBodyToString();

  bool isTileAlreadyAt(int row, int col);

  bool isFirstTileOnBoard();


//  bool isBoardEmpty();


  int getRows();

  int getCols();

  vector<vector<Tile*> > getTilesOnBoard();

  bool checkHorizontalTiles(int atRow, int atCol, Tile* tile, int direction);

  bool checkVerticalTiles(int atRow, int atCol, Tile* tile, int direction);

private:
  int rows = 0;
  int cols = 0;
  vector<vector<Tile*> > tilesOnBoard;
  bool isFirstTilePlaced;
};

#endif
