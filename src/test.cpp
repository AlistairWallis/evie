
#include"world.h"
#include<stdio.h>
#include<stdlib.h>
#include"ioz.h"

int main(int argc,char*argv[])
{

  srand(0);
  int p;
  world *pop=NULL;
  gzFile fptr=NULL; 
  char filename[]="test.pop.gz";
  
  
  int s;
  char buf[10];
  fptr=gzopen(filename,"rb");
  gzgets(fptr,buf,10);
  sscanf(buf,"%d\n",&s);
  pop=new world(s);
  if (!loadworld(fptr,pop)){printf("error loading %s\n",filename);}
  else {printf("Loaded %s\n",filename);}
  gzclose(fptr);
  
  /*
  pop=new world(250);
  pop->set_terrain();
  pop->respawn(62500);
  */
  pop->openmain(1);
  pop->displaymain();
  int i;
  for (i=0;i<5000;i++)
    {
      p=pop->step();
      printf("%d, %lu\n",p,pop->age);
      if (p==0){printf("alldead\n");break;}
    }
  
   fptr=gzopen(filename,"wb");
   gzprintf(fptr,"%d\n",pop->mapsize);
   if (saveworld(fptr,pop)){printf("Saved %s\n",filename);}
   else printf("error saving %s\n",filename);
   
   gzclose(fptr);
  
  return 0;
}
