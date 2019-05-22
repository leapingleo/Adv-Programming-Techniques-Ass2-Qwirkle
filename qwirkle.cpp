#include "Menu.h"
#define EXIT_SUCCESS 0

int main(void) {
  Menu* menu = new Menu();
  menu->showMenu();

  delete menu;

  return EXIT_SUCCESS;
}
