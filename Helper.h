#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <stdlib.h>
#include <chrono>
#include <thread>
#include <time.h>
#include "Tile.h"

std::string letterForRows(int rowNumber);

void printError(std::string s);

std::string getInput(std::string s);

int letterToInt(std::string rowLetter);

bool isWithinBound(int atRow, int atCol, int maxRows, int maxCols);

bool isSameColour(Tile* tile1, Tile* tile2);

std::vector<int> randomSet(int min, int max);
