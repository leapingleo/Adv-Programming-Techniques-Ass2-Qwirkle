#include "Menu.h"
#include <iostream>
#include <fstream>

using std::cin;
using std::cout;
using std::endl;
using std::string;

Menu::Menu(){
  //getMenu();
}

Menu::~Menu(){
}

void Menu::showMenu()
{
  cout << "Menu" << endl;
  cout << "-----" << endl;
  cout << "1. New Game" << endl;
  cout << "2. Load Game" << endl;
  cout << "3. Show Student Information" << endl;
  cout << "4. Quit" << endl;
  cout << "5. New Game with A.I (Artificial Incompetence)" << endl;
  cout << endl;

  std::string choice = getInput("> ");
  if(choice  == "1") {
    cout << "Starting a New Game" << endl;
    cout << endl;
    string name1 = getPlayerNameInput(1);
    string name2 = getPlayerNameInput(2);

    cout << "Let's Play!\n" << endl;
    Game* game = new Game();
    game->newGame(name1, name2);

    delete game;
  }
  else if (choice == "2") {
    Game* game = new Game();
    game->loadGame();

    delete game;
  }
  else if (choice == "3") {
    getStudentInfo();
    showMenu();
  }
  else if (choice == "4") {
    cout << "GoodBye" << endl;
  }
  else if (choice == "5") {
    Game* game = new Game();
    game->turnOnAI();

    string name1 = getPlayerNameInput(1);
    game->newGame(name1, "Artificial Incompetence");
    delete game;
  }
  else {
    printError("Not valid! Please Re-enter your choice!");
    showMenu();
  }
}

void Menu::getStudentInfo()
{
  std::fstream file("studentInfo.txt",std::ios::in);

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
  showMenu();
}

bool Menu::isValidName(std::string name) {
  bool valid = true;

  if (name != ""){
    for (char c: name)
      if ((!isalpha(c) || !isupper(c)))
        valid = false;
  }
  else
    valid = false;

  return valid;
}

std::string Menu::getPlayerNameInput(int n) {
  string name = "";
  do {
    cout << "Enter a name for player " << n << " (uppercase characters only)" << endl;
    name = getInput("> ");
  } while (!isValidName(name));
  cout << endl;

  return name;

}
