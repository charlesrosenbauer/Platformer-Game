#ifndef __GRAPHICS_HEADER__
#define __GRAPHICS_HEADER__


#include "SDL/SDL.h"
#include "types.hpp"










struct RenderObj{
  int tile, depth, x, y;
  bool isParticle;
};










void drawRect    (GfxData*, int, int, int, int, int, int);
void drawTile    (GfxData*, int, int, int);
void drawParticle(GfxData*, int, int, int);
void renderObj   (GfxData*, RenderObj*);






#endif
