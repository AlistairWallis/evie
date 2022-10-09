#ifndef COMMAND_H
#define COMMAND_H
#include"world.h"
#include"mini_window.h"
#include"conf.h"
enum comerr {NOERR,UNKNOWNCOM,UNKNOWNVAR,WRONGVAL};

int command_line(char *com,world * theworld,mini_window *miniwin, int *seed);
void help(char *com);

#endif
