#include "LinkedList.h"
#include "Tile.h"
#include "Player.h"
#include "Board.h"
#include <iostream>
#include <fstream>

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

private:
  Board* board;
  Player* player1;
  Player* player2;
  std::string currentPlayerName;
  LinkedList* list;
  bool gameOver;
};
