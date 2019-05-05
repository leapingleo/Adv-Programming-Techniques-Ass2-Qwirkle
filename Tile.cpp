
#include "Tile.h"

Tile::Tile(Colour colour, Shape shape){
  this->colour = colour;
  this->shape = shape;
}

std::string Tile::toString(){
  return colour + std::to_string(shape);
}

Colour Tile::getColour(){
  return colour;
}

Shape Tile::getShape(){
  return shape;
}
