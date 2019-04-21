#include "TileCodes.h"

char converToColour(int n){
  char colour = RED;

  if (n == 0)
    colour = RED;
  else if (n == 1)
    colour = ORANGE;
  else if (n == 2)
    colour = YELLOW;
  else if (n == 3)
    colour = GREEN;
  else if (n == 4)
    colour = BLUE;
  else if (n == 5)
    colour = PURPLE;

  return colour;
}
