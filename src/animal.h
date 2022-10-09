#ifndef ANIMAL_H
#define ANIMAL_H

#include"neurone.h"
#define STARTNEURONES 10
#define MAXNEURONES 20
#define CHARGENESIZE 10
#define MAXGENOMESIZE() (MAXNEURONES*NGENESIZE)+CHARGENESIZE
/* set coords of facing tile */
void inline setfacing(int *cd,int *fc,int dir,int max)
{
  fc[0]=cd[0];
  fc[1]=cd[1];
  if (dir==0){fc[1]++;}
  else if (dir==1){fc[0]++;}
  else if (dir==2){fc[1]--;}
  else if (dir==3){fc[0]--;}
  if (fc[0]<0){fc[0]+=max;}
  else if (fc[0]>=max){fc[0]-=max;}
  if (fc[1]<0){fc[1]+=max;}
  else if (fc[1]>=max){fc[1]-=max;}
}


class animal
{
 public:
  animal();
  ~animal(){}
  void animate(int x,int y,int d,int max);
  int action(int sight); /* sight is colour of facing tile */
  void left(int max)
  {
    direction--;
    if (direction<0){direction=3;}
    setfacing(coords,facing,direction,max);
  }
  void right(int max)
  {
    direction++;
    if (direction>3){direction=0;}
    setfacing(coords,facing,direction,max);
  }
  void go(int max)
  {
    coords[0]=facing[0];
    coords[1]=facing[1];
    setfacing(coords,facing,direction,max);
  }

  void eat(float food,int terrain);

  void energy_budget();

  void print();

  /*animal data*/
  int number;
  int coords[2];/* {xcoord,ycoord} */
  int facing[2];/* coords of facing tile */
  int direction;
  //
  bool alive;
  bool adult;   /* true when size >= adultsize . When true cloning can occur */
  int age;
  int colour;   /* 001 to 999 */
  //
  float energy; /* i.e. amount of food stored */
  float size;  
  //
  float speed;  /* 0.0 to 1.0 */ 
  //
  int adultsize;
  int babysize;
  int vore; /* 0-9 0==pure herbivore, 9==pure carnivore */
  //
  /*colour, adultsize, babysize, vore: characteristics chromosome (10 digits)*/
  int Nneurones;
  int genomesize;
  char genome[MAXGENOMESIZE()]; 
  neurone network[MAXNEURONES]; 
  /* collection of Nneurones neurones to make up network */
  float state[NSTATES]; /*NSTATES dictated by neurone class*/
  //
  /*statistics*/
  int Nclones;
  int Nkills;
  int Nsteals;
  int lastSeen;
  int lastAction;
};



#endif
