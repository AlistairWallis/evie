#include"meme.h"
#include<stdlib.h>
#include<stdio.h>
#include<math.h>
#include<string.h>

void meme(world* theworld)
{
  int i;
  for (i=0;i<1000;i++)
     {
       meme(theworld,i);
     }
}

void meme(world* theworld, int colour)
{
  int s=theworld->mapsize;
  s=s*s;
  char structure[MAXNEURONES+1];
  int numb_at_colour;
  double genome_mean[MAXNEURONES];
  double sum_sqr[MAXNEURONES];
  double genome_variance[MAXNEURONES];
  double avg_vore;
  animal *lanimal;
  int j,k,l,m;
  
  for (j=0;j<MAXNEURONES;j++)
    {
      genome_mean[j]=0;
      genome_variance[j]=0;
      sum_sqr[j]=0;
      structure[j]='\0';
    }
  numb_at_colour=0;
  avg_vore=0;

  for (k=0;k<s;k++)
    {
      lanimal=&(theworld->myanimals[k]);
      if (lanimal->alive && lanimal->colour==colour)
        {
          for (l=0;l<lanimal->Nneurones;l++)
            {
              int T=lanimal->network[l].type;
              char lchar;
              switch(T)
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
                case SPEED :
                  lchar='V';
                  break;
                case STATE1:
                  lchar='1';
                  break;
                case STATE2:
                  lchar='2';
                  break;
                default:
                  lchar='?';
                }
              structure[l]=lchar;
            }
          structure[lanimal->Nneurones+1]='\0';
          avg_vore+=lanimal->vore;
          numb_at_colour++;
          for (m=0;m<MAXNEURONES;m++)
            {
              genome_mean[m]+=static_cast<double>(structure[m]);
              sum_sqr[m]+=pow(static_cast<double>(structure[m]),2);
            }
        }
    }
  for (k=0;k<MAXNEURONES;k++)
    {
      genome_mean[k]/=numb_at_colour;
      genome_variance[k]=(sum_sqr[k]/numb_at_colour) - pow(genome_mean[k],2);
    }
  if (numb_at_colour>0)
    {
      printf("Col:%.3i\t",colour);
      for (k=0;k<MAXNEURONES;k++)
        {
          char gene=char(fabs(genome_mean[k]));
          if (sqrt(genome_variance[k]!=0)){gene=46;}
          if (gene!=0 && gene!=10){printf("%c",gene);}
        }
          avg_vore/=numb_at_colour;
          printf("\t\tavg vore:%.1f\tPop:%d\n",avg_vore,numb_at_colour);
    }
}


void stat(world *theworld)
{
  printf("stats\n");
  int s=theworld->mapsize;
  s=s*s;
  animal *lanimal;
  int k,c;
  int hkill=0;
  int hclon=0;
  int killer=s+1;
  int cloner=s+1;
  int i;
  for (i=0;i<s;i++)
    {
      lanimal=&(theworld->myanimals[i]);
      if (lanimal->alive)
	{
	  k=lanimal->Nkills;
	  c=lanimal->Nclones;
	  if (k>hkill){killer=i;hkill=k;}
	  if (c>hclon){cloner=i;hclon=c;}
	}
    }
  if (killer!=s+1)
    {
      printf("Killer %d\n",killer);
      theworld->myanimals[killer].print();
    }
  printf("\n");
  if (cloner!=s+1)
    {
      printf("Cloner %d\n",cloner);
      theworld->myanimals[cloner].print();
    }
}


