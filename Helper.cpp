#include "Helper.h"

std::string letterForRows(int rowNumber){
  std::string s = "";

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
  else if (rowNumber == 16)
    s = "Q";
  else if (rowNumber == 17)
    s = "R";
  else if (rowNumber == 18)
    s = "S";
  else if (rowNumber == 19)
    s = "T";
  else if (rowNumber == 20)
    s = "U";
  else if (rowNumber == 21)
    s = "V";
  else if (rowNumber == 22)
    s = "W";
  else if (rowNumber == 23)
    s = "X";
  else if (rowNumber == 24)
    s = "Y";
  else if (rowNumber == 25)
    s = "Z";

  return s;
}

int letterToInt(std::string rowLetter){
   int n = 0;

   if (rowLetter == "A")
     n = 0;
   else if (rowLetter == "B")
     n = 1;
   else if (rowLetter == "C")
     n = 2;
   else if (rowLetter == "D")
     n = 3;
   else if (rowLetter == "E")
     n = 4;
   else if (rowLetter == "F")
     n = 5;
   else if (rowLetter == "G")
     n = 6;
   else if (rowLetter == "H")
     n = 7;
   else if (rowLetter == "I")
     n = 8;
   else if (rowLetter == "J")
     n = 9;
   else if (rowLetter == "K")
     n = 10;
   else if (rowLetter == "L")
     n = 11;
   else if (rowLetter == "M")
     n = 12;
   else if (rowLetter == "N")
     n = 13;
   else if (rowLetter == "O")
     n = 14;
   else if (rowLetter == "P")
     n = 15;
   else if (rowLetter == "Q")
     n = 16;
   else if (rowLetter == "R")
     n = 17;
   else if (rowLetter == "S")
     n = 18;
   else if (rowLetter == "T")
     n = 19;
   else if (rowLetter == "U")
     n = 20;
   else if (rowLetter == "V")
     n = 21;
   else if (rowLetter == "W")
     n = 22;
   else if (rowLetter == "X")
     n = 23;
   else if (rowLetter == "Y")
     n = 24;
   else if (rowLetter == "Z")
     n = 25;

   return n;
}

void printError(std::string s){
  std::cout << s << std::endl;
  std::cout << std::endl;
}

std::string getInput(std::string s){
  std::string output = "";

  std::cout << s;
  std::getline(std::cin, output);

  return output;
}

bool isWithinBound(int atRow, int atCol, int maxRows, int maxCols){
  return atRow < maxRows && atCol < maxCols;
}

bool isSameColour(Tile* tile1, Tile* tile2){

  return tile1->getColour() == tile2->getColour()
         && tile1 != nullptr && tile2 != nullptr;
}
