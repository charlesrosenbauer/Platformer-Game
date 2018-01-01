#include <SDL/SDL.h>
#include "types.hpp"
#include "graphics.hpp"
#include "events.hpp"










int main(){
  SDL_Init (SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("Platform Game", 0);
  GfxData gfx;

  gfx.screen = SDL_SetVideoMode(640, 360, 32, 0);
  gfx.tiles  = SDL_LoadBMP("data/tileset.bmp");
  SDL_SetColorKey(gfx.tiles, SDL_SRCCOLORKEY, 0xFFFFFF);
  gfx.font   = SDL_LoadBMP("data/font.bmp");
  SDL_SetColorKey(gfx.font , SDL_SRCCOLORKEY, 0xFFFFFF);

  EventBuffer events;
  RenderHeap heap;

  bool cont = true;
  while(cont){
    getEvents(&events);
    for(int i = 0; i < events.eventNum; i++){
      if((events.events[i].eventType     == SDLEVENT)
       &&(events.events[i].sdlevent.type == SDL_QUIT))
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

    renderHeap(&gfx, &heap);

    SDL_Delay(15);
    SDL_Flip(gfx.screen);
    SDL_FillRect(gfx.screen, 0, 0);
  }

}
