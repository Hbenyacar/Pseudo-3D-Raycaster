#include <iostream>
#include "Map.h"
#include "Player.h"
using namespace std;

Map::Map(vector<vector<int>> grid) 
    : grid(grid) {}

void Map::draw(Player player) {
    for (int i = grid.size() - 1; i >= 0; i--) {
        for (int j = 0; j < grid.size(); j++) {
            if (i == floor(player.y) && j == floor(player.x)) {
                cout << arrow(player);
            } else {
                (grid[i][j] == 1) ? cout << "#" : cout << ".";
            }
            cout << " ";
        }
        cout << endl;
    }
}

string Map::arrow(Player player) {
    if (player.angle < 22.5 || player.angle >= 338.5) {return "→";}
    else if (player.angle >= 22.5 && player.angle < 67.5) {return "↗";}
    else if (player.angle < 112.5 && player.angle >= 67.5) {return "↑";}
    else if (player.angle < 157.5 && player.angle >= 112.5) {return "↖";}
    else if (player.angle < 202.5 && player.angle >= 157.5) {return "←";}
    else if (player.angle < 247.5 && player.angle >= 202.5) {return "↙";}
    else if (player.angle < 292.5 && player.angle >= 247.5) {return "↓";}
    else if (player.angle < 338.5 && player.angle >= 292.5) {return "↘";}
}