#include <iostream>
#include <fstream>
#include "Helper.h"
#include "Game.h"

using std::cout;
using std::cin;

class Menu {
public:
   Menu();

   ~Menu();

   void showMenu();

   void getStudentInfo();

   bool isValidName(std::string name);

   std::string getPlayerNameInput(int n);
};
