#include <iostream>
#include "Wall.h"
#include "Ray.h"
#include <cmath>
using namespace std;
#define ld long double
#define HORIZONTAL WallType::HORIZONTAL
#define VERTICAL WallType::VERTICAL

Wall::Wall(WallType type, ld distToPlayer, ld height)
        : type(type), distToPlayer(distToPlayer), height(height) {}


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

ld Wall::projectedHeight(ld FOV, ld screenWidth, ld screenHeight) {
    ld p, radians;
    radians = (FOV) * (M_PI / 180);

    p = screenWidth / (2 * tan(radians / 2));

    ld projectedHeight = ((height * p) / distToPlayer);
    ld adjustedHeight = adjustHeight(projectedHeight, screenHeight);
    return adjustedHeight;
}

int Wall::adjustHeight(ld projectedHeight, ld screenHeight) {
    int adjustedHeight;
    if (projectedHeight >= screenHeight) {
        projectedHeight = screenHeight - 1;
    }
    adjustedHeight = floor(projectedHeight);
    if ((adjustedHeight % 2) != 0) {
        adjustedHeight--;
    }

    if (projectedHeight < 0) {
        adjustedHeight = 0;;
    }

    return adjustedHeight;
}