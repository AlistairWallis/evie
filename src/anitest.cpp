#include"world.h"
#include"ioz.h"
#include<zlib.h>
#include<stdio.h>
#include<stdlib.h>

int main(int argc,char*argv[])
{
  world *pop=new world();
  if (argc<=1){printf("Usage:%s <filename>\n",argv[0]);exit(0);}

  printf("Loading %s\n",argv[1]);
  gzFile fptr=NULL;

  fptr=gzopen(argv[1],"rb");
  if (!fptr){printf("No such file %s\n",argv[1]);return -1;}

  if (!loadworld(fptr,pop)){printf("error loading %s\n",argv[1]);}
  else {printf("Loaded %s\n",argv[1]);}
  gzclose(fptr);
 
  printf("Age:%lu\n",pop->age);
  printf("mutation:%d\n",pop->mutation);
  printf("death_age:%d\n",pop->death_age);
  printf("grass_grow:%d\n",pop->grass_grow);
  printf("carrion_fade:%d\n",pop->carrion_fade);
  printf("pop:%d\n",pop->statistics.pop);
  printf("stay_cost:%f\n",pop->stay_cost);
  printf("turn_cost:%f\n",pop->turn_cost);
  printf("go_cost:%f\n",pop->go_cost);
  printf("bump_cost:%f\n",pop->bump_cost);
  printf("eat_cost:%f\n",pop->eat_cost);
  printf("clone_cost:%f\n",pop->clone_cost);
  printf("attack_cost:%f\n",pop->attack_cost);

  int s=pop->mapsize;
  int i;
  for (i=0;i<s*s;i++)
    {

      if (pop->myanimals[i].alive)
	{
//	  if (pop->myanimals[i].age==0)
	   {printf("i-%d\n",i);pop->myanimals[i].print();}
	}
    }
    
return 0;
}
