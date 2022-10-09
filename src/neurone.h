#ifndef NEURONE_H
#define NEURONE_H

#define NSTATES 2
#define NWEIGHTS 7
/* RGB,adult,NSTATES,threshold */
#define NGENESIZE 15
/* 1 for type, and 2 for each weight */

enum NeuroneType {STAY,LEFT,RIGHT,GO,EAT,CLONE,ATTACK,SPEED,STATE1,STATE2};

class neurone
{
 public:
  neurone();
  neurone(char *gene);
  ~neurone(){}

  float output(int sight,bool adult,float *state);
  float weight[NWEIGHTS];
  int type;
};

#endif




