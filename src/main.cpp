#include"conf.h"
#include"world.h"
#include"mini_window.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>
#include"ioz.h"
#include"command.h"
#include"keypress.h"

int seedrand;

int main(int argc,char*argv[])
{
  if(!seedrand) seedrand=time(0);
  srand(seedrand);
  printf ("EVIE %s\n\n",PACKAGE_VERSION);
  printf ("seed:%i\n",seedrand);
  world *pop=NULL;
  bool running=false;
  bool testing=false;
  int test_age=0;
  /* command line variables */
  size_t cs=150;
  char *com;
  com=(char*)malloc(cs+1);

  int p,g,c,s;
  int herbi,omni,carni;
  double e;
  long unsigned int t;

  pop=new world(250);
  pop->reset();
  pop->set_terrain();
  pop->respawn(25000);
#ifndef NO_GRAPHICS
  mini_window miniwin;
  miniwin.setup(&pop->gmini);
#endif

  for(;;)
    {
      if (!running)
	{
	  printf(":");
	  getline(&com,&cs,stdin);
	  if (strncmp(com,"run",3)==0)
	    {
	      printf("Press SPACE BAR to stop\n");
	      //printf(" Time\n\n");
              if (pop->testanimal==NULL)
                {
	          printf(" Pop\tH\tO\tC\tGRASS\tCARRION\tenergy\tTIME\n");
		  testing=false;
                }
              else
		{
		  printf("SEEN\tACTION\tAGE\tCLONES\tSTEALS\tKILLS\tSIZE\tENERGY\tSPEED\tSTATE1\tSTATE2\n");
		  testing=true;
		  test_age=pop->testanimal->age;
		}
              running=true;
	    }
	  else
	    {
	      if (command_line(com,pop,&miniwin,&seedrand)!=NOERR){help(com);}
	    }
	}
      else 
	{
          p=pop->step();
         
	  t=pop->age;
          s=pop->mapsize;
          herbi=pop->statistics.population[0];
          omni=pop->statistics.population[1];
          carni=pop->statistics.population[2];
          p=herbi+omni+carni;
          g=100*pop->statistics.grass_tiles/(s*s);
          c=100*pop->statistics.carrion_tiles/(s*s);
          e=pop->statistics.energy/1000000;
	      //printf("\rTime: %d",t);
	  if (!testing)
            {
              printf("\r%d \t%d \t%d \t%d \t%d \t%d \t%.2f \t%lu ",p,herbi,omni,carni,g,c,e,t);
              fflush(stdout);
            }
          if (p==0){running=false;printf("\a\n");}
          if (testing)
            {
  	       if (pop->testanimal==NULL){running=false;testing=false;printf("\n");}
               else if (pop->testanimal->age>test_age)
                 {
                   int lastsee=pop->testanimal->lastSeen;
                   int lastact=pop->testanimal->lastAction;
                   char lchar;
		   switch(lastact)
		     {
		    case STAY:
		      lchar='S';
		      break;
		    case LEFT:
		      lchar='L';
		      break;
		    case RIGHT:
		      lchar='R';
		      break;
		    case GO:
		      lchar='G';
		      break;
		    case EAT:
			lchar='E';
		      break;
		    case CLONE:
			lchar='C';
		      break;
		    case ATTACK:
			lchar='K';
		      break;
		    default:
		      lchar='?';
		    }

                   int age=pop->testanimal->age;
		   int nk=pop->testanimal->Nkills;
                   int ns=pop->testanimal->Nsteals;
		   int nc=pop->testanimal->Nclones;
                   float size=pop->testanimal->size;
                   float speed=pop->testanimal->speed;
		   float energy=pop->testanimal->energy;
                   float state1=pop->testanimal->state[0];
                   float state2=pop->testanimal->state[1];
		   printf("%03d \t%c \t%d \t%d \t%d \t%d \t%.0f \t%.2f \t%.2f \t%.2f \t%.2f\n ",lastsee,lchar,age,nc,ns,nk,size,energy,speed,state1,state2);
//                   printf("\r%03d \t%c \t%d \t%d \t%d \t%d \t%.0f \t%.2f \t%.2f \t%.2f ",lastsee,lchar,age,nc,ns,nk,size,speed,state1,state2);

                   fflush(stdout);
		   test_age=pop->testanimal->age;
		}

            }
#ifndef NO_GRAPHICS
	  if (pop->miniopen)
	    {
	      //if (t%10==0)
		//{
	      	  miniwin.refresh_window(herbi,omni,carni,g);
		//}
	    }
#endif
	}

      cbreak();
      int a=keypress();
      if(a==32){running=false;printf("\n");}
      normal();
    }
 

  
  return 0;
}
