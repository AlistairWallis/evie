#include"graphics.h"

#include<g2.h>
#include<g2_X11.h>
#include<stdlib.h>

graphics::graphics(int mapsize,int scale,char *its_name)
{
  SCALING=scale;//4 or 1

  graphics_id = 
    g2_open_X11X(SCALING*mapsize,SCALING*mapsize,100,100,its_name,NULL,NULL,0,0);

//create palette
 double red,green,blue;
 for (int i=0;i<1000;i++)
   {
     blue=(static_cast<double>(i%10))/10;
     green=(static_cast<double>((i/10)%10))/10;
     red=(static_cast<double>((i/100)%10))/10;
     palette[i]=g2_ink(graphics_id,red,green,blue);
   }
 g2_set_background(graphics_id,palette[0]);
 g2_set_auto_flush(graphics_id,0);
}

void graphics::setup(int mapsize,int scale,char *its_name)
{
  SCALING=scale;//4 or 1

  graphics_id = 
    g2_open_X11X(SCALING*mapsize,SCALING*mapsize,100,100,its_name,NULL,NULL,0,0);

//create palette
 double red,green,blue;
 for (int i=0;i<1000;i++)
   {
     blue=(static_cast<double>(i%10))/10;
     green=(static_cast<double>((i/10)%10))/10;
     red=(static_cast<double>((i/100)%10))/10;
     palette[i]=g2_ink(graphics_id,red,green,blue);
   }
 g2_set_background(graphics_id,palette[0]);
 g2_set_auto_flush(graphics_id,0);
}

void graphics::setup(int x,int y,int scale,char *its_name)
{
  SCALING=scale;//4 or 1

  graphics_id = 
    g2_open_X11X(SCALING*x,SCALING*y,100,100,its_name,NULL,NULL,0,0);

//create palette
 double red,green,blue;
 for (int i=0;i<1000;i++)
   {
     blue=(static_cast<double>(i%10))/10;
     green=(static_cast<double>((i/10)%10))/10;
     red=(static_cast<double>((i/100)%10))/10;
     palette[i]=g2_ink(graphics_id,red,green,blue);
   }
 g2_set_background(graphics_id,palette[0]);
 g2_set_auto_flush(graphics_id,0);
}

void graphics::clear()
{
  g2_clear(graphics_id);
}

void graphics::close()
{
  g2_close(graphics_id);
}

void graphics::display_line(int x,int y,int a,int b,int colour)
{
  double startx=static_cast<double>(x*SCALING);
  double starty=static_cast<double>(y*SCALING);
  double endx=static_cast<double>(a*SCALING);
  double endy=static_cast<double>(b*SCALING);
  g2_pen(graphics_id,palette[colour]);
  g2_set_line_width(graphics_id,0.01);
  g2_line(graphics_id,startx,starty,endx,endy);
}
void graphics::display_pixel(int x,int y,int colour)
{
  double xcoord=static_cast<double>(x*SCALING);
  double ycoord=static_cast<double>(y*SCALING);
  g2_pen(graphics_id,palette[colour]);
  if (SCALING>1)
    {
      g2_filled_rectangle
	(graphics_id,xcoord,ycoord,xcoord+SCALING-1,ycoord+SCALING-1);
    }
  else {g2_plot(graphics_id,xcoord,ycoord);}
}

void graphics::flush()
{
  g2_flush(graphics_id);
}

void graphics::query_pointer(int *xcoord, int *ycoord,unsigned int *button)
{
  double x;
  double y;
  g2_query_pointer(graphics_id,&x,&y,button);
  *xcoord=static_cast<int>(x/SCALING);
  *ycoord=static_cast<int>(y/SCALING);
}
