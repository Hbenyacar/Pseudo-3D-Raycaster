#include <iostream>
#include "Map.h"
using namespace std;

Map::Map(Player player, vector<vector<int>> grid) 
    : player(player), grid(grid) {}

void Map::draw() {
    for (int i = grid.size() - 1; i >= 0; i--) {
        for (int j = 0; j < grid.size(); j++) {
            cout << grid[i][j];
        }
        cout << endl;
    }
}