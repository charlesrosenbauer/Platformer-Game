#include "events.hpp"










void getEvents(EventBuffer* events){
  SDL_Event tmp;
  int n = 0;
  while(SDL_PollEvent(&tmp)){
    events->events[n] = tmp;
    n++;
  }
  events->eventNum = n;
}
