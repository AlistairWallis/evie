#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"ioz.h"

#define BUFSIZE 80

bool saveworld(gzFile fptr,world *theworld)
{
  theworld->update_stats();
  if (!fptr || !theworld){return false;}
  gzprintf(fptr,"%s %s\n",PACKAGE_NAME,PACKAGE_VERSION);
  gzprintf(fptr,"%d\n",theworld->mapsize);
  gzprintf(fptr,"%lu %d %d %d %d %d %d %d %d\n",
	   theworld->age,  
	   theworld->mutation,
           theworld->addsub_mutation,
	   theworld->death_age,
	   theworld->grass_grow,
           theworld->grass_food,
	   theworld->min_size,
	   theworld->carrion_fade,
	   theworld->statistics.pop);
  gzprintf(fptr,"%f %f %f %f %f %f %f %d\n",
	   theworld->stay_cost,
	   theworld->turn_cost,
	   theworld->go_cost,
	   theworld->bump_cost,
	   theworld->eat_cost,
	   theworld->clone_cost,
	   theworld->attack_cost,
           theworld->steal_food);
  int sz=theworld->mapsize;
  
  int i;
  tile *pt;
  animal *pa;
  for(i=0;i<sz*sz;i++)
    {
      pt=&theworld->mytiles[i];
      writetile(fptr,pt);
    }
  for(i=0;i<sz*sz;i++)
    {
      pa=&theworld->myanimals[i];
      if(pa->alive)
	{
	  gzprintf(fptr,"*\n");
	  writeanimal(fptr,pa);
	}
    }
  return true;
}


bool loadworld(gzFile fptr,world *theworld)
{
  int s;
  char b[10];
  char name[5];
  char version[5];
  gzgets(fptr,b,10);
  sscanf(b,"%s %s\n",name,version);
  if (strncmp(name,PACKAGE_NAME,4)!=0)
    {
      printf("Old version\n");
      printf("Trying legacy loader\n");
      return legacyloadworld(fptr,theworld);
    }
  int v=int(100*atof(version));
  int p=int(100*atof(PACKAGE_VERSION));
  if (v>p)
    {
      printf("File is for a later version of %s\nFile may not load properly\n",PACKAGE_NAME);
    }
  printf("Version %s\n",version);

  gzgets(fptr,b,10);
  sscanf(b,"%d\n",&s);
  delete theworld;
  theworld=new world(s);

  char buf[BUFSIZE];
  if (!fptr || !theworld){return false;}
  gzgets(fptr,buf,BUFSIZE);
  sscanf(buf,"%lu %d %d %d %d %d %d %d %d\n",
	 &theworld->age,  
	 &theworld->mutation,
         &theworld->addsub_mutation,
	 &theworld->death_age,
	 &theworld->grass_grow,
         &theworld->grass_food,
	 &theworld->min_size,
	 &theworld->carrion_fade,
	 &theworld->statistics.pop);

  gzgets(fptr,buf,BUFSIZE);
  sscanf(buf,"%f %f %f %f %f %f %f %d\n",
	 &theworld->stay_cost,
	 &theworld->turn_cost,
	 &theworld->go_cost,
	 &theworld->bump_cost,
	 &theworld->eat_cost,
	 &theworld->clone_cost,
	 &theworld->attack_cost,
         &theworld->steal_food);

  int sz=theworld->mapsize;

  int i;
  tile *pt;
  animal *pa;
  theworld->rocks=0;
  for(i=0;i<sz*sz;i++)
    {
      pt=&theworld->mytiles[i];
      readtile(fptr,pt);
      if (pt->terrain==ROCK){theworld->rocks++;}
      pt->panimal=NULL;
      theworld->myanimals[i].alive=false;
    }
#ifdef DEBUG
  printf("Loaded %d tiles\n",sz*sz);
#endif
  for(i=0;i<theworld->statistics.pop;i++)
    {
      pa=&theworld->myanimals[i];
      do
	{
	  gzgets(fptr,buf,BUFSIZE);
	}
      while(buf[0]!='*');

      readanimal(fptr,pa,sz,v);
      theworld->mytiles[pa->coords[0]+pa->coords[1]*(sz)].panimal=pa;
#ifdef DEBUG
//      printf("i-%d\n",i);
//      pa->print();
#endif
    }

  printf("Loaded %d animals\n",theworld->statistics.pop);
 
  return true;
}

