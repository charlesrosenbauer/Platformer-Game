#include <SDL/SDL.h>










int main(){
  SDL_Init (SDL_INIT_EVERYTHING);
  SDL_Surface* screen = SDL_SetVideoMode(640, 360, 32, 0);


  uint32_t* pix = (uint32_t*)screen->pixels;
  for(int it = 0; it < 230400; it++)
    pix[it] = 0;


  SDL_Flip(screen);
  SDL_Delay(5000);
}
