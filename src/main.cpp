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
  while(cont){
    while(SDL_PollEvent( &event ))
      if(event.type == SDL_QUIT) cont = false;

    drawTile(&gfx, 16, 16, 1);
    SDL_Delay(15);
    SDL_Flip(gfx.screen);
  }
}
