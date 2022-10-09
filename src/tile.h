#ifndef TILE_H
#define TILE_H

#include"animal.h"

//has terrain,colour
enum Terrain {ROCK,NOTHING,GRASS,CARRION};
#define GRASS_COLOUR 283
#define ROCK_COLOUR 333
#define CARRION_COLOUR 900

class tile
{
 public:
  tile();
  tile(int new_terrain);
  ~tile(){}
  int get_colour();  

  animal *panimal;

  float food;
  int terrain;
};

#endif
