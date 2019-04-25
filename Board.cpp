#include "Board.h"

Board::Board(){
  rows = 6;
  cols = 6;

  boardRows = vector<vector<Tile*> > (rows, vector<Tile*>(cols));

}

//store the tile into the 2d vector at index row, col
void Board::store(Tile* tile, int row, int col){
  if (boardRows[row][col] == nullptr) {
     if (cols - col == 1) {
       cols += 1;
       for (int i = 0; i < rows; i++)
        boardRows[i].resize(cols);
     } else if (rows - row == 1){
       rows += 1;
       boardRows.resize(rows, vector<Tile*>(cols));
     }
    // boardRows.resize(rows, vector<Tile*>(cols));
    boardRows[row][col] = tile;
  }
  // for (int i = 0; i < boardRows.size(); i++){
  //   //conver row number to letters
  //   std::cout << letterForRows(i) << " |";
  //   for (int j = 0; j < boardRows[i].size(); j++){
  //     if (boardRows[i][j] != nullptr)
  //       std::cout << boardRows[i][j]->toString() << "|";
  //     else{
  //       std::cout << "  |";
  //     }
  //   }
  //   std::cout << std::endl;
  // }
}

string Board::boardBodyToString(){
  string s = "";

  for (int i = 0; i < boardRows.size(); i++){
    //conver row number to letters
    s += letterForRows(i) + " |";
    for (int j = 0; j < boardRows[i].size(); j++){
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


string Board::boardHeaderToString(){
  string s = "   ";
  int numOfDashesToPrint = cols * 3 + 1;

  //first row of the board, 1, 2, 3, 4, ...
  for (int i = 0; i < cols; i++){
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

void Board::printBoard(){
  std::cout << boardHeaderToString();
  std::cout << boardBodyToString();
}