bool legacyloadworld(gzFile fptr,world *theworld)
{
  int s;
  gzrewind(fptr);
  char b[10];
  gzgets(fptr,b,10);
  sscanf(b,"%d\n",&s);
  delete theworld;
  theworld=new world(s);

  char buf[BUFSIZE];
  //if (!fptr || !theworld){return false;}
  gzgets(fptr,buf,BUFSIZE);
  sscanf(buf,"%lu %d %d %d %d %d %d\n",
         &theworld->age,
         &theworld->mutation,
         &theworld->death_age,
         &theworld->grass_grow,
         &theworld->min_size,
         &theworld->carrion_fade,
         &theworld->statistics.pop);
  gzgets(fptr,buf,BUFSIZE);
  sscanf(buf,"%f %f %f %f %f %f %f\n",
         &theworld->stay_cost,
         &theworld->turn_cost,
         &theworld->go_cost,
         &theworld->bump_cost,
         &theworld->eat_cost,
         &theworld->clone_cost,
         &theworld->attack_cost);

// before version 2.0 addsub hardcoded to 10% of mutation
// if more variables added later add here
// therefore ...
  printf("Setting addsub to 10%\n");
  theworld->addsub_mutation=10;
  printf("Setting steal_food to 0\n");
  theworld->steal_food=false;
  int sz=theworld->mapsize;

  int i;
  tile *pt;
  animal *pa;
  theworld->rocks=0;
  for(i=0;i<sz*sz;i++)
    {
      pt=&theworld->mytiles[i];
      readtile(fptr,pt);
      if (pt->terrain==ROCK){theworld->rocks++;}
      pt->panimal=NULL;
      theworld->myanimals[i].alive=false;
    }

  for(i=0;i<theworld->statistics.pop;i++)
    {
      pa=&theworld->myanimals[i];
      do
        {
          gzgets(fptr,buf,BUFSIZE);
        }
      while(buf[0]!='*');

      readanimal(fptr,pa,sz,220); //version 2.2 and lower
      theworld->mytiles[pa->coords[0]+pa->coords[1]*(sz)].panimal=pa;
    }

  return true;
}





bool writeanimal(gzFile fptr,animal *theanimal)
{
  if (!fptr || !theanimal){return false;}
  /* write number,coords[2],direction */
  
  gzprintf(fptr,
	   "%d %d %d %d %d %d\n",
	   theanimal->number,
	   theanimal->coords[0],
	   theanimal->coords[1],
	   theanimal->direction,
	   theanimal->Nneurones,
	   theanimal->age);
  gzprintf(fptr,
	   "%f %f %f %f %f\n",
	   theanimal->energy,
	   theanimal->size,
	   theanimal->speed,
	   theanimal->state[0],
	   theanimal->state[1]);
  gzprintf(fptr,
	   "%d %d\n",
	   theanimal->Nclones,
	   theanimal->Nkills,
           theanimal->Nsteals);
  gzputs(fptr,theanimal->genome);  
  gzprintf(fptr,"\n");
  return true;
}

bool readanimal(gzFile fptr, animal *theanimal,int worldsize,int version)
{
  char buf[BUFSIZE];
  int x,y,d;
  float s,sp,st1,st2;
  if (!fptr || !theanimal){return false;}
  gzgets(fptr,buf,BUFSIZE);
  sscanf(buf,"%d %d %d %d %d %d\n",
	 &theanimal->number,
	 &x,
	 &y,
	 &d,
	 &theanimal->Nneurones,
	 &theanimal->age);
  gzgets(fptr,buf,BUFSIZE);
  sscanf(buf,"%f %f %f %f %f\n",
	 &theanimal->energy,
	 &s,
	 &sp,
	 &st1,
	 &st2);
  gzgets(fptr,buf,BUFSIZE);
  if (version>220)
    {
      sscanf(buf,"%d %d\n",
 	 &theanimal->Nclones,
	 &theanimal->Nkills,
         &theanimal->Nsteals);
    }
  else
    {
      sscanf(buf,"%d %d\n",
         &theanimal->Nclones,
         &theanimal->Nkills);
    }
  gzgets(fptr,theanimal->genome,MAXGENOMESIZE());

  theanimal->animate(x,y,d,worldsize);
  theanimal->speed=sp;
  theanimal->size=s;
  theanimal->state[0]=st1;
  theanimal->state[1]=st2;
  if (s>=static_cast<float>(theanimal->adultsize)){theanimal->adult=true;}
  return true;
}

bool writetile(gzFile fptr,tile *thetile)
{
  if (!fptr || !thetile){return false;}
  gzprintf(fptr,"%f %d\n",
	   thetile->food,
	   thetile->terrain);
  return true;
}

bool readtile(gzFile fptr, tile *thetile)
{
  char buf[80];
  if (!fptr || !thetile){return false;}
  gzgets(fptr,buf,80);
  sscanf(buf,"%f %d\n",
	 &thetile->food,
	 &thetile->terrain);
  return true;
}

