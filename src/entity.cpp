#include "entity.hpp"
#include "SDL/SDL.h"










void updatePlayer(Object* e, EventBuffer* events){
  Entity* ent = (Entity*)e->data;
  for(int i = 0; i < events->eventNum; i++){
    if(events->events[i].eventType     == SDLEVENT){
      if(events->events[i].sdlevent.type == SDL_KEYDOWN){
        switch(events->events[i].sdlevent.key.keysym.sym){
          case SDLK_UP    : ent->dy = (ent->jmpnum < 2)? -3 : ent->dy; break;
          //case SDLK_DOWN  : ent->dy =  1; break;
          case SDLK_RIGHT : ent->dx =      2; break;
          case SDLK_LEFT  : ent->dx =     -2; break;
          case SDLK_LSHIFT: ent->boost = 1.5; break;
          case SDLK_RSHIFT: ent->boost = 1.5; break;
          default: break;
        }
      }else if(events->events[i].sdlevent.type == SDL_KEYUP){
        switch(events->events[i].sdlevent.key.keysym.sym){
          case SDLK_UP    : ent->jmpnum++; break;
          //case SDLK_DOWN  : ent->dy = (ent->dy > 0)? 0 : ent->dy; break;
          case SDLK_RIGHT : ent->dx = (ent->dx > 0)? 0 : ent->dx; break;
          case SDLK_LEFT  : ent->dx = (ent->dx < 0)? 0 : ent->dx; break;
          case SDLK_LSHIFT: ent->boost = 1; break;
          case SDLK_RSHIFT: ent->boost = 1; break;
          default: break;
        }
      }
    }
  }
  ent->dy += 0.1;
  ent->x  += ent->dx * ent->boost;
  ent->y  += ent->dy * ent->boost;

  //Just for now until actual collision is in the game
  if(ent->y > 200){
    ent->y = 200;
    ent->jmpnum = 0;
  }
}










void renderPlayer(Object* e, RenderHeap* rheap){
  Entity* ent = (Entity*)e->data;
  rheap->offsetX = ent->x;
  rheap->offsetY = ent->y;
  RenderObj robj {32, 4, (int)ent->x-16, (int)ent->y-24, false};
  pushHeap(robj, rheap);
}












void updateObject(Object* e, EventBuffer* events, RenderHeap* rheap){
  switch(e->type){
    case PLAYER:
      updatePlayer(e, events);
      renderPlayer(e, rheap);
      break;
    default: break; // For now
  }
}
