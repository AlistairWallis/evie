#include"mini_window.h"
#include<stdio.h>

void mini_window::setup(graphics *window)
{ 
  my_window=window;
  for (int k=0;k<4;k++)
    {
      for (int i=0;i<162;i++)
	{
	  buffer[k][i]=0;
	}
    } 
}

void mini_window::refresh_window(int herb,int omni,int carn,int g)
{
  if (counter % refresh_rate == 0)
   { 
  for (int k=0;k<4;k++)
    {
      for (int i=0;i<162;i++)
	{
	  int col;
	  my_window->display_pixel(i,buffer[k][i],0);
//          my_window->display_line(i,buffer[k][i],i+1,buffer[k][i+1],0);
	  buffer[k][i]=buffer[k][i+1];
	  if (k==0){col=999;}
	  else if (k==1){col=119;}
	  else if (k==2){col=911;}
	  else if (k==3){col=191;}
	  if (buffer[k][i]>0){my_window->display_pixel(i,buffer[k][i],col);}
//if (buffer[k][i]>0){my_window->display_line(i,buffer[k][i],i+2,buffer[k][i+2],col);}
	}
    }
//  int total_pop=herb+omni+carn;
//  buffer[0][162]=100*herb/total_pop;
//  buffer[1][162]=100*omni/total_pop;
//  buffer[2][162]=100*carn/total_pop;

  buffer[0][162]=int(scaling*herb/200.0f);
  buffer[1][162]=int(scaling*omni/200.0f);
  buffer[2][162]=int(scaling*carn/200.0f);

  buffer[3][162]=g;

  my_window->flush();
}
counter++;
}
