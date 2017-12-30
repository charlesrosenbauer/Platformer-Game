#ifndef __GRAPHICS_HEADER__
#define __GRAPHICS_HEADER__


#include "SDL/SDL.h"
#include "types.hpp"










struct RenderObj{
  int tile, depth, x, y;
  bool isParticle;
};










struct RenderHeap{
	int top = -1;
	RenderObj heap[4096];	//Should be more than enough for most cases.
};










void drawRect    (GfxData*, int, int, int, int, int, int);
void drawTile    (GfxData*, int, int, int);
void drawParticle(GfxData*, int, int, int);
void renderObj   (GfxData*, RenderObj*);
int  pushHeap    (RenderObj,RenderHeap*);
RenderObj popHeap(RenderHeap*);
void renderHeap  (GfxData*, RenderHeap*);
void showHeap    (RenderHeap*);




#endif
