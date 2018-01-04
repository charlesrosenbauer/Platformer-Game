#ifndef __EVENT_HEADER__
#define __EVENT_HEADER__


#include "SDL/SDL.h"











const uint8_t SIDE_UP = 1;
const uint8_t SIDE_DN = 2;
const uint8_t SIDE_LF = 4;
const uint8_t SIDE_RT = 8;

enum GameEventType{
  COLLISIONEVENT, DESTROYEVENT
};

struct GameEvent{
  GameEventType type;
  union{
    struct{
      int entityA, entityB;
      uint8_t sides;
    } collisionEvent;

    struct{
      int entity;
    } destroyEvent;
  };
};










enum EventType{
  SDLEVENT, GAMEEVENT, VOIDEVENT
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
void pushEvent(EventBuffer*, Event);






#endif
