//tile.cpp tile class member functions

#include "tile.h"
#include<stdlib.h>

tile::tile()
{
  panimal=NULL;
  terrain=ROCK;
}

tile::tile(int new_terrain)
{
  panimal=NULL;
  terrain=new_terrain;
 
}


int tile::get_colour()
{
  if (panimal && panimal->alive)
    {
      return panimal->colour;
    }
  else if (terrain==GRASS){return GRASS_COLOUR;}
  else if (terrain==ROCK){return ROCK_COLOUR;}
  else if (terrain==CARRION){ return CARRION_COLOUR;}
  return 0;
}
