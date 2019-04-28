#include "Game.h"

Game::Game(){
  board = new Board(boardRows, boardCols);

  player1 = new Player("Leo");
  player2 = new Player("Tomas");
  tileBag = new LinkedList();
  gameOver = false;
  currentPlayerName = player1->getName();
  gameSetup();
}

void Game::gameSetup(){
  //initialize the tile bag, not randomized just yet!
  for (int i = 1; i < 7; i++)
    for (int j = 0; j < 6; j++)
      tileBag->add(new Tile(converToColour(j), i));

  //Player 1 get 6 tiles
  for (int i = 0; i < 6; i++){
    player1->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
  //Player 2 get 6 tiles
  for (int i = 0; i < 6; i++){
    player2->addTiles(tileBag->getNext()->getTile());
    tileBag->deleteFront();
  }
}

void Game::play(){
  while (!gameOver) {
    if (currentPlayerName == player1->getName()){
      displayInfo(player1);
      makeAMove(player1);
      currentPlayerName = player2->getName();
    } else {
      displayInfo(player2);
      makeAMove(player2);
      currentPlayerName = player1->getName();
    }
  }
}

void Game::displayInfo(Player* player){
  cout << player->getName() << ", it's your turn" << std::endl;
  board->printBoard();
  cout << endl;
  player->showTilesOnHand();
  cout << endl;
}

void Game::makeAMove(Player* player){
  std::string command = getInput("> ");
  transform(command.begin(),command.end(),command.begin(),::toupper);
  //get row and col from player's command

  if (command.substr(0, 5) == "PLACE"){
    //PLACE XX AT XX
    std::string tileName = command.substr(6,2);
    int placeAtRow = letterToInt(command.substr(12,1));
    int placeAtCol = std::stoi(command.substr(13,2));

    if (player->getTilesOnHand()->has(tileName)) {
      Tile* tileToPlace = player->findTile(tileName);

      if (isWithinBound(placeAtRow, placeAtCol, board->getRows(), board->getCols())
      && !board->isTileAlreadyAt(placeAtRow, placeAtCol)){
          if (board->canPlace(placeAtRow, placeAtCol))
            placeTile(tileToPlace, placeAtRow, placeAtCol, player);
          else {
            printError("NOT A VALID MOVE! TRY AGAIN!");
            makeAMove(player);
          }
      } else {
        printError("SPOT NOT AVAILABLE! TRY AGAIN!");
        makeAMove(player);
      }
    } else {
      printError("YOU DON'T HAVE THAT TILE, DO YOU???");
      makeAMove(player);
    }
  }
  else if (command.substr(0, 7) == "REPLACE"){
    std::string tileToReplace = command.substr(8,2);

    if (player->getTilesOnHand()->has(tileToReplace)) {
      replaceTile(tileToReplace, player);
    } else {
      printError("ARE YOU SURE YOU HAVE THIS TILE???");
      makeAMove(player);
    }
  } 
  else if (command.substr(0, 4) == "SAVE"){
    filename = command.substr(5);
    filename += ".txt";
    saveGame(player1->getTilesOnHand(), player2->getTilesOnHand(), player1->getName(), player2->getName() );
  }
  
  
  else {
    printError("INVALID INPUT.");
    makeAMove(player);
  }
}

void Game::replaceTile(std::string tileName, Player* player){
  player->removeTile(tileName);
  player->addTiles(tileBag->getNext()->getTile());
  tileBag->deleteFront();
  cout << std::endl;
}

void Game::placeTile(Tile* tile, int atRow, int atCol, Player* player){
  player->removeTile(tile->toString());
  //draw a new tile
  player->addTiles(tileBag->getNext()->getTile());
  //delete the withdrawn tile, which is always the head tile/node
  tileBag->deleteFront();
  board->store(tile, atRow, atCol);
  cout << std::endl;
}

void Game::saveGame(LinkedList* p1Hand, LinkedList* p2Hand, string p1Name, string p2Name /*int p1Score, int p2Score, */)
{
    std::string fullBoard = board->boardHeaderToString();
    fullBoard += board->boardBodyToString();

    std::ofstream ofile(filename);
    if(!ofile.fail()){
        ofile << p1Name << "\r\n";
/*        ofile << p1Score << "\r\n"; 
*/
        Node* current = p1Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        
        }       

        ofile << p2Name << "\r\n";
/*        ofile << p2Score << "\r\n";
*/
        current = p2Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        
        }

        ofile << fullBoard << "\r\n";

        current = this->tileBag->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
            
        }
        

        ofile << "which player" << "\r\n"; 

        ofile.close();

        cout << "Game successfully saved" << endl;
    }
}