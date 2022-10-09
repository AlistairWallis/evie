#include"neurone.h"

#include<stdlib.h>

neurone::neurone()
{
  for (int i=0;i<NWEIGHTS;i++)
    {
      weight[i]=0;
    }
  type=STAY;
}

neurone::neurone(char *gene)
{
  type=static_cast<int>(abs(gene[0]-106)); /* type stored in 1st char */
  for (int i=1;i<NGENESIZE-1;i+=2)
    {
      weight[i/2]=(static_cast<float>(gene[i+1]-106))/10;
      weight[i/2]+=(static_cast<float>(gene[i+1]-106))/100;
    }
}


float neurone::output(int sight,bool adult,float *state)
{
  float a;
  if (adult){a=1.0;}
  else {a=0.0;}
 
  float r,g,b;
  b=static_cast<float>((sight%10))/10;
  g=static_cast<float>((sight/10)%10)/10;
  r=static_cast<float>((sight/100)%10)/10;
  float act=0;
  act+=weight[0]*r;
  act+=weight[1]*g;
  act+=weight[2]*b;
  act+=weight[3]*a;
  act+=weight[4]*state[0];
  act+=weight[5]*state[1];
  act-=weight[6]; /* subtract threshold */

  return (act);
}
