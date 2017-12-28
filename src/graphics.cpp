#include "graphics.hpp"










void drawRect(GfxData* g, int x, int y, int sx, int sy, int h, int w){
	SDL_Rect offset, clip;
	offset.x = x;
	offset.y = y;
	clip.x = sx;
	clip.y = sy;
	clip.h = h;
	clip.w = w;
	SDL_BlitSurface(g->tiles, &clip, g->screen, &offset);
}










void drawTile(GfxData* g, int x, int y, int t){
	int ty = (t / 8) * 48;
	int tx = (t % 8) * 32;
	drawRect(g, x, y, tx, ty, 48, 32);
}










void drawParticle(GfxData* g, int x, int y, int t){
	int ty = (t / 32) * 12;
	int tx = (t % 32) *  8;
	drawRect(g, x, y, tx, ty, 12,  8);
}









//This will be called from a function operating on a RenderObj heap
void renderObj(GfxData* g, RenderObj* r){
	if(r->isParticle)
		drawParticle(g, r->x, r->y, r->tile);
	else
		drawTile    (g, r->x, r->y, r->tile);
}
