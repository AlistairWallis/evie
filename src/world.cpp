#include "world.h"
#include "clone.h"

#include<stdlib.h>
#include<stdio.h>
#include<math.h>

world::world()
{
#ifdef DEBUG
  fprintf(stderr,"world::world()\n");
#endif
  mapsize=DEF_MAPSIZE;
//  mytiles=(tile*)calloc(mapsize*mapsize,sizeof(tile));
mytiles=(tile*)malloc(mapsize*mapsize*sizeof(tile));
//  myanimals=(animal*)calloc(mapsize*mapsize,sizeof(animal));
myanimals=(animal*)malloc(mapsize*mapsize*sizeof(animal));
  if (mytiles==NULL || myanimals==NULL){printf("Out of memory!\n");exit(0);}
#ifdef DEBUG
  fprintf(stderr,"malloc(%d * %11d) = 0x%016x\n",mapsize*mapsize,sizeof(tile));
  fprintf(stderr,"malloc(%d * %11d) = 0x%016x\n",mapsize*mapsize,sizeof(animal));
#endif

  for (int i=0;i<mapsize*mapsize;i++)
    {
      mytiles[i]=tile();
      myanimals[i]=animal();
    }
  testanimal=NULL;
  age=0;

#ifndef NO_GRAPHICS
  mainopen=false;
  miniopen=false;
#endif
  rocks=0;
  statistics=stat();
}

world::world(int size)
{
#ifdef DEBUG
  fprintf(stderr,"world::world(%d)\n",size);
#endif
  mapsize=size;
  //mytiles=(tile*)calloc(mapsize*mapsize,sizeof(tile));
mytiles=(tile*)malloc(mapsize*mapsize*sizeof(tile));
  //myanimals=(animal*)calloc(mapsize*mapsize,sizeof(animal));
myanimals=(animal*)malloc(mapsize*mapsize*sizeof(animal));
  if (mytiles==NULL || myanimals==NULL){printf("Out of memory!\n");exit(0);}
#ifdef DEBUG
  fprintf(stderr,"malloc(%d * %11d) = 0x%016x\n",mapsize*mapsize,sizeof(tile),mytiles);
  fprintf(stderr,"malloc(%d * %11d) = 0x%016x\n",mapsize*mapsize,sizeof(animal),myanimals);
#endif
  for (int i=0;i<mapsize*mapsize;i++)
    {
      mytiles[i]=tile();
      myanimals[i]=animal();
    }
  testanimal=NULL;
  age=0;

#ifndef NO_GRAPHICS
  mainopen=false;
  miniopen=false;
#endif
  rocks=0;
  statistics=stat();
}

world::~world()
{
#ifdef DEBUG
  fprintf(stderr,"world::~world()\n");
  fprintf(stderr,"free(0x%016x)\n",mytiles);
  fprintf(stderr,"free(0x%016x)\n",myanimals);
#endif
  free(mytiles);
  mytiles=NULL;
  free(myanimals);
  myanimals=NULL;
  testanimal=NULL;
}

void world::reset()
{
#ifdef DEBUG
  fprintf(stderr,"world::reset()\n");
#endif
  mutation=DEF_MUTATION;
  addsub_mutation=DEF_ADDSUB_MUTATION;
  death_age=DEF_DEATH_AGE;
  grass_food=DEF_GRASS_FOOD;
  min_size=DEF_MIN_SIZE;

  grass_grow=DEF_GRASS_GROW;
  carrion_fade=DEF_CARRION_FADE;

  stay_cost=DEF_STAY_COST;
  turn_cost=DEF_TURN_COST;
  go_cost=DEF_GO_COST;
  bump_cost=DEF_BUMP_COST;
  eat_cost=DEF_EAT_COST;
  clone_cost=DEF_CLONE_COST;
  attack_cost=DEF_ATTACK_COST;
  work_ratio=DEF_WORK_RATIO;
  steal_food=DEF_STEAL_FOOD;
}

void world::set_terrain()
{
#ifdef DEBUG
  fprintf(stderr,"void world::set_terrain()\n");
#endif
  int i;
  for (i=0;i<mapsize*mapsize;i++)
    {
      mytiles[i].terrain=GRASS;
      mytiles[i].food=grass_food;
      /* display terrain */
#ifndef NO_GRAPHICS
      if (mainopen)
	{
	  gmain.display_pixel(i%mapsize,i/mapsize,mytiles[i].get_colour());
	}
#endif
    }
#ifndef NO_GRAPHICS
  if (mainopen){gmain.flush();}
#endif
}


