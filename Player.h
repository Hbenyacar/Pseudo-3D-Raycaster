#pragma once
#include "Direction.h"
#include "Map.h"
#define ld long double

struct Player
{
    ld x;
    ld y;
    ld angle;
    ld fov;
    Map map;

   Player(ld startX, ld startY, Map map, ld fov);

   ld move(Direction direction);
   ld calcX();
   ld calcY();
   ld turn(Direction direction);
   void setCoord(int dir, int turn);
   void epsilonClamp();
};
