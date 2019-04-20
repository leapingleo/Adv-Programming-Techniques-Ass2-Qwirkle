#include<iostream>
#include<fstream>

using namespace std;

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

void saveGame()
{
    string filename;
    cout << "Enter filename: " ;
    cin >> filename;
    cout << endl;
    ofstream ofile(filename);
    if(!ofile.fail()){
        ofile << "nameP1" << "\r\n" << endl;
        ofile << "scoreP1" << "\r\n" << endl;
        ofile << "char* tileP1[]" << "\r\n" << endl;
        ofile << "nameP2" << "\r\n" << endl;
        ofile << "scoreP2" << "\r\n" << endl;
        ofile << "char* tileP2[]" << "\r\n" << endl;
        ofile << "char* board[]" << "\r\n" << endl;
        ofile << "char* tileBags[]" << "\r\n" << endl;
        ofile << "which player" << "\r\n" << endl;
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
