#include "stat.h"

#include<stdlib.h>
#include<stdio.h>

stat::stat()
{
  population[0]=0;
  population[1]=0;
  population[2]=0;
  pop=0;
  energy=0;
  grass_tiles=0;
  carrion_tiles=0;
  grass_coverage=0.0f;
  carrion_coverage=0.0f;
  clones=0;
  kills=0;
}

void stat::reset()
{
  grass_tiles=0;
  carrion_tiles=0;
  population[0]=0;
  population[1]=0;
  population[2]=0;
  pop=0;
  energy=0;
  clones=0;
  kills=0;
}

void stat::update(animal *change)
{
  if (change->alive)
	{		
		if (change->vore==0){population[0]+=1;}
	  	else if (change->vore==9){population[2]+=1;}
	  	else {population[1]+=1;}
                pop++;
                energy+=change->size;
	}
  else
	{
                if (change->vore==0){population[0]-=1;}
                else if (change->vore==9){population[2]-=1;}
                else {population[1]-=1;}
                pop--;
                energy-=change->size;
        }

}


void stat::print()
{
  printf("Population: %d\n",pop);
  printf("Herbivores: %d\n",population[0]);
  printf("Omnivores:  %d\n",population[1]);
  printf("Carnivores: %d\n",population[2]);
}

void stat::display()
{
}
