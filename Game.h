#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include "Helper.h"
#include <iostream>
#include <fstream>
#include <algorithm>

using std::cout;
using std::endl;

class Game{
public:

  Game();

  void save();

  void gameSetup();

  void play();

  void makeAMove(Player* player);

  void gamePlay(Player* player);

  void displayInfo(Player* player);

  void placeTile(Tile* tile, int atRow, int atCol, Player* player);

  void replaceTile(std::string tileName, Player* player);
private:
  Board* board;
  int boardRows = 6;
  int boardCols = 6;
  Player* player1;
  Player* player2;
  std::string currentPlayerName;
  LinkedList* tileBag;
  bool gameOver;
};
