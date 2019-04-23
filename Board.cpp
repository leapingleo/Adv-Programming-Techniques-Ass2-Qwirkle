#include "Board.h"

Board::Board(){
  rows = 6;
  cols = 6;

  boardRows = vector<vector<Tile*> > (rows, vector<Tile*>(cols));
}

//store the tile into the 2d vector at index row, col
void Board::store(Tile* tile, int row, int col){
  if (boardRows[row][col] == nullptr)
    boardRows[row][col] = tile;
}

string Board::boardBodyToString(){
  string s = "";

  for (int i = 0; i < row; i++){
    //conver row number to letters
    s += letterForRows(i) + " |";
    for (int j = 0; j < col; j++){
      //retrieve the tile from the vector at index (i,j)
      if (boardRows[i][j] != nullptr)
        s += boardRows[i][j]->toString() + "|";
      else{
        s += "  |";
      }
    }
    s += "\n";
  }
  return s;
}


string Board::boardHeaderToString(int rows){
  string s = "   ";
  int numOfDashesToPrint = rows * 3 + 1;

  //first row of the board, 1, 2, 3, 4, ...
  for (int i = 0; i < rows; i++){
    s += std::to_string(i) + "  ";
  }

  //second row of the board, dashes
  s += "\n  ";
  for (int i = 0; i < numOfDashesToPrint; i++){
    s += "-";
  }
  s += "\n";
  return s;
}

string Board::letterForRows(int rowNumber){
  string s = "";

  if (rowNumber == 0)
    s = "A";
  else if (rowNumber == 1)
    s = "B";
  else if (rowNumber == 2)
    s = "C";
  else if (rowNumber == 3)
    s = "D";
  else if (rowNumber == 4)
    s = "E";
  else if (rowNumber == 5)
    s = "F";
  else if (rowNumber == 6)
    s = "G";
  else if (rowNumber == 7)
    s = "H";
  else if (rowNumber == 8)
    s = "I";
  else if (rowNumber == 9)
    s = "J";
  else if (rowNumber == 10)
    s = "K";
  else if (rowNumber == 11)
    s = "L";
  else if (rowNumber == 12)
    s = "M";
  else if (rowNumber == 13)
    s = "N";
  else if (rowNumber == 14)
    s = "O";
  else if (rowNumber == 15)
    s = "P";

  return s;
}

int Board::getRows(){
  return rows;
}

int Board::getCols(){
  return cols;
}
