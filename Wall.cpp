#include <iostream>
#include "Wall.h"
#include <cmath>
using namespace std;
#define ld long double
#define HORIZONTAL WallType::HORIZONTAL
#define VERTICAL WallType::VERTICAL

Wall::Wall(WallType type, ld distToPlayer, ld height)
        : type(type), distToPlayer(distToPlayer), height(height) {}

ld Wall::projectedHeight(ld FOV, ld screenWidth) {
    ld p, radians;
    radians = (FOV) * (M_PI / 180);

    p = screenWidth / (2 * tan(radians / 2));

    return ((height * p) / distToPlayer);
}

char Wall::character() {
    switch (type)
    {
    case HORIZONTAL:
        return '=';
    case VERTICAL:
        return '#';
    default:
        return '\0';
    }
}