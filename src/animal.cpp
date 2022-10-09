#include"animal.h"
#include"tile.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<math.h>

animal::animal()
{
  //Nneurones=1+rand()%(MAXNEURONES-1);
  Nneurones=1+rand()%(STARTNEURONES);
  genomesize=(Nneurones*NGENESIZE)+CHARGENESIZE; /* rgb,adultsize,babysize */
  int i;
  for (i=0;i<genomesize;i++)
    {
      genome[i]=97+rand()%19;
      //if (i==9){genome[i]=106;} 
/*force all random animals to be herbivores
  carnivores can evolve later*/
    }
  /*random genome created, however, need to perform animate function for
    creature to be fully activated */
  number=0;
  colour=0;
  adultsize=0;
  babysize=0;
  size=0;
  vore=0;
  energy=0;
  speed=0;

  state[0]=0;
  state[1]=0;

  coords[0]=0;
  coords[1]=0;
  facing[0]=0;
  facing[1]=0;
  direction=0;
  alive=false;
  adult=false;
  age=0;
  Nclones=0;
  Nkills=0;
  Nsteals=0;
  lastSeen=0;
  lastAction=0;
}


void animal::animate(int x,int y,int d,int max)
{
  genomesize=(Nneurones*NGENESIZE)+CHARGENESIZE; /* rgb,adultsize,babysize */

  /* setup characteristics */
  colour=abs((genome[0]-106)*100)+abs((genome[1]-106)*10)+abs((genome[2]-106));
  babysize=abs((genome[3]-106)*100)+abs((genome[4]-106)*10)
    + abs((genome[5]-106));
  adultsize=abs((genome[6]-106)*100)+abs((genome[7]-106)*10)
    + abs((genome[8]-106));
  vore=abs((genome[9]-106));
  size=static_cast<float>(babysize);
  /* strip off network part of genome */
  char netgenome[genomesize-CHARGENESIZE];
  strncpy(netgenome,genome+CHARGENESIZE,genomesize-CHARGENESIZE);

  /* setup neurones */
  char neuronegene[NGENESIZE];
  for (int i=0;i<Nneurones;i++)
    {
      strncpy(neuronegene,(netgenome+(i*NGENESIZE)),NGENESIZE);
      network[i]=neurone(neuronegene);	
    }
  /* set coords */
  speed=0;
  state[0]=0;
  state[1]=0;
  coords[0]=x;coords[1]=y;
  direction=d;
  setfacing(coords,facing,direction,max);
  alive=true;
}


int animal::action(int sight)
{
  float h,v;
  h=-100;
  int highest=STAY;
  int type;
  for (int i=0;i<Nneurones;i++)
    {
      type=network[i].type;
      if (type<SPEED)
	{
	  v=network[i].output(sight,adult,state);
	  if (v>h){highest=type;h=v;}
	}
      else if (type==SPEED)
	{
	  speed=network[i].output(sight,adult,state);
	  if (speed>1){speed=1;}
	  else if (speed<-1){speed=-1;}
	}
      else if (type==STATE1)
	{
	  state[0]=network[i].output(sight,adult,state);
	  if (state[0]>1){state[1]=1;}
	  else if (state[0]<-1){state[0]=-1;}
	}
      else if (type==STATE2)
	{
	  state[1]=network[i].output(sight,adult,state);
	  if (state[1]>1){state[1]=1;}
	  else if (state[1]<-1){state[1]=-1;}
	}
    }
  lastAction=highest;
  lastSeen=sight;
  return (highest);
}

void animal::eat(float food,int terrain)
{
  if (terrain==CARRION)
    {
//      food/=10/(1+static_cast<float>(vore));
	food*=static_cast<float>(vore)/9;
    }
  else if (terrain==GRASS)
    {
//      food/=10/(10-static_cast<float>(vore));
	food*=(9-static_cast<float>(vore))/9;
    }
  energy+=food;
}

void animal::energy_budget()
{
  age++;
 
  size+=energy;
  energy=0;
  if (size>static_cast<float>(adultsize))
    {
      energy=size-static_cast<float>(adultsize);
      size=static_cast<float>(adultsize);
    }
   
  adult=false;
  if (size<static_cast<float>(babysize)){alive=false;}
  else if (size>=static_cast<float>(adultsize)){adult=true;}
}

void animal::print()
{
  int i;
  printf("\n Number:%d",number);
  printf("\n X:%d, Y:%d",coords[0],coords[1]);
  printf("\nfX:%d,fY:%d",facing[0],facing[1]);
  printf("\ndir:%d\n",direction);

  if (alive){printf("alive\n");}
  else {printf("dead\n");}
  if (adult){printf("adult\n");}
  else {printf("baby\n");}

  printf("Age: %d\n",age);
  printf("Colour:%d\n",colour);

  printf("adultsize:%d\n",adultsize);
  printf("babysize:%d\n",babysize);
  printf("vore:%d\n",vore);
  
  printf("size:%f\n",size);
  printf("speed:%f\n",speed);
  printf("state[0]:%f\n",state[0]);
  printf("state[1]:%f\n",state[1]);
  printf("Nneurones:%d\n",Nneurones);
  int t;
  for (i=0;i<Nneurones;i++)
    {
      t=network[i].type;
      switch(t)
	{
	case STAY:
	  printf("S");
	  break;
	case RIGHT:
	  printf("R");
	  break;
	case LEFT:
	  printf("L");
	  break;
	case GO:
	  printf("G");
	  break;
	case EAT:
	  printf("E");
	  break;
	case CLONE:
	  printf("C");
	  break;
	case ATTACK:
	  printf("K");
	  break;
	case SPEED:
	  printf("V");
	  break;
	case STATE1:
	  printf("1");
	  break;
	case STATE2:
	  printf("2");
	  break;
	default:
	  printf("?");
	}
    }
  printf("\n");
  for (i=0;i<genomesize;i++){printf("%c",genome[i]);}
  printf("\n");
  printf("Nclones:%d\t Nsteals:%d\t Nkills:%d\n",Nclones,Nsteals,Nkills);
}
