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
using std::cin;

class Game{
public:

  Game();

  ~Game();

  void newGame(string name1, string name2);

  void generateRandomizedTileSet();

  void AIMove(vector<vector<Tile*> > boardTiles, Player* player);

  void save();

  void gameSetup();

  void play();

  void saveGame(LinkedList* p1Hand, LinkedList* p2Hand,
              string p1Name, string p2Name, int p1Score, int p2Score, string currentPlayer);

  void loadGame();

private:
  Board* board;
  LinkedList* tileBag;
  Player* player1;
  Player* player2;
  int boardRows = 8;
  int boardCols = 8;
  int scoreToGive = 0;
  std::string currentPlayerName;
  std::string filename;
  bool isQwirkle = false;

  bool isGameOver();

  bool matchHorizontalTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile, int direction);

  bool matchVerticalTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile, int direction);

  bool canPlace(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile);

  void makeAMove(Player* player);

  void displayInfo(Player* player);

  void givePlayerScore(Player* player);

  void placeTile(Tile* tile, int atRow, int atCol, Player* player);

  void replaceTile(std::string tileName, Player* player);

  void calculateScores(vector<vector<Tile*> > boardTiles, int atRow, int atCol);

  int countColTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction);

  int countRowTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction);

};