void world::hills(int Nmountains,int maxsize,int minsize)
{
#ifdef DEBUG
  fprintf(stderr,"void world::set_hills(Nmountains,int maxsize,int minsize)\n");
#endif
 
  /* fancy rock drawing stuff here*/
  if (Nmountains>0 && maxsize>=0 && minsize>=0 && maxsize>=minsize)
    {
      int i,s,x,y,xc,yc,j,k;
      tile *lt=NULL;
      for (i=0;i<Nmountains;i++)
	{
	  if (maxsize==minsize){s=maxsize;}
	  else {s=(minsize+rand()%(maxsize-minsize))/2;}
	  x=rand()%mapsize;y=rand()%mapsize;
	  for (j=x-s;j<s+x;j++)
	    {
	      for (k=y-s;k<s+y;k++)
		{
		  if (sqrt((j-x)*(j-x)+(k-y)*(k-y))<s)
		    {
		      if (j<0){xc=j+mapsize;}
		      else if (j>=mapsize){xc=j-mapsize;}
		      if (k<0){yc=k+mapsize;}
		      else if (k>=mapsize){yc=k-mapsize;}
		      else {xc=j;yc=k;}
		      lt=&(mytiles[xc+yc*mapsize]);
			  if (lt)
			  {
		      		lt->terrain=ROCK;
		      		lt->food=0;
		      		if (lt->panimal)
				{
			  		lt->panimal->alive=false;
                          		statistics.update(lt->panimal);
			  		lt->panimal=NULL;
				}
#ifndef NO_GRAPHICS
		      		if (mainopen)
					{
			  			gmain.display_pixel(xc,yc,ROCK_COLOUR);
					}
#endif
		      		rocks++;
		    
			  }
		  }
		}
	    }
	}
    }
  else if (Nmountains!=0){printf("*error - check values*\n");}
  
#ifndef NO_GRAPHICS
  if (mainopen){gmain.flush();}
#endif
}

void world::remove_hills()
{
  for (int i=0;i<mapsize*mapsize;i++)
    {
      if (mytiles[i].terrain==ROCK)
        {
          mytiles[i].terrain=GRASS;
          mytiles[i].food=grass_food;
#ifndef NO_GRAPHICS
          if (mainopen)
            {
              gmain.display_pixel(i%mapsize,i/mapsize,mytiles[i].get_colour());
            }
#endif

        }      
   }

#ifndef NO_GRAPHICS
  if (mainopen){gmain.flush();}
#endif

}

void world::respawn(int population)
{
#ifdef DEBUG
  fprintf(stderr,"void world::respawn(%d)\n",population);
#endif
  age=0;
  if (population<=(mapsize*mapsize)-rocks)
    {
      int i,x,y;
     
      /* create all */
      for (i=0;i<population;i++)
	{
	  do
	    {
	      x=rand()%mapsize;y=rand()%mapsize;
	    }
	  while
	    (mytiles[x+y*(mapsize)].terrain == 
	     ROCK || mytiles[x+y*mapsize].panimal);
	  myanimals[i].animate(x,y,rand()%4,mapsize);
	  myanimals[i].number=i;

          /* update stats */
	  statistics.update(myanimals+i);

	  mytiles[x+y*(mapsize)].panimal=&(myanimals[i]);
	  /* display animal */
#ifndef NO_GRAPHICS
	  if (mainopen){gmain.display_pixel(x,y,myanimals[i].colour);}
#endif
	}
    }
  else {printf("** population exceeds available space **\n");}
#ifndef NO_GRAPHICS
  if (mainopen){gmain.flush();}
#endif
}
#ifndef NO_GRAPHICS
void world::openmain(int scale,char *name)
{
  if (mainopen){gmain.close();}
  gmain=graphics(mapsize,scale,name);
  mainopen=true;
}
void world::closemain()
{
  if (mainopen)
    {
      gmain.close();
      mainopen=false;
    }
}

void world::displaymain()
{
  int i;
  for (i=0;i<mapsize*mapsize;i++)
    {
      /* display terrain */
      if (mainopen){gmain.display_pixel(i%mapsize,i/mapsize,mytiles[i].get_colour());}
    }
  if (mainopen){gmain.flush();}
}

void world::openmini()
{
  char title[]="Pop"; 
  if (miniopen){gmini.close();}
  gmini.setup(162,100,1,title);
  gmini.clear();

  miniopen=true;
}

void world::closemini()
{
  if (miniopen)
    {
      gmini.close();
      miniopen=false;
    }
}
#endif

