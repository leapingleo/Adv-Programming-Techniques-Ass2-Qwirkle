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

  ~Game();

  void save();

  void gameSetup();

  void play();

  void makeAMove(Player* player);

  void gamePlay(Player* player);

  void displayInfo(Player* player);

  void placeTile(Tile* tile, int atRow, int atCol, Player* player);

  void replaceTile(std::string tileName, Player* player);

  void saveGame(LinkedList* p1Hand, LinkedList* p2Hand, string p1Name, string p2Name /*int p1Score, int p2Score, */);

  void loadGame();

  bool matchHorizontalTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile, int direction);

  bool matchVerticalTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile, int direction);

  bool canPlace(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile);

private:
  Board* board;
  int boardRows = 6;
  int boardCols = 6;
  Player* player1;
  Player* player2;
  std::string currentPlayerName;
  LinkedList* tileBag;
  bool gameOver;
  std::string filename;
};
