#include<iostream>
#include<fstream>

using namespace std;

void saveGame(int argc, char* argv[])
{
    string filename;
    ofstream ofile;
    cout << "Enter filename: " ;
    cin >> filename;
    cout << endl;
    ofile.open(filename);
    if(!ofile.fail()){
        ofile << "nameP1" << "\n";
        ofile << "scoreP1" << "\n";
        ofile << "char* tileP1[]" << "\n";
        ofile << "nameP2" << "\n";
        ofile << "scoreP2" << "\n";
        ofile << "char* tileP2[]" << "\n";
        ofile << "char* board[]" << "\n";
        ofile << "char* tileBags[]" << "\n";
        ofile << "which player" << "\n";
        ofile.close();
    }
}

void loadGame(){
    
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

struct stockType{
    string nameP1;
    int scoreP1;
    char tileP1[];
    string nameP2;
    int scoreP2;
    char tileP2[];
    char board;
    char tileBags[];
    
    
}
