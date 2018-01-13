#include <SDL/SDL.h>
#include "types.hpp"
#include "graphics.hpp"
#include "events.hpp"
#include "entity.hpp"










int main(){
  SDL_Init (SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("Platform Game", 0);
  GfxData gfx;

  gfx.screen = SDL_SetVideoMode(_GLOBAL_FRAME_WIDTH__, _GLOBAL_FRAME_HEIGHT_, 32, 0);

  gfx.tiles  = SDL_LoadBMP("data/tileset.bmp");
  SDL_SetColorKey(gfx.tiles, SDL_SRCCOLORKEY, 0xFFFFFF);
  gfx.font   = SDL_LoadBMP("data/font.bmp");
  SDL_SetColorKey(gfx.font , SDL_SRCCOLORKEY, 0xFFFFFF);

  EventBuffer eventsA, eventsB;
  RenderHeap heap;

  ObjectVector objects;
  createPlayer(&objects);
  createBlock (&objects, 3, 4);

  bool cont = true;
  bool mode = true;
  while(cont){
    EventBuffer* events = mode? &eventsA : &eventsB;
    EventBuffer* nexts  = mode? &eventsB : &eventsA;
    getEvents(events);
    for(int i = 0; i < events->eventNum; i++){
      if((events->events[i].eventType     == SDLEVENT)
       &&(events->events[i].sdlevent.type == SDL_QUIT))
          cont = false;
    }

    RenderObj obj0 {1, 8, 16, 16, false};
    RenderObj obj1 {1, 7, 32, 32, false};
    RenderObj obj2 {3, 6, 48, 48, false};
    RenderObj obj3 {3, 5, 64, 64, false};
    RenderObj obj4 {4, 4, 80, 80, false};
    RenderObj obj5 {4, 3, 96, 96, false};
    RenderObj obj6 {5, 2,112,112, false};
    RenderObj obj7 {5, 1,128,128, false};

    pushHeap(obj0, &heap);
    pushHeap(obj1, &heap);
    pushHeap(obj2, &heap);
    pushHeap(obj3, &heap);
    pushHeap(obj4, &heap);
    pushHeap(obj5, &heap);
    pushHeap(obj6, &heap);
    pushHeap(obj7, &heap);

    updateObjects(&objects, events, nexts, &heap);
    renderHeap(&gfx, &heap);
    checkCollisions(&objects, nexts);

    SDL_Delay(15);
    SDL_Flip(gfx.screen);
    SDL_FillRect(gfx.screen, 0, 0);
    mode = !mode;
  }

}
