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










inline int  heapParent(int index){
	return (index - 2) / 2;
}

inline int  heapLeft  (int index){
	return (index * 2) + 1;
}

inline int  heapRight (int index){
	return (index * 2) + 2;
}

inline void heapSwap  (RenderHeap* h, int a, int b){
	RenderObj temp = h->heap[a];
	h->heap[a]     = h->heap[b];
	h->heap[b]     = temp;
}










void bubbleDown (RenderHeap* h, int index){
	int left  = heapLeft (index);
	int right = heapRight(index);

	int targetDepth = h->heap[index].depth;
	RenderObj temp;

	if(left > h->top){
		if((right <= h->top) && (h->heap[right].depth < targetDepth)){
			// Swap
			heapSwap  (h, right, index);
			bubbleDown(h, right);
		}
	}else if(right > h->top){
		if((left <= h->top) && (h->heap[left].depth < targetDepth)){
			// Swap
			heapSwap  (h, left, index);
			bubbleDown(h, left);
		}
	}else if((h->heap[left].depth < h->heap[right].depth)
			  && (h->heap[left].depth  < targetDepth)){
		// Swap
		heapSwap  (h, left, index);
		bubbleDown(h, left);
	}else if (h->heap[right].depth < targetDepth){
		// Swap
		heapSwap  (h, right, index);
		bubbleDown(h, right);
	}
}










void bubbleUp (RenderHeap* h, int index){
	if(index <= 0) return;

	int parent = heapParent(index);
	if(h->heap[parent].depth > h->heap[index].depth){
		heapSwap(h, parent, index);
		bubbleUp(h, parent);
	}
}










int pushHeap(RenderHeap* h, RenderObj obj){
	if(h->top >= 4096) return -1;

	h->top++;
	h->heap[h->top] = obj;
	bubbleUp(h, h->top);

	return 0;
}










RenderObj popHeap(RenderHeap* h){

	RenderObj ret;
	if(h->top < 0) return ret;

	ret = h->heap[0];
	if(h->top > 0){
		heapSwap(h, 0, h->top);
		h->top--;
		bubbleDown(h, 0);
	}
	return ret;
}
