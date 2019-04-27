#include "Board.h"
#include "Helper.h"

Board::Board(int rows, int cols){
  this->rows = rows;
  this->cols = cols;

  tilesOnBoard = vector<vector<Tile*> > (rows, vector<Tile*>(cols));

}

//store the tile into the 2d vector at index row, col
void Board::store(Tile* tile, int row, int col){
  if (tilesOnBoard[row][col] == nullptr) {
     if (cols - col == 1) {
       cols += 1;
       for (int i = 0; i < rows; i++)
        tilesOnBoard[i].resize(cols);
     } else if (rows - row == 1){
       rows += 1;
       tilesOnBoard.resize(rows, vector<Tile*>(cols));
     }
    // tilesOnBoard.resize(rows, vector<Tile*>(cols));
    tilesOnBoard[row][col] = tile;
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

int Board::getRows(){
  return rows;
}

int Board::getCols(){
  return cols;
}

void Board::printBoard(){
  std::cout << boardHeaderToString();
  std::cout << boardBodyToString();
}

bool Board::isTileAlreadyAt(int row, int col){
  return tilesOnBoard[row][col] != nullptr;
}
