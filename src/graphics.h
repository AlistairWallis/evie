//graphics.h function defs

#ifndef GRAPHICS_H
#define GRAPHICS_H

class graphics
{
 public:
  graphics(){};
  graphics(int mapsize,int scale,char *its_name);
  ~graphics(){}
  void setup(int mapsize,int scale,char *its_name);
  void setup(int x,int y,int scale,char *its_name);
  void clear();
  void close();
  void display_pixel(int x,int y,int colour);
  void display_line(int x,int y,int a,int b,int colour);
  void flush();
  void query_pointer(int *xcoord, int *ycoord,unsigned int *button);

  int get_id(){return graphics_id;}
 private:
  int graphics_id;
  int palette[1000];
  int SCALING;//4
};

#endif