void demo(world* theworld,int colour)
{
  int maxage=theworld->death_age;
  int demog[maxage/50];
  float clone[maxage/50];
  float steal[maxage/50];
  float kills[maxage/50];
  int number=0;
  int i;
  for (i=0;i<maxage/50;i++){demog[i]=0;clone[i]=0;steal[i]=0;kills[i]=0;}
// search through world picking ages of particular colour
  printf("\nDemographics of %d\n",colour);
  int s=theworld->mapsize;
  s=s*s;
  animal *lanimal;
  for (i=0;i<s;i++)
    {
      lanimal=&(theworld->myanimals[i]);
      if (lanimal->alive)
        {
          if (lanimal->colour==colour)
            {
               demog[(lanimal->age)/50]+=1;
               clone[(lanimal->age)/50]+=lanimal->Nclones;
               steal[(lanimal->age)/50]+=lanimal->Nsteals;
               kills[(lanimal->age)/50]+=lanimal->Nkills;
               number+=1;
            }
        }
    }
  if (number>0)
    {
      printf("Age      \t Pop\t % \tClones\tSteals\tKills\n");
      for (i=0;i<maxage/50;i++)
        {
          printf("%03d-%03d  \t %d \t %d% \t%05.2f \t%05.2f \t%05.2f\n",i*50,(i*50)+50,demog[i],100*demog[i]/number,clone[i]/demog[i],steal[i]/demog[i],kills[i]/demog[i]);
        }
    }
}

void schem(world* theworld,int colour)
{
  printf("Schema of %d\n",colour);

  char localgenome[MAXGENOMESIZE()];
  double n=0;
  int i;
  double genome_mean[MAXGENOMESIZE()];
  double sum_sqr[MAXGENOMESIZE()];
  double genome_variance[MAXGENOMESIZE()];
  for (i=0;i<MAXGENOMESIZE();i++)
    {
      genome_mean[i]=0;
      sum_sqr[i]=0;
      genome_variance[i]=0;
    }

  int s=theworld->mapsize;
  s=s*s;
  animal *lanimal;
  for (i=0;i<s;i++)
    {
      lanimal=&(theworld->myanimals[i]);
      if (lanimal->alive && lanimal->colour==colour)
        {
           n+=1;
           strncpy(localgenome,lanimal->genome,lanimal->genomesize);
           for (int j=0;j<lanimal->genomesize;j++)
             {
	       genome_mean[j]=genome_mean[j]+static_cast<double>(localgenome[j]);
	       sum_sqr[j]=sum_sqr[j]+pow((static_cast<double>(localgenome[j])),2);
             }
        }
    }
  for (int k=0;k<MAXGENOMESIZE();k++)
    {
      genome_mean[k]=genome_mean[k]/n;
      genome_variance[k]=(sum_sqr[k]/n)-pow((genome_mean[k]),2);
    }
  printf("%d animals\n",int(n));
  if (n>0)
    {
      for (int k=0;k<CHARGENESIZE;k++)
        {
          char gene=char(fabs(genome_mean[k]));
          if (sqrt(genome_variance[k])!=0){gene=46;}
          printf("%c",gene);
        }
      printf(" ");
      for (int k=CHARGENESIZE;k<MAXGENOMESIZE();k++)
        {
          if ((k-CHARGENESIZE)%NGENESIZE==0){printf(" ");}
          char gene=char(fabs(genome_mean[k]));
          if (sqrt(genome_variance[k])!=0){gene=46;}
          if (gene==0){break;}
          printf("%c",gene);
        }
    }
  printf("\n");
}

void kill(world* theworld,int colour)
{
  int s=theworld->mapsize;
  s=s*s;
  animal *lanimal;
  int n=0;
  for (int i=0;i<s;i++)
   {
      lanimal=&(theworld->myanimals[i]);
      if (lanimal->alive && lanimal->colour==colour)
        {
          theworld->kill(lanimal);
          n++;
        }
   }
  printf("Killed %d animals\n",n);
}

void killall(world* theworld)
{
  int s=theworld->mapsize;
  s=s*s;
  animal *lanimal;
  for (int i=0;i<s;i++)
   {
      lanimal=&(theworld->myanimals[i]);
      if (lanimal->alive)
        {
          theworld->kill(lanimal);
        }
   }
  printf("Killed all animals\n");
}

