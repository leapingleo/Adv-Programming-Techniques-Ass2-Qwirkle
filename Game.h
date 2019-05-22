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

  //set up a new game with players, tile bags, and dive into play
  void newGame(string name1, string name2);

  void save();

  //set up the game, set up a randomized tile bag and assign 6 tiles to each player
  void gameSetup();

  void play();

  void saveGame(LinkedList* p1Hand, LinkedList* p2Hand, string p1Name,
                string p2Name, int p1Score, int p2Score, string currentPlayer);

  void loadGame();

  ////A.I trigger to call AIMove in play()
  void turnOnAI();

private:
  Board* board;
  LinkedList* tileBag;
  Player* player1;
  Player* player2;
  int boardRows = 6;
  int boardCols = 6;
  int scoreToGive = 0;
  std::string currentPlayerName;
  std::string filename;
  bool isQwirkle = false;
  bool isEarlyTermination = false;
  bool playingWithAI = false;
  bool exitDuringGame = false;
  bool noMorePossibleMoves = false;

  /* return one of the end game condition, i.e no more tiles in the bag,
     one player got no more tiles */
  bool isGameOver();

  /* check if a to-be-placed tile matching horizontal and vertical tiles around it
     also checks if the tiles on its left and tiles on its right are all unique
     and same for tiles on its above and the tiles below it  */
  bool isMatchingTilesAround(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile);

  /* check if a tile can be placed based on the rules, it calls isMatchingTilesAround() for
     further validation */
  bool canPlace(vector<vector<Tile*> > boardTiles, int atRow, int atCol, Tile* tile);

  /* tiles generated through the number representation. e.g "1" represents ORANGE
    and CIRCLE.
    each distinct shape and color is both represented by an integer
    1. generate 36 different randomized "integer" strings(color + shape),
       and put them into a string vector
    2. futhur randomization(shuffle) for the string vector
    3. retrieve and parse each string element to integer color and shape,
       and add each to the tile bag
    **The usual nestted for-loop generates a randomized but predictable pattern,
      i.e. each outter loop produces same integer with inner loop, e.g 12, 13, 14, 16, 15, 11 */
  void generateRandomizedTileSet();

  /* The AI stores all possible moves, and choose one and make a move
     it also can replace a tile where there's no possible moves */
  void AIMove(vector<vector<Tile*> > boardTiles, Player* player);

  //read and validate a command, and turn it into an action
  void makeAMove(Player* player);

  //display player scores and print the board
  void displayInfo(Player* player);

  //assginment scores to the player
  void givePlayerScore(Player* player);

  //place a tile
  void placeTile(Tile* tile, int atRow, int atCol, Player* player);

  //replace a tile for player
  void replaceTile(std::string tileName, Player* player);

  /* counting the number of tiles around the spot the player placed a tile, and
     add up scores */
  void calculateScores(vector<vector<Tile*> > boardTiles, int atRow, int atCol);

  //show final scores and winner annoucement
  void showResult();

  //count the number of tiles horizontally at a spot
  int countColTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction);

  //count the number of tiles vertically at a spot
  int countRowTiles(vector<vector<Tile*> > boardTiles, int atRow, int atCol, int direction);

};
