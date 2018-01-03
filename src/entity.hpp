#ifndef __ENTITY_HEADER__
#define __ENTITY_HEADER__


#include "types.hpp"
#include "graphics.hpp"
#include "events.hpp"
#include <vector>
#include <cstdint>










struct PlayerData{
  float tryX, tryY, boost;
  int8_t jmpnum;
};










struct EnvironmentData{
  float h, w;
  bool isSolid;
};










union ObjectData{
  PlayerData      plyd;
  EnvironmentData envd;
};










enum ObjectType{
  PLAYER, ENEMY, ENVIRONMENT, TIMER
};

struct Object{
  ObjectType type;
  ObjectData data;
  int entityIndex;
};











struct Entity{
  float x, y, dx, dy;
  int parentIndex;
};










// Things are separated for performance.
struct ObjectVector{
  std::vector<Object> objects;
  std::vector<Entity> entities;
};










void updateObject(ObjectVector*, EventBuffer*, EventBuffer*, RenderHeap*);
int  createPlayer(ObjectVector*);
void removeObject(ObjectVector*, int);






#endif
