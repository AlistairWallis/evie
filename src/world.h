#ifndef WORLD_H
#define WORLD_H

#define DEF_MAPSIZE          150

#define DEF_MUTATION        5000
#define DEF_ADDSUB_MUTATION   10
#define DEF_DEATH_AGE        500
#define DEF_GRASS_FOOD        60
#define DEF_MIN_SIZE         120
#define DEF_GRASS_GROW      6000
#define DEF_CARRION_FADE      0

#define DEF_STAY_COST       1.0f
#define DEF_TURN_COST       2.0f
#define DEF_GO_COST         2.0f
#define DEF_WORK_RATIO    300.0f
#define DEF_BUMP_COST       5.0f
#define DEF_EAT_COST        5.0f
#define DEF_CLONE_COST      2.0f 
#define DEF_ATTACK_COST     5.0f
#define DEF_STEAL_FOOD     false

#include"conf.h"
#include"tile.h"
#include"stat.h"


#ifndef NO_GRAPHICS
#include"graphics.h"

#endif
class world
{
 public:
  world();
  world(int size); /* total number of tiles == size*size */
  ~world();
  void reset();
  void set_terrain();
  void hills(int Nmountains,int maxsize,int minsize);
  void remove_hills();
  void respawn(int population);
 
  int step(); /* do timestep */
  void update_stats();
  void kill(animal *panimal);

  /* graphics */
#ifndef NO_GRAPHICS
  void openmain(int scale,char *name);
  void closemain();
  void displaymain();
  void openmini();
  void closemini();
  graphics gmain;
  graphics gmini;
  bool mainopen;
  bool miniopen;
#endif
  int mapsize;
  tile *mytiles;
  animal *myanimals;
  animal *testanimal;
  unsigned long int age;
  int mutation;
  int addsub_mutation;
  int death_age;
  int grass_food;
  int min_size;

  int grass_grow;
  int carrion_fade;

  float stay_cost;
  float turn_cost;
  float go_cost;
  float work_ratio;
  float bump_cost;
  float eat_cost;
  float clone_cost;
  float attack_cost;
  bool steal_food;

  int rocks;
  stat statistics;
};

#endif

