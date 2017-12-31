#ifndef __EVENT_HEADER__
#define __EVENT_HEADER__


#include "SDL/SDL.h"










struct EventBuffer{
  SDL_Event events[1024];
  int eventNum;
};










void getEvents(EventBuffer*);






#endif
