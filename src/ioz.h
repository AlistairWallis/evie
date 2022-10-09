#ifndef IOZ_H
#define IOZ_H

#include<zlib.h>
#include"animal.h"
#include"tile.h"
#include"world.h"

bool saveworld(gzFile fptr,world *theworld);

bool loadworld(gzFile fptr,world *theworld);

bool legacyloadworld(gzFile fptr,world *theworld);

bool writeanimal(gzFile fptr,animal *theanimal);

bool readanimal(gzFile fptr,animal *theanimal,int worldsize,int version);

bool writetile(gzFile fptr,tile *thetile);

bool readtile(gzFile fptr,tile *thetile);

#endif
