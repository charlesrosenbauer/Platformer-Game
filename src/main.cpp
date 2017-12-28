#include <SDL/SDL.h>










int main(){
  SDL_Init (SDL_INIT_EVERYTHING);
  SDL_WM_SetCaption("Platform Game", 0);
  SDL_Surface* screen = SDL_SetVideoMode(640, 360, 32, 0);
  SDL_Surface* tiles  = SDL_LoadBMP("data/tileset.bmp");
  SDL_SetColorKey(tiles, SDL_SRCCOLORKEY, 0xFFFFFF);
  SDL_Surface* font   = SDL_LoadBMP("data/font.bmp");
  SDL_SetColorKey(font , SDL_SRCCOLORKEY, 0xFFFFFF);


  


  SDL_Flip(screen);
  SDL_Delay(5000);
}
