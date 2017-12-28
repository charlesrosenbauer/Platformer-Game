#include <SDL/SDL.h>
#include "types.hpp"
#include "graphics.hpp"










int main(){
  SDL_Init (SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("Platform Game", 0);
  GfxData gfx;

  gfx.screen = SDL_SetVideoMode(640, 360, 32, 0);
  gfx.tiles  = SDL_LoadBMP("data/tileset.bmp");
  SDL_SetColorKey(gfx.tiles, SDL_SRCCOLORKEY, 0xFFFFFF);
  gfx.font   = SDL_LoadBMP("data/font.bmp");
  SDL_SetColorKey(gfx.font , SDL_SRCCOLORKEY, 0xFFFFFF);

  SDL_Event event;

  bool cont = true;
  int n = 0;
  while(cont){
    while(SDL_PollEvent( &event ))
      if(event.type == SDL_QUIT) cont = false;

    RenderObj r {n, 0, 16, 16, true};
    renderObj(&gfx, &r);

    SDL_Delay(15);
    SDL_Flip(gfx.screen);
    SDL_FillRect(gfx.screen, 0, 0);
    n = (n + 4) % 1024;
  }
}
