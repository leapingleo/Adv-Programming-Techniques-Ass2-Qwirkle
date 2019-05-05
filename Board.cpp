#include "Board.h"

Board::Board(int rows, int cols){
  this->rows = rows;
  this->cols = cols;

  tilesOnBoard = vector<vector<Tile*> > (rows, vector<Tile*>(cols));
  isFirstTilePlaced = false;
}

//store the tile into the 2d vector at index row, col
void Board::store(Tile* tile, int row, int col){
  if (tilesOnBoard[row][col] == nullptr) {
     //if placed at the edge of the board, resize the 2d vector by 1
     if (cols - col == 1) {
       cols += 1;

       for (int i = 0; i < rows; i++)
         tilesOnBoard[i].resize(cols);
     } else if (rows - row == 1){
       rows += 1;
       tilesOnBoard.resize(rows, vector<Tile*>(cols));
     }
    tilesOnBoard[row][col] = tile;

    if (!isFirstTilePlaced)
      isFirstTilePlaced = true;
  }
}

string Board::boardBodyToString(){
  string s = "";

  for (int i = 0; i < tilesOnBoard.size(); i++){
    //conver row number to letters
    s += letterForRows(i) + " |";
    for (int j = 0; j < tilesOnBoard[i].size(); j++){
      if (tilesOnBoard[i][j] != nullptr)
        s += tilesOnBoard[i][j]->toString() + "|";
      else{
        s += "  |";
      }
    }
    s += "\r\n";
  }
  return s;
}

string Board::boardHeaderToString(){
  string s = "   ";
  int numOfDashesToPrint = cols * 3 + 1;

  //first row of the board, 1, 2, 3, 4, ...
  for (int i = 0; i < cols; i++){
    if (i < 10)
      s += std::to_string(i) + "  ";
    else
      s += std::to_string(i) + " ";
  }

  //second row of the board, dashes
  s += "\r\n  ";
  for (int i = 0; i < numOfDashesToPrint; i++){
    s += "-";
  }
  s += "\r\n";
  return s;
}

void Board::printBoard(){
  std::cout << boardHeaderToString();
  std::cout << boardBodyToString();
}

bool Board::isTileAlreadyAt(int row, int col){
  return tilesOnBoard[row][col] != nullptr;
}


bool Board::canPlace(int atRow, int atCol, Tile* tile){
  int leftward = -1;
  int rightward = 1;
  int upward = -1;
  int downward = 1;
  bool can = false;

//  std::cout << tile->getColour() << std::endl;
  if (tilesOnBoard[atRow][atCol - 1] != nullptr)
  std::cout << tilesOnBoard[atRow][atCol - 1]->getColour() << std::endl;

  if (!isFirstTilePlaced)
    can = true;

  if (checkHorizontalTiles(atRow, atCol - 1, tile, leftward))
    can = true;
  if (checkHorizontalTiles(atRow, atCol + 1, tile, rightward))
    can = true;
  if (checkVerticalTiles(atRow - 1, atCol, tile, upward))
    can = true;
  if (checkVerticalTiles(atRow + 1, atCol, tile, downward))
    can = true;

  return can;
}

bool Board::checkHorizontalTiles(int atRow, int atCol, Tile* tile, int direction){
  bool valid = false;

  if (atCol > 0 && atCol < cols)
    while (tilesOnBoard[atRow][atCol] != nullptr) {
      if (tilesOnBoard[atRow][atCol]->getColour() == tile->getColour()
          && tilesOnBoard[atRow][atCol]->getShape() != tile->getShape()) {

          valid = true;
        }
      atCol += direction;
  }
  return valid;
}

bool Board::checkVerticalTiles(int atRow, int atCol, Tile* tile, int direction){
  bool valid = false;

  if (atRow > 0 && atRow < rows) {
    while (tilesOnBoard[atRow][atCol] != nullptr) {
      if (tilesOnBoard[atRow][atCol]->getColour() != tile->getColour()
          && tilesOnBoard[atRow][atCol]->getShape() == tile->getShape()) {
            valid = true;
          }
      atRow += direction;
  }
}
  return valid;
}

vector<vector<Tile*> > Board::getTilesOnBoard(){
  return tilesOnBoard;
}

int Board::getRows(){
  return rows;
}

int Board::getCols(){
  return cols;
}

bool Board::isFirstTileOnBoard(){
  return isFirstTilePlaced;
}
