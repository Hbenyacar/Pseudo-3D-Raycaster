#pragma once
#include "Direction.h"
#define ld long double

struct Player
{
    ld x;
    ld y;
    ld angle;

   Player(ld startX, ld startY);

   ld move(Direction direction);
   ld calcX();
   ld calcY();
   ld turn(Direction direction);
   void setCoord(int dir, int turn);
   void epsilonClamp();
};
