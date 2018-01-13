#ifndef __ENTITY_HEADER__
#define __ENTITY_HEADER__


#include "types.hpp"
#include "graphics.hpp"
#include "events.hpp"
#include <vector>
#include <cstdint>
#include <cstdio>










struct Entity{
  float x, y, dx, dy, h, w;
  int parentIndex;
  bool isSolid;
};










class Object{
public:
  int entityIndex;
  virtual void update(Entity*, EventBuffer*, EventBuffer*){return;};
  virtual void render(Entity*, RenderHeap*){return;};
  Object(int index){ entityIndex = index; }
};










class PlayerObj : public Object{
public:
  float tryX, tryY, boost;
  int8_t jmpnum;
  void update(Entity*, EventBuffer*, EventBuffer*);
  void render(Entity*, RenderHeap*);
  PlayerObj(int index) : Object(index) { tryX = 0; tryY = 0; boost = 1; jmpnum =0; }
};










class BlockObj : public Object{
public:
  int tile, depth;
  void update(Entity*, EventBuffer*, EventBuffer*);
  void render(Entity*, RenderHeap*);
  BlockObj(int index, int t, int d) : Object(index) { tile = t; depth = d; }
};










// Things are separated for performance.
struct ObjectVector{
  std::vector<Object> objects;
  std::vector<Entity> entities;
};










void updateObjects  (ObjectVector*, EventBuffer*, EventBuffer*, RenderHeap*);
int  createPlayer   (ObjectVector*);
int  createBlock    (ObjectVector*, int, int);
void removeObject   (ObjectVector*, int);
Event isCollided    (Entity*, Entity*);
void checkCollisions(ObjectVector*, EventBuffer*);




#endif