int world::step()
{
  int i,x,y,xf,yf,a,s;
  animal *lanimal;
  tile *pfacing;
  /* check every creature */
  statistics.reset();
  for (i=0;i<mapsize*mapsize;i++)
    {
      lanimal=&myanimals[i];

      /* check if it is alive */
      if (lanimal->alive)
	{

      // check animal colour and kill if black
      // invisibilty not fair
         if (lanimal->colour==0){lanimal->alive=false;}

	  /* update stats */
          statistics.update(myanimals+i);

	  /* check if it is fast enough to have a turn */
	  s=static_cast<int>(round((lanimal->speed+1.0f)*5.0));
	  if (s>=rand()%10)	  
	    {
	      x=lanimal->coords[0];
	      y=lanimal->coords[1];
	      xf=lanimal->facing[0];
	      yf=lanimal->facing[1];
	      
	      pfacing=&mytiles[xf+yf*(mapsize)];
	      
	      /* get action */
	      if (lanimal->size>0)
		{
		  a=lanimal->action(pfacing->get_colour());
		  switch (a)
		    {
		      
		    case LEFT:
		      lanimal->left(mapsize);
		      lanimal->energy-=turn_cost;
		      break;
		    case RIGHT:
		      lanimal->right(mapsize);
		      lanimal->energy-=turn_cost;
		      break;
		    case GO:
		      if (!pfacing->panimal && !pfacing->terrain==ROCK) // no animal
			{
			  lanimal->go(mapsize);
			  pfacing->panimal=lanimal;
			  mytiles[x+y*(mapsize)].panimal=NULL;
			  /* display movement */
#ifndef NO_GRAPHICS
			  if (mainopen)
			    {
			      gmain.display_pixel(x,y,mytiles[x+y*(mapsize)].get_colour());
			      gmain.display_pixel(xf,yf,pfacing->get_colour());
			    }
#endif
		      /* size dependent movement cost */		      
			  lanimal->energy-=(go_cost*(1+(lanimal->size/work_ratio)));
			}
		      else {lanimal->energy-=(bump_cost*(1+(lanimal->size/work_ratio)));}
		      
		      break;
		    case EAT:
		      if (!pfacing->panimal && pfacing->terrain!=ROCK) // no animal
			{
			  lanimal->eat(pfacing->food,pfacing->terrain);
			  pfacing->food=0;
			  pfacing->terrain=NOTHING;
			  /* display eaten tile */
#ifndef NO_GRAPHICS
			  if (mainopen)
			    {
			      gmain.display_pixel(xf,yf,0);
			    }
#endif
			}
		      /* what if tries to eat rock or animal? */
		      /* maybe implement punishment? bump cost perhaps */
                      
		      // else {lanimal->energy-=bump-cost;}
                      //steal food from animal
                      else if (steal_food && pfacing->panimal->alive)
                       {
                         float food=pfacing->panimal->size;
                         if (food>=pfacing->panimal->babysize)
                           {
                             lanimal->eat(pfacing->panimal->babysize,CARRION);
                             pfacing->panimal->size-=pfacing->panimal->babysize;
                           }
                         else
                           {
                             lanimal->energy+=pfacing->panimal->size;
                             pfacing->panimal->size=0;
                           }
                         lanimal->Nsteals++;
                       }
		      lanimal->energy-=eat_cost;
		      break;
		    case CLONE:
		      {
			tile *nest=NULL;
			animal *baby=NULL;
			
			/* 1st check if babysize<size */
			if (lanimal->babysize<lanimal->size)
			  {
			    /* search surrounding tiles for vacancy */
			    /* set x,y to freetile coords */
			    for (int j=0;j<9;j++)
			      {
				x=lanimal->coords[0]+(1-rand()%3);
				y=lanimal->coords[1]+(1-rand()%3);
				if (x>=mapsize){x-=mapsize;}
				else if (x<0){x+=mapsize;}
				if (y>=mapsize){y-=mapsize;}
				else if (y<0){y+=mapsize;}
				
				nest=&(mytiles[x+y*(mapsize)]);
                                //nest=&(mytiles[(x*mapsize)+y]);

				if (!nest->panimal && nest->terrain!=ROCK)
				  {break;} /* tile free */
				nest=NULL;
			      }
			    /* search through myanimals for vacancy */
			    if (nest!=NULL)
			      {
				
				for (int j=0;j<mapsize*mapsize;j++)
				  {
				    if (!myanimals[j].alive)
				      {
					baby=&(myanimals[j]);
					break;
				      }
				  }
			      }
			    if (nest!=NULL && baby!=NULL) /* perform clone */
			      {
				*baby=animal();
				baby->Nneurones =
				  clone(lanimal->genome,lanimal->genomesize,baby->genome,mutation,addsub_mutation);
				baby->number=lanimal->number;
				baby->animate(x,y,rand()%4,mapsize);
				lanimal->size-=baby->size;
				if (lanimal->size<lanimal->babysize)
				  {baby->size-=lanimal->size;}
				nest->panimal=baby;

				/* update stats */
                                statistics.update(baby);

				lanimal->Nclones++;
				/* display baby */
#ifndef NO_GRAPHICS
				if (mainopen)
				  {
				    gmain.display_pixel(x,y,nest->get_colour());
				  }
#endif
			      }		  
			  }
			else {lanimal->alive=false;}
		      }
		      lanimal->energy-=clone_cost;
		      break;
		    case ATTACK:
		      if (pfacing->panimal) 
			{
                          if (pfacing->panimal->alive)
                            {
			      if (lanimal->size*(lanimal->vore+1) > 
			          pfacing->panimal->size*(pfacing->panimal->vore+1))
			        {
                                  this->kill(pfacing->panimal);
			          lanimal->Nkills++;
			        }
			      else {lanimal->age=death_age+1;}
                            }
			}
		      lanimal->energy-=attack_cost;
		      break;
		    default:
		      {
			/* STAY */
			lanimal->energy-=stay_cost;
		      }
		    }
		}
	      else {lanimal->alive=false;}
	      /* energy budget for animal */
	      lanimal->energy_budget();
	      
	      /* if animal is dead remove it from tile */
	      if (lanimal->age>death_age){lanimal->alive=false;}
	      else if (lanimal->size<float(min_size))
		{lanimal->alive=false;}
	      else if (lanimal->adultsize<lanimal->babysize)
		{lanimal->alive=false;}
	      if (!lanimal->alive)
		{
                  this->kill(lanimal);
		  /*check if lanimal is testanimal and set testanimal to NULL*/
		  if (lanimal==testanimal){testanimal=NULL;}

		}
	    }

	}
    
  /* check every tile */
      if (mytiles[i].terrain==GRASS){statistics.grass_tiles+=1;}
      else if (mytiles[i].terrain==CARRION){statistics.carrion_tiles+=1;}
      statistics.energy+=mytiles[i].food;
/* do grass grow and carrion fade */
      x=rand()%mapsize;
      y=rand()%mapsize;
      pfacing=&(mytiles[x+y*(mapsize)]);
      int t=pfacing->terrain;
 
      if (t==GRASS && !pfacing->panimal)
	{
	  if (rand()%100000<grass_grow)
	    {
	      bool grow=false;
	      int k,l;
	      for (int m=0;m<9;m++)
		{
		  k=(1-rand()%3);
		  l=(1-rand()%3);
		  if (x+k>=mapsize){k-=mapsize;}
		  else if (x+k<0){k+=mapsize;}
		  if (y+l>=mapsize){l-=mapsize;}
		  else if (y+l<0){l+=mapsize;}
		  if (!grow)
		    {
		      pfacing=&(mytiles[x+k+(y+l)*(mapsize)]);
                      //pfacing=&(mytiles[(x+k)*mapsize+(y+l)];
		      t=pfacing->terrain;
		      if (t==NOTHING)
			{
			  grow=true;
			  pfacing->terrain=GRASS;
			  pfacing->food=grass_food;
			  /* display it */
#ifndef NO_GRAPHICS
			  if (mainopen && !pfacing->panimal)
			    {
			      gmain.display_pixel(x+k,y+l,GRASS_COLOUR);
			    }
#endif
			}
		    }
		  if (grow)break;
		}
	    }
	}
      
      //carrion fade
      else if (t==CARRION && rand()%100000<carrion_fade)
	{
	  pfacing->terrain=NOTHING;
	  pfacing->food=0;
#ifndef NO_GRAPHICS
	  if (mainopen)
	    {
	      gmain.display_pixel(x,y,0);
	    }
#endif
	}
//more stat updates
      statistics.grass_coverage=float(100*statistics.grass_tiles/(mapsize*mapsize));
    }
  age++;
#ifndef NO_GRAPHICS
  if (mainopen){gmain.flush();}
#endif
  return (statistics.population[0]+statistics.population[1]+statistics.population[2]);
}

void world::update_stats()
{
  statistics.reset();
  for (int i=0;i<mapsize*mapsize;i++)
    {
      if (myanimals[i].alive){statistics.pop++;}
    }
  printf("%d animals\n",statistics.pop);
}

void world::kill(animal *panimal)
{
       panimal->alive=false;
       tile *ptile;
       ptile=&(mytiles[panimal->coords[0]+panimal->coords[1]*(mapsize)]);
       if (ptile->terrain==CARRION)
         {
           ptile->food+=panimal->size;
         }
       else
         {
           ptile->terrain=CARRION;
           ptile->food=panimal->size;
         }
         ptile->panimal=NULL;

         /* update stats */
         statistics.update(panimal);

         /*display carrion*/
#ifndef NO_GRAPHICS
         if (mainopen)
           {
             gmain.display_pixel(panimal->coords[0],panimal->coords[1],CARRION_COLOUR);
           }
#endif

}
