#include <iostream>
#include <cmath>
#include "Ray.h"
#include "Wall.h"

#include <fstream>

using namespace std;
#define ld long double

#define MOVE_SPEED 1
#define CELL_SIZE 1
#define HORIZONTAL WallType::HORIZONTAL
#define VERTICAL WallType::VERTICAL
#define WALL_HEIGHT 1

void debugLog(const std::string& msg) {
    static std::ofstream debugFile("debug.log", std::ios::app);
    debugFile << msg << '\n';
    debugFile.flush();  // ← REQUIRED for real-time logging
}

Ray::Ray(ld angle, ld startX, ld startY, vector<vector<int>> grid) 
    : angle(angle), startX(startX), startY(startY), grid(grid) {}

Wall Ray::hitWall() {
    ld horizontal = distHoriWall();
    ld vertical = distVertWall();

    WallType type;
    if (vertical < horizontal) {
        type = VERTICAL;
        return Wall(type, vertical, WALL_HEIGHT);
    } else {
        type = HORIZONTAL;
        return Wall(type, horizontal, WALL_HEIGHT);
    }
}

/* First Hit Horizontal Wall at player's angle */

ld Ray::distHoriWall() {
    ld yn, x, y, xn, totalDist, xMove, yMove, checkLower;

    ld radians = angle * (M_PI / 180);

    if (sin(radians) == 0) {
        return INT_MAX;
    }

    bool facingUp = sin(radians) > 0;
    bool facingDown = !facingUp;

    if (facingUp) { yn = ceil(startY) - startY; y = ceil(startY);}
    else { yn = startY - floor(startY); y = floor(startY); }

    // to check below grid[x][y-1] if ray is facing down

    if (facingUp) { checkLower = 0; } 
    else { checkLower = 1;}

    xn = yn / tan(radians);
    x = startX + xn;

    totalDist = sqrt(pow(xn, 2) + pow(yn, 2)); 
    if (facingUp) { yMove = CELL_SIZE;} 
    else { yMove = -CELL_SIZE;}

    xMove = yMove / tan(radians);

    while (true) {
        if (outOfBounds(x, y - checkLower)) {break;}
        if (grid[floor(x)][y - checkLower] == 1) {
            debugLog(to_string(floor(x)) + " " + to_string(y - checkLower));
            debugLog("Total Distance HORI: " + to_string(totalDist));
            break;
        }
        x += xMove;
        y += yMove;
        totalDist += sqrt(pow(xMove, 2) + pow(yMove, 2));
    }

    return totalDist;
}

/* First Hit Vertical Wall at player's angle */

ld Ray::distVertWall() {

    ld yn, x, y, xn, totalDist, xMove, yMove, checkLower;

    ld radians = angle * (M_PI / 180);

    if (cos(radians) == 0) {
        return INT_MAX;
    }

    bool facingRight = cos(radians) > 0;
    bool facingLeft = !facingRight;

    if (facingRight) { xn = ceil(startX) - startX; x = ceil(startX);}
    else { xn = startX - floor(startX); x = floor(startX); }

    // to check below grid[x][y-1] if ray is facing down

    if (facingRight) { checkLower = 0; } 
    else { checkLower = 1;}

    yn = xn * tan(radians);
    y = startY + yn;

    totalDist = sqrt(pow(xn, 2) + pow(yn, 2)); 
    if (facingRight) { xMove = CELL_SIZE;} 
    else { xMove = -CELL_SIZE;}

    yMove = xMove * tan(radians);

    while (true) {
        if (outOfBounds(x - checkLower, y)) {break;}
        if (grid[x - checkLower][floor(y)] == 1) {
            debugLog(to_string(floor(x)) + " " + to_string(y - checkLower));
            debugLog("Total Distance VERT: " + to_string(totalDist));
            break;
        }
        x += xMove;
        y += yMove;
        totalDist += sqrt(pow(xMove, 2) + pow(yMove, 2));
    }

    return totalDist;
}

bool Ray::outOfBounds(ld x, ld y) {
    if (x >= grid.size() || y >= grid.size() || x < 0 || y < 0) {
        debugLog("Total Distance: INFINITE");
        return true;
    }
    return false;
}

