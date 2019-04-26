#include<iostream>
#include<fstream>
#include "LinkedList.h"
#include "Player.h"

using namespace std;

class Save{
public:

    void saveGame(LinkedList* p1Hand, LinkedList* p2Hand, LinkedList* tileBag, string p1Name, string p2Name, int p1Score, int p2Score, string board, string boardBody, string filename);
    void loadGame();


    
};