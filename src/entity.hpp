#ifndef __ENTITY_HEADER__
#define __ENTITY_HEADER__


#include "types.hpp"
#include "graphics.hpp"
#include "events.hpp"










enum ObjectType{
  PLAYER, ENEMY, ENVIRONMENT, TIMER
};

struct Object{
  ObjectType type;
  void* data;
  int   EntityIndex;
};










struct Entity{
  float x, y, dx, dy, jmpnum;
  Object* parent;
};










void updateObject(Object*, EventBuffer*, RenderHeap*);






#endif
