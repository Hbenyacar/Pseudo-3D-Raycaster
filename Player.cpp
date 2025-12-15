#include <cmath>
#include "Player.h"

#define ld long double

#define TURN_SPEED 5
#define MOVE_SPEED 1
#define POS_DIR 1
#define NEG_DIR -1
#define EPSILON 1e-10
#define NO_TURN 0
#define L_TURN 1
#define R_TURN 2

Player::Player (ld startX, ld startY, Map map, ld fov)
    : x(startX), y(startY), angle(0), map(map), fov(fov) {}

ld Player::move(Direction direction) {
    switch (direction)
    {
    case Direction::FORWARD: setCoord(POS_DIR, NO_TURN); break;
    case Direction::BACKWARD: setCoord(NEG_DIR, NO_TURN); break;
    case Direction::LEFT: setCoord(POS_DIR, L_TURN); break;
    case Direction::RIGHT: setCoord(POS_DIR, R_TURN); break;
    }
    return -1;
}

ld Player::turn(Direction direction) {
    switch (direction)
    {
    case Direction::LEFT: (angle < TURN_SPEED) ? angle = 360 : 
                            angle -= TURN_SPEED; break;
    case Direction::RIGHT: (angle > (360 - TURN_SPEED)) ? angle = 0 : 
                            angle += TURN_SPEED; break;
    }
    return angle;
}

void Player::setCoord(int dir, int turn) {
    ld originalAngle = angle;
    switch (turn) {
        case L_TURN: angle += 90; break; // Left = Go forward at angle + 90 degree
        case R_TURN: angle -= 90; break; // Right = Go forward at angle - 90 degree
        default: break;
    }

    x += dir * calcX(); // Distance moved in x direction
    y += dir * calcY(); // Distance moved in y direction

    // Round to 0 if small enough
    epsilonClamp();

    angle = originalAngle;
}

ld Player::calcX() {
    ld radians = angle * (M_PI / 180);
    ld x = (ld) MOVE_SPEED * cos(radians);
    return x;
}

ld Player::calcY() {
    ld radians = angle * (M_PI / 180);
    ld y = (ld) MOVE_SPEED * sin(radians);
    return y;
}

void Player::epsilonClamp() {
    if (abs(x) < EPSILON) {x = 0;}
    if (abs(y) < EPSILON) {y = 0;}
}