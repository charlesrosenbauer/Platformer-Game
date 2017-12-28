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
