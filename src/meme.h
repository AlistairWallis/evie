#ifndef MEME_H
#define MEME_H
#include"world.h"

//do genome comparison
void meme(world* theworld);
void meme(world* theworld, int colour);

//show highest killer and highest cloner
void stat(world* theworld);
//show demographics of particular colour
void demo(world* theworld, int colour);
//show detailed genome comparison of particular colour
void schem(world* theworld, int colour);
//kill all animals of a particular colour
void kill(world* theworld,int colour);
void killall(world *theworld);

#endif
