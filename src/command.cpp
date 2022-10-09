#include"command.h"
#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include"ioz.h"
#include"meme.h"

int command_line(char *com,world *theworld,mini_window *miniwin,int *seed)
{
  char buf0[20];
  char buf1[20];
  float val=0;
  float val1=0;
  sscanf(com,"%s %s %f %f",
	 buf0,buf1,&val,&val1);

  if (strncmp(buf0,"set",2)==0)
    {
      
      if (strncmp(buf1,"mutation",3)==0)
	{
	  if (val>=0 && val <=1000000)
	    {
	      theworld->mutation=val;
	      printf("Setting mutation to %d\n",int(val));
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
     if (strncmp(buf1,"addsub",3)==0)
        {
          if (val>=0 && val <=10000)
            {
              theworld->addsub_mutation=val;
              printf("Setting addsub mutation to %d%\n",int(val));
              return NOERR;
            }
          else return WRONGVAL;
        }

      else if (strncmp(buf1,"death_age",3)==0)
	{
	  if (val>=0)
	    {
	      theworld->death_age=int(val);
	      printf("Setting death_age to %d\n",int(val));

	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"grass_food",7)==0)
	{
	  if (val>=0)
	    {
	      theworld->grass_food=int(val);
	      printf("Setting grass_food to %d\n",int(val));
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"min_size",3)==0)
	{
	  if (val>=1)
	    {
	      theworld->min_size=int(val);
	      printf("Setting min_size to %d\n",int(val));
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"grass_grow",7)==0)
	{
	  if (val>=0 && val<=100000)
	    {
	      theworld->grass_grow=int(val);
	      printf("Setting grass_grow to %d\n",int(val));
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"carrion_fade",3)==0)
	{
	  if (val>=0 && val<=100000)
	    {
	      theworld->carrion_fade=int(val);
	      printf("Setting carrion_fade to %d\n",int(val));
	      return NOERR;
	    }
	  else return WRONGVAL;
	}

      else if (strncmp(buf1,"stay_cost",3)==0)
	{
	  if (val>=0)
	    {
	      theworld->stay_cost=val;
	      printf("Setting stay_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"turn_cost",2)==0)
	{
	  if (val>=0)
	    {
	      theworld->turn_cost=val;	      
	      printf("Setting turn_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"go_cost",2)==0)
	{
	  if (val>=0)
	    {
	      theworld->go_cost=val;
	      printf("Setting go_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"bump_cost",2)==0)
	{
	  if (val>=0 && val<=100000)
	    {
	      theworld->bump_cost=val;
	      printf("Setting bump_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"eat_cost",2)==0)
	{
	  if (val>=0)
	    {
	      theworld->eat_cost=val;
	      printf("Setting eat_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"clone_cost",2)==0)
	{
	  if (val>=0)
	    {
	      theworld->clone_cost=val;
	      printf("Setting clone_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"attack_cost",2)==0)
	{
	  if (val>=0)
	    {
	      theworld->attack_cost=val;
	      printf("Setting attack_cost to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"work_ratio",2)==0)
	{
	  if (val>=1)
	    {
	      theworld->work_ratio=val;
	      printf("Setting work_ratio to %f\n",val);
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"steal_food",3)==0)
        {
          if (val==0)
            {
              theworld->steal_food=false;
              printf("Setting steal_food to false\n");
              return NOERR;
            }
          else if (val==1)
            {
              theworld->steal_food=true;
              printf("Setting steal_food to true\n");
              return NOERR;
            }
          else return WRONGVAL;
        }

      else if (strncmp(buf1,"seed",3)==0)
        {
          if (val>=0)
            {
              *seed=int(val);
              printf("Setting random seed to %d\n",int(val));
	      srand(*seed);
              return NOERR;
            }
          else return WRONGVAL;
        }
      else if (strncmp(buf1,"mwr",3)==0)
        {
          if (int(val)>0)
            {
              miniwin->refresh_rate=int(val);
              printf("Setting mwr to %d\n",int(val));
              return NOERR;
            }
          else return WRONGVAL;
        }
      else if (strncmp(buf1,"mws",3)==0)
        {
          if (val>0)
            {
              miniwin->scaling=val;
              printf("Setting mws to %f\n",val);
              return NOERR;
            }
          else return WRONGVAL;
        }

      else return UNKNOWNVAR;
    }

  else if (strncmp(buf0,"show",2)==0)
    {
      if (strncmp(buf1,"mutation",3)==0)
	{
	  printf("mutation is %d\n",theworld->mutation);
	}
      else if (strncmp(buf1,"addsub",3)==0)
        {
          printf("addsub is %d%\n",theworld->mutation);
        }
      else if (strncmp(buf1,"death_age",3)==0)
	{
	  printf("death_age is %d\n",theworld->death_age);
	}
      else if (strncmp(buf1,"grass_food",7)==0)
	{
	  printf("grass_food is %d\n",theworld->grass_food);
	}
      else if (strncmp(buf1,"min_size",3)==0)
	{
	  printf("min_size is %d\n",theworld->min_size);
	}
      else if (strncmp(buf1,"grass_grow",7)==0)
	{
	  printf("grass_grow is %d\n",theworld->grass_grow);
	}
      else if (strncmp(buf1,"carrion_fade",3)==0)
	{
	  printf("carrion_fade is %d\n",theworld->carrion_fade);
	}

      else if (strncmp(buf1,"stay_cost",3)==0)
	{
	  printf("stay_cost is %f\n",theworld->stay_cost);
	}
      else if (strncmp(buf1,"turn_cost",2)==0)
	{
	  printf("turn_cost is %f\n",theworld->turn_cost);
	}
      else if (strncmp(buf1,"go_cost",2)==0)
	{
	  printf("go_cost is %f\n",theworld->go_cost);
	}
      else if (strncmp(buf1,"bump_cost",2)==0)
	{
	  printf("bump_cost is %f\n",theworld->bump_cost);
	}
      else if (strncmp(buf1,"eat_cost",2)==0)
	{
	  printf("eat_cost is %f\n",theworld->eat_cost);
	}
      else if (strncmp(buf1,"clone_cost",2)==0)
	{
	  printf("clone_cost is %f\n",theworld->clone_cost);
	}
      else if (strncmp(buf1,"attack_cost",2)==0)
	{
	  printf("attack_cost is %f\n",theworld->attack_cost);
	}
      else if (strncmp(buf1,"work_ratio",2)==0)
	{
	  printf("work_ratio is %f\n",theworld->work_ratio);
	}
      else if (strncmp(buf1,"steal_food",3)==0)
        {
          printf("steal_food is %d\n",theworld->steal_food);
        }
      else if (strncmp(buf1,"seed",3)==0)
        {
          printf("random seed is %d\n",*seed);
        }

      else if(strncmp(buf1,"all",2)==0)
	{
	  printf("mutation is %d\n",theworld->mutation);
          printf("addsub mutation is %d%\n",theworld->addsub_mutation);
	  printf("death_age is %d\n",theworld->death_age);
	  printf("grass_food is %d\n",theworld->grass_food);
	  printf("grass_grow is %d\n",theworld->grass_grow);
	  printf("min_size is %d\n",theworld->min_size);
	  printf("carrion_fade is %d\n",theworld->carrion_fade);
	  printf("stay_cost is %f\n",theworld->stay_cost);
	  printf("turn_cost is %f\n",theworld->turn_cost);
	  printf("go_cost is %f\n",theworld->go_cost);
	  printf("bump_cost is %f\n",theworld->bump_cost);
	  printf("eat_cost is %f\n",theworld->eat_cost);
	  printf("clone_cost is %f\n",theworld->clone_cost);
	  printf("attack_cost is %f\n",theworld->attack_cost);
          printf("steal_food is %d\n",theworld->steal_food);
	  printf("work_ratio is %f\n",theworld->work_ratio);
          printf("random seed is %d\n",*seed);
	  printf("mwr (Mini window refresh rate) is %d\n",miniwin->refresh_rate);
          printf("mws (Mini window scaling) is %f\n",miniwin->scaling);
	}
      else return UNKNOWNVAR;
    }
#ifndef NO_GRAPHICS
  else if (strncmp(buf0,"open",4)==0)
    {
      if (strncmp(buf1,"main",4)==0)
	{
	  if (val>=1 && val<=5)
	    {
	      char name[]=PACKAGE_NAME;
	      theworld->openmain(int(val),name);
	      theworld->displaymain();
	      return NOERR;
	    }
	  else return WRONGVAL;
	}
      else if (strncmp(buf1,"mini",4)==0)
	{
	  theworld->openmini();
	  return NOERR;
	}
      else return UNKNOWNVAR;
    }
  else if (strncmp(buf0,"close",4)==0)
    {
      if (strncmp(buf1,"main",4)==0)
	{
	  theworld->closemain();
	}
      else if (strncmp(buf1,"mini",4)==0)
	{
	  theworld->closemini();
	}
      else return UNKNOWNVAR;
    }
#endif
  else if (strncmp(buf0,"save",4)==0)
    {
      printf("Saving %s\n",buf1);
      gzFile fptr=NULL;
      fptr=gzopen(buf1,"rb");
      if (fptr)
	{
	  char c=0;
	    {
	      printf("%s exists - Overwrite(y/n)",buf1);
	      c=getc(stdin);
	    }
	  while (c!='y' && c!='n');
	  gzclose(fptr);
	  if (c=='n'){return NOERR;}
	}
      fptr=gzopen(buf1,"wb");
//      gzprintf(fptr,"%d\n",theworld->mapsize);
      if (saveworld(fptr,theworld)){printf("Saved %s\n",buf1);}
      else printf("error saving %s\n",buf1);
      gzclose(fptr);
      return NOERR;
    }
  else if (strncmp(buf0,"load",4)==0)
    {
#ifndef NO_GRAPHICS
      theworld->closemain();
      theworld->closemini();
#endif
      printf("Loading %s\n",buf1);
      gzFile fptr=NULL;	 

      fptr=gzopen(buf1,"rb");
      if (!fptr){printf("No such file %s\n",buf1);return NOERR;}

      if (!loadworld(fptr,theworld)){printf("error loading %s\n",buf1);}
      else {printf("Loaded %s\n",buf1);}
      gzclose(fptr);
      return NOERR;
    }
  else if (strncmp(buf0,"remove",4)==0)
    {
      printf("Removing hills\n");
      theworld->remove_hills();
      return NOERR;
    }
  else if (strncmp(buf0,"reset",4)==0)
    {
      printf("Resetting to defaults\n");
      theworld->reset();
      return NOERR;
    }
  else if (strncmp(buf0,"respawn",4)==0)
    {
      int s=atoi(buf1);
      if (s>0)
	{
	  int sz=theworld->mapsize;
	  printf("Respawning %d\n",s);
#ifndef NO_GRAPHICS
	  theworld->closemain();
	  theworld->closemini();
#endif
	  delete theworld;
	  theworld=new world(sz);
	  theworld->set_terrain();
	  theworld->respawn(s);
	  return NOERR;
	}
      else {return WRONGVAL;}
    }
  else if (strncmp(buf0,"resize",4)==0)
    {
      int s;
      sscanf(buf1,"%d",&s);
      if (s>100)
	{
#ifndef NO_GRAPHICS
	  theworld->closemain();
	  theworld->closemini();
#endif
	  delete theworld;
	  theworld=new world(s);
	  return NOERR;
	}
      else {return WRONGVAL;}
    }
  else if (strncmp(buf0,"hills",2)==0)
    {
      int n;
      sscanf(buf1,"%d",&n);
      if (n<1 || n>20){return WRONGVAL;}
      if (int(val)<=0 || int(val1)<=0){return WRONGVAL;}
      theworld->hills(n,int(val),int(val1));
      return NOERR;
    }
  else if (strncmp(buf0,"test",4)==0)
    {
      int n;
      sscanf(buf1,"%d",&n);
      if (n<0)
	{
	  theworld->testanimal=NULL;
	  printf("test off\n");
	  return NOERR;
	}
      int max=theworld->mapsize;
      max=max*max;
      if (n<max  && (theworld->myanimals+n)->alive)
	{
          theworld->testanimal=theworld->myanimals+n;  
	}
      else return WRONGVAL;
      theworld->testanimal->print();
      return NOERR;
    }
  else if (strncmp(buf0,"meme",2)==0)
    {
      sscanf(buf1,"%f",&val);
      if (val>0 && val<1000)
        {
          meme(theworld,int(val));
          return NOERR;
        }
      meme(theworld);
      return NOERR;
    }
  else if (strncmp(buf0,"statistics",4)==0)
    {
      stat(theworld);
      return NOERR;
    }
  else if (strncmp(buf0,"demographics",4)==0)
    {
      sscanf(buf1,"%f",&val);
      if (val>0 && val<1000)
        {
          demo(theworld,int(val));
          return NOERR;
        }
      else return WRONGVAL;
    }
  else if (strncmp(buf0,"schema",4)==0)
    {
      sscanf(buf1,"%f",&val);
      if (val>0 && val<1000)
        {
          schem(theworld,int(val));
          return NOERR;
        }
      else return WRONGVAL;
    }
 else if (strncmp(buf0,"kill",3)==0)
    {
      if (strncmp(buf1,"all",3)==0)
        {
          killall(theworld);
          return NOERR;
        }
      sscanf(buf1,"%f",&val);
      if (val>0 && val<1000)
        {
          kill(theworld,int(val));
          return NOERR;
        }
      else return WRONGVAL;
    }

  else if (strncmp(buf0,"help",2)==0)
    {
      help(buf1);
      return NOERR;
    }
  else if (strncmp(buf0,"ls",2)==0)
    {
      //char cl[256];
      //strcat(buf1,"/*.pop.gz\n");
      //strcpy(cl,buf0);
      //strcat(cl," ");
      //strcat(cl,buf1);
      //printf("%s %s\n",buf0,buf1);
      //fprintf("ls %s/*.pop.gz",buf1);
      system("ls *.pop.gz");
      //system(buf0);
      return NOERR;
    }
  else if (strncmp(buf0,"quit",1)==0)
    {
      printf("bye!\n");
      exit(0);
    }
  else 
    {
      return UNKNOWNCOM;
    }
  
  return NOERR;
}


void help(char *com)
{

  if (strncmp(com,"show",3)==0)
    {
      printf("*show world variable settings*\n");
      printf(":show\tall\n\tmutation\n\taddsub\n\tdeath_age\n\tgrass_food\n\tgrass_grow\n\tmin_size\n\tcarrion_fade\n\tstay_cost\n\tturn_cost\n\tgo_cost\n\tbump_cost\n\teat_cost\n\tclone_cost\n\tattack_cost\n\twork_ratio\n\tseed\n");
    }
  else if (strncmp(com,"set",3)==0)
    {
      printf("*set world variables*\n");
      printf(":set\tmutation\t[0-1000000]\n\taddsub   \t[0-10000%]\n\tdeath_age\t[0-?]\n\tgrass_food\t[0-?]\n\tgrass_grow\t[0-100000\n\tmin_size\t[1-?]\n\tcarrion_fade\t[0-100000]\n\tstay_cost\t[0.0-?\n\tturn_cost\t[0.0-?]\n\tgo_cost\t\t[0.0-?]\n\tbump_cost\t[0.0-?]\n\teat_cost\t[0.0-?]\n\tclone_cost\t[0.0-?]\n\tattack_cost\t[0.0-?]\n\tsteal_food\t[0 or 1]\n\twork_ratio\t[1.0-?]\n\tseed\t\t[0-?]\n");
    }
  else if (strncmp(com,"open",3)==0)
    {
      printf("*open graphical display*\n");
      printf(":open\tmain\t<size>\t[1-5]\n\tmini\n");
    }
  else if (strncmp(com,"close",3)==0)
    {
      printf("*close graphical display*\n");
      printf(":close\tmain\n\tmini\n");
    }
  else if (strncmp(com,"load",3)==0)
    {
      printf("*load file*\n");
      printf(":load\t<filename>\n");
    }
  else if (strncmp(com,"save",3)==0)
    {
      printf("*save file*\n");
      printf(":save\t<filename>\n");
    }
  else if (strncmp(com,"reset",4)==0)
    {
      printf("*reset to defaults*\n");
      printf(":reset\n");
    }
  else if (strncmp(com,"respawn",4)==0)
    {
      printf("*respawn world with random animals*\n");
      printf(":respawn\t<population>\t[1-?]\n");
    }
  else if (strncmp(com,"resize",4)==0)
    {
      printf("*create new world*\n");
      printf(":resize\t<mapsize>\t[100-?]\n");
    }
  else if (strncmp(com,"hills",2)==0)
    {
      printf("*build hills*\n");
      printf(":hills\t<no. of hills> <max size> <min size>\t[1-20] [1-?] [1-?]\n");
    }
  else if (strncmp(com,"meme",2)==0)
    {
      printf("*animal analysis function*\n");
      printf(":meme\n");
      printf(":meme\t<animal colour>\n");
    }
  else if (strncmp(com,"demog",3)==0)
    {
      printf("*animal demographics by colour*\n");
      printf(":demog\t<animal colour>\n");
    }
  else if (strncmp(com,"schem",3)==0)
    {
      printf("*genome analysis function*\n");
      printf(":schem\t<animal colour>\n"); 
    }
  else if (strncmp(com,"kill",3)==0)
    {
      printf("*kill animals by colour*\n");
      printf(":kill\t<animal colour>\n");
    }
  else if (strncmp(com,"test",3)==0)
    {
      printf("*test animal of particular number*\n");
      printf(":test\t<animal number>\n");
    }
  else if (strncmp(com,"quit",1)==0)
    {
      printf("*quit evie*\n");
      printf(":quit\n");
    }


  else if (strncmp(com,"mutation",3)==0)
    {
      printf("The mutation rate per 1000000\n");
    }
  else if (strncmp(com,"addsub",3)==0)
    {
      printf("The addition/subtraction mutation rate as a percentage of mutation rate\n");
    }
  else if (strncmp(com,"death_age",3)==0)
    {
      printf("The number of turns taken before compulsory death\n");
    }

  else printf("help\tshow\tset\topen\tclose\tload\tsave\treset\nrespawn\tresize\thills\tmeme\tdemog\tschem\tkill\ttest\tquit\n");
}   


