#include "events.hpp"










void getEvents(EventBuffer* events){
  SDL_Event tmp;
  int n = 0;
  while(SDL_PollEvent(&tmp)){
    events->events[n].sdlevent  = tmp;
    events->events[n].eventType = SDLEVENT;
    n++;
  }
  events->eventNum = n;
}
