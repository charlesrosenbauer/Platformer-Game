#include "entity.hpp"
#include "SDL/SDL.h"










void updatePlayer(Object* e, EventBuffer* events){
  Entity* ent = (Entity*)e->data;
  for(int i = 0; i < events->eventNum; i++){
    if(events->events[i].eventType     == SDLEVENT){
      if(events->events[i].sdlevent.type == SDL_KEYDOWN){
        switch(events->events[i].sdlevent.key.keysym.sym){
          case SDLK_UP    : ent->dy =  1; break;
          case SDLK_DOWN  : ent->dy = -1; break;
          case SDLK_RIGHT : ent->dx =  1; break;
          case SDLK_LEFT  : ent->dx = -1; break;
          default: break;
        }
      }else if(events->events[i].sdlevent.type == SDL_KEYUP){
        switch(events->events[i].sdlevent.key.keysym.sym){
          case SDLK_UP    : ent->dy = (ent->dy > 0)? 0 : ent->dy; break;
          case SDLK_DOWN  : ent->dy = (ent->dy < 0)? 0 : ent->dy; break;
          case SDLK_RIGHT : ent->dx = (ent->dx > 0)? 0 : ent->dx; break;
          case SDLK_LEFT  : ent->dx = (ent->dx < 0)? 0 : ent->dx; break;
          default: break;
        }
      }
    }
  }
  ent->x += ent->dx;
  ent->y += ent->dy;
}










void updateObject(Object* e, EventBuffer* events){
  switch(e->type){
    case PLAYER:
      updatePlayer(e, events);
      break;
    default: break; // For now
  }
}
