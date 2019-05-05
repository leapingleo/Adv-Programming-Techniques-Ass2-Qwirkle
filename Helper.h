#include <iostream>
#include "Tile.h"

std::string letterForRows(int rowNumber);

void printError(std::string s);

std::string getInput(std::string s);

int letterToInt(std::string rowLetter);

bool isWithinBound(int atRow, int atCol, int maxRows, int maxCols);

bool isSameColour(Tile* tile1, Tile* tile2);
