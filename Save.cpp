#include "Save.h"

struct stockType{
    string nameP1;
    int scoreP1;
    string nameP2;
    int scoreP2;
    char tileP2;
    char board;
    char tileBags;
    char tileP1;
};


void Save::saveGame(LinkedList* p1Hand, LinkedList* p2Hand, LinkedList* tileBag, string p1Name, string p2Name, int p1Score, int p2Score, string boardHead, string boardBody, string filename)
{
    ofstream ofile(filename);
    if(!ofile.fail()){
        ofile << p1Name << "\r\n";
        ofile << p1Score << "\r\n"; 

        Node* current = p1Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        
        }       

        ofile << p2Name << "\r\n";
        ofile << p2Score << "\r\n";

        current = p2Hand->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            current = current->next;
        
        }

        ofile << boardHead << boardBody << "\r\n";

        current = tileBag->getHead();
        while(current != nullptr){
            if(current -> next != nullptr)
                ofile << current->getTile()->toString() << ", ";
            else
                ofile << current->getTile()->toString() << "\r\n";
            
        }
        

        ofile << "which player" << "\r\n"; 

        ofile.close();
    }
}

void Save::loadGame(){
    
    int index;
    string filename;
    stockType load[9];
    cout << "Enter filename: " ;
    cin >> filename;
    cout << endl;
    ifstream infile(filename);
    for(index = 0; index < 9; index++){
        infile >> load[index].nameP1;
        infile >> load[index].scoreP1;
        infile >> load[index].tileP1;
        infile >> load[index].nameP2;
        infile >> load[index].scoreP2;
        infile >> load[index].tileP2;
        infile >> load[index].board;
        infile >> load[index].tileBags;
    }
    

}
