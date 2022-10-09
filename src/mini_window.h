#ifndef mini_window_h
#define mini_window_h
#include"graphics.h"
#include"stat.h"

class mini_window
{
 public:
  mini_window(){counter=0;refresh_rate=10;scaling=1;}

  ~mini_window(){}
  void setup(graphics *window);
  void refresh_window(int herb,int omni, int carn,int g);
  void close(){my_window->close();}
  void flush(){my_window->flush();}
  int refresh_rate;
  float scaling;
 private:
  int counter;
  graphics *my_window;
  int buffer[4][200];
};
#endif
