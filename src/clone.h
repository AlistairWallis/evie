#ifndef CLONE_H
#define CLONE_H
#include"animal.h"
#include<stdlib.h>
#include<string.h>

/* returns NUMBER OF NEURONES IN *baby*/
/* mutation is per 1000000 */
/* returns number of neurones in baby genome*/
int clone(char *genome,int size,char *baby,int mutation,int addsub_mutation)
{
  int babysize=size;
  int point_one,point_two;
  point_one=point_two=CHARGENESIZE;

  /*copy characteristics gene 1st */
  strncpy(baby,genome,CHARGENESIZE);

  while(point_two<size)
    {
      if (point_one<MAXGENOMESIZE())
	{
	  strncpy(baby+point_one,genome+point_two,NGENESIZE);
	  *(baby+point_one+NGENESIZE)='\0';
	  point_one=point_one+NGENESIZE;
	  point_two=point_two+NGENESIZE;
	}
      else break;
      if (rand()%1000000<(addsub_mutation*mutation/100))
	{
	  //deletion
	  if (rand()%10<5 && (babysize/NGENESIZE)>=1)
	    {
	      point_two=point_two+NGENESIZE;
	      babysize-=NGENESIZE;
	    }
	  //addition
	  else if (point_two>=(CHARGENESIZE+NGENESIZE) && (babysize/NGENESIZE)<MAXNEURONES)
	    {
	      point_two=point_two-NGENESIZE;
	      babysize+=NGENESIZE;
	    }
	}

    }
  // do mutation
  int i;
  for (i=0;i<babysize;i++)
    {
      if (*(baby+i)=='\0'){break;}
      else if (rand()%1000000<mutation)
	{
	  baby[i]=97+rand()%19;
	}
    }
  return ((babysize-CHARGENESIZE)/NGENESIZE);
}

#endif
