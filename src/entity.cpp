#include "entity.hpp"
#include "SDL/SDL.h"










// Assumes that player and ent are both part of the same player object
void updatePlayer(Object* player, Entity* ent, EventBuffer* events, EventBuffer* nextEvents){

  for(int i = 0; i < events->eventNum; i++){
    if(events->events[i].eventType     == SDLEVENT){
      if(events->events[i].sdlevent.type == SDL_KEYDOWN){
        switch(events->events[i].sdlevent.key.keysym.sym){
          case SDLK_UP    : ent->dy = (player->data.plyd.jmpnum < 3)? -3 : ent->dy; break;
          //case SDLK_DOWN  : ent->dy =  1; break;
          case SDLK_RIGHT : ent->dx =      2; break;
          case SDLK_LEFT  : ent->dx =     -2; break;
          case SDLK_LSHIFT: player->data.plyd.boost = 1.5; break;
          case SDLK_RSHIFT: player->data.plyd.boost = 1.5; break;
          default: break;
        }
      }else if(events->events[i].sdlevent.type == SDL_KEYUP){
        switch(events->events[i].sdlevent.key.keysym.sym){
          case SDLK_UP    : player->data.plyd.jmpnum++; break;
          //case SDLK_DOWN  : ent->dy = (ent->dy > 0)? 0 : ent->dy; break;
          case SDLK_RIGHT : ent->dx = (ent->dx > 0)? 0 : ent->dx; break;
          case SDLK_LEFT  : ent->dx = (ent->dx < 0)? 0 : ent->dx; break;
          case SDLK_LSHIFT: player->data.plyd.boost = 1; break;
          case SDLK_RSHIFT: player->data.plyd.boost = 1; break;
          default: break;
        }
      }
    }
  }
  ent->dy += 0.1;
  ent->x  += ent->dx * player->data.plyd.boost;
  ent->y  += ent->dy * player->data.plyd.boost;

  //Just for now until actual collision is in the game
  if(ent->y > 200){
    ent->y = 200;
    player->data.plyd.jmpnum = 0;
  }
}










void renderPlayer(Entity* ent, RenderHeap* rheap){
  rheap->offsetX = ent->x;
  rheap->offsetY = ent->y;
  RenderObj robj {32, 4, (int)ent->x-16, (int)ent->y-24, false};
  pushHeap(robj, rheap);
}









void renderBlock(Entity* ent, int tile, int depth, RenderHeap* rheap){
  RenderObj robj {tile, depth, (int)ent->x, (int)ent->y, false};
  pushHeap(robj, rheap);
}












void updateObject(ObjectVector* objs, EventBuffer* events, EventBuffer* nextEvents, RenderHeap* rheap){
  for(int i = 0; i < objs->objects.size(); i++){
    Object*     obj  = &objs->objects[i];
    ObjectType  type =  objs->objects[i].type;
    int         entI =  objs->objects[i].entityIndex;

    switch(type){
      case PLAYER: {
        Entity* e = &objs->entities[entI];
        updatePlayer(obj, e, events, nextEvents);
        renderPlayer(     e, rheap);
      } break;
      case ENVIRONMENT: {
        Entity* e = &objs->entities[entI];
        renderBlock (e, obj->data.envd.tile, obj->data.envd.depth, rheap);
      } break;
      default:
        printf("Unexpected object!\n");
        exit(-1);
    }
  }
}










void removeObject(ObjectVector* objs, int oIndex){
  Object o = objs->objects[oIndex];
  int eIndex = o.entityIndex;
  if(eIndex != -1){
    // Remove associated entity data
    objs->entities[eIndex] = objs->entities.back();
    objs->entities.pop_back();
    // Update entity index in parent of moved entity
    objs->objects[objs->entities[eIndex].parentIndex].entityIndex = eIndex;
  }
  // Remove object
  objs->objects[oIndex] = objs->objects.back();
  objs->entities.pop_back();
  // Update parent index in child of moved object
  objs->entities[objs->objects[oIndex].entityIndex].parentIndex = oIndex;
}










int createPlayer(ObjectVector* objs){
  Object player;
  player.type = PLAYER;
  player.data.plyd = PlayerData{0, 0, 1, 0};
  objs->objects.push_back(player);

  int objIndex = objs->objects.size()-1;

  Entity entity{0, 0, 0, 0, 48, 32, objIndex, true};
  objs->entities.push_back(entity);

  objs->objects.back().entityIndex = objIndex;
  return objIndex;
}










int createBlock(ObjectVector* objs, int tile, int depth){
  Object block;
  block.type = ENVIRONMENT;
  block.data.envd = EnvironmentData{tile, depth};
  objs->objects.push_back(block);

  int objIndex = objs->objects.size()-1;

  Entity entity{0, 0, 0, 0, 32, 32, objIndex, true};
  objs->entities.push_back(entity);

  objs->objects.back().entityIndex = objIndex;
  return objIndex;
}










Event isCollided(ObjectVector* objs, int entA, int entB){
  Entity* a = &objs->entities[entA];
  Entity* b = &objs->entities[entB];

  float aMaxX = a->x + a->w;
  float aMaxY = a->y + a->h;
  float bMaxX = b->x + b->w;
  float bMaxY = b->y + b->h;

  bool isSolid = a->isSolid && b->isSolid;

  if(isSolid        &&
     (a->x < bMaxX) &&
     (aMaxX > b->x) &&
     (a->y < bMaxY) &&
     (aMaxY > b->y)) {

    Event ret;
    ret.eventType = GAMEEVENT;
    ret.gameevent.type = COLLISIONEVENT;
    ret.gameevent.collisionEvent.entityA = entA;
    ret.gameevent.collisionEvent.entityB = entB;
    return ret;
  }

  Event ret;
  ret.eventType = VOIDEVENT;
  return ret;
}










void checkCollisions(ObjectVector* objs, EventBuffer* evts){
  // This won't scale all too well. Use space partitioning if it gets too slow.
  // Running some numbers, I figure this will start becoming an issue when we
  // are handling a couple hundred entities.

  for(int i = 0; i < objs->entities.size(); i++)
    for(int j = 0; j < objs->entities.size(); j++)
      if(i != j)
        pushEvent(evts, isCollided(objs, i, j));
}
