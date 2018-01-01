#ifndef __EVENT_HEADER__
#define __EVENT_HEADER__


#include "SDL/SDL.h"











struct GameEvent{
  int data;     // Add more later
};










enum EventType{
  SDLEVENT, GAMEEVENT
};

struct Event{
  union{
    SDL_Event sdlevent;
    GameEvent gameevent;
  };
  EventType eventType;
};










struct EventBuffer{
  Event events[1024];
  int eventNum;
};










void getEvents(EventBuffer*);






#endif
