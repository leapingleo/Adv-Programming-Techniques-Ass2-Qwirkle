#include "Menu.h"
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;

Menu::Menu(){
  //getMenu();
}

void Menu::getMenu()
{
  std::string s = "Menu\n-----\n1. New Game\n2. Load Game\n3. Show student information\n4. Quit\nPlease Enter Your Choice: ";

  std::string choice = getInput(s);
  if(choice == "1") {
    Game* game = new Game();
    game->play();
  }
  else if (choice == "3") {
    getStudentInfo();
  } else {
    printError("Not valid! Please Re-enter your choice!");
    getMenu();
  }
}


void Menu::getStudentInfo()
{
  std::fstream file("test.txt",std::ios::in);

  if (!file.fail()) {
    while (!file.eof()) {
      string line;
      getline(file,line);

      if (file.tellg() > 0) {
        cout<<line;
        cout<<endl;
      }
    }
  }
  else
    cout <<"Can not open file"<<endl;

  file.close();
  getMenu();
}
