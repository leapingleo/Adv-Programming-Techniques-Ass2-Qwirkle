#include "Board.h"

Board::Board(){
  row = 6;
  col = 6;
}

void Board::store(Tile* tile){
  //board.push_back(tile);
}

string Board::boardBodyToString(){
  string s = "";

  for (int i = 0; i < row; i++){
    //conver row number to letters
    s += letterForRows(i) + " |";
    for (int j = 0; j < col; j++){
      s += "  |";
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
