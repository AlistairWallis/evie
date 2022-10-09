#ifndef STAT_H
#define STAT_H

#include"animal.h"

class stat
{
 public:
  stat();
  ~stat(){}
  void reset();
  void print();
  void display();
  void update(animal *change);

  int population[3]; // 3 different pops for herni,omni, & carni
  int pop;
  double energy;
  int grass_tiles;
  int carrion_tiles;
  float grass_coverage;
  float carrion_coverage;
  int clones;
  int kills;

};

#endif
