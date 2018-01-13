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










void pushEvent(EventBuffer* events, Event e){
  // If Event is valid
  if(e.eventType != VOIDEVENT){
    // Just make sure there aren't too many events stored.
    // It might be good to switch to a vector, though I'll put it off for now.
    if(events->eventNum >= 1024){
      printf("Too many events!\n");
      exit(-1);
    }
    events->events[events->eventNum] = e;
    events->eventNum++;
  }
}
