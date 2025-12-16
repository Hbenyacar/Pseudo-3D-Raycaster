#pragma once
#include <vector>

#define ld long double
using namespace std;

struct Player;

struct Map {

    vector<vector<int>> grid;

    Map(vector<vector<int>> grid);
    void draw(Player player);
    string arrow(Player player);
    void drawWalls(ld width, ld height, Player player);
    void print(vector<vector<char>> view);
};