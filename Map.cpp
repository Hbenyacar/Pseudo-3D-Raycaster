#include <iostream>
#include "Map.h"
#include "Player.h"
#include "Ray.h"
#include "Wall.h"
using namespace std;

Map::Map(vector<vector<int>> grid) 
    : grid(grid) {}

void Map::draw(Player player) {
    // for (int i = grid.size() - 1; i >= 0; i--) {
    //     for (int j = 0; j < grid.size(); j++) {
    //         if (i == floor(player.y) && j == floor(player.x)) {
    //             cout << arrow(player);
    //         } else {
    //             (grid[i][j] == 1) ? cout << "#" : cout << ".";
    //         }
    //         cout << " ";
    //     }
    //     cout << endl;
    // }

    for (int i = 0; i < grid.size(); i++) {
        for (int j = 0; j < grid.size(); j++) {
            if (j == floor(player.y) && i == floor(player.x)) {
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
    ld angle = player.angle;

    if (angle < 22.5 || angle >= 338.5) {return "↓";}
    else if (angle >= 22.5 && angle < 67.5) {return "↘";}
    else if (angle < 112.5 && angle >= 67.5) {return "→";}
    else if (angle < 157.5 && angle >= 112.5) {return "↗";}
    else if (angle < 202.5 && angle >= 157.5) {return "↑";}
    else if (angle < 247.5 && angle >= 202.5) {return "↖";}
    else if (angle < 292.5 && angle >= 247.5) {return "←";}
    else if (angle < 338.5 && angle >= 292.5) {return "↙";}

    if (angle < 22.5 || angle >= 338.5) {return "→";}
    else if (angle >= 22.5 && angle < 67.5) {return "↗";}
    else if (angle < 112.5 && angle >= 67.5) {return "↑";}
    else if (angle < 157.5 && angle >= 112.5) {return "↖";}
    else if (angle < 202.5 && angle >= 157.5) {return "←";}
    else if (angle < 247.5 && angle >= 202.5) {return "↙";}
    else if (angle < 292.5 && angle >= 247.5) {return "↓";}
    else if (angle < 338.5 && angle >= 292.5) {return "↘";}
}

void Map::drawWalls(ld screenWidth, ld screenHeight, Player player) {
    ld FOV = player.fov;
    ld angle = player.angle;
    ld raySpacing = FOV / screenWidth;
    ld leftMostAngle = angle + (FOV / 2);
    

    vector<vector<char>> view(screenHeight, vector<char>(screenWidth, ' '));

    for (int i = 0; i < screenWidth; i++) {

        ld castAngle = leftMostAngle - (i * raySpacing);

        Ray ray = Ray(castAngle, player.x, player.y, grid); 
        Wall wall = ray.castRay();

        char c = wall.character();
        ld projectedHeight = wall.projectedHeight(player.fov, screenWidth, screenHeight);

        for (int j = 0; j < projectedHeight/2; j++) {
            view[screenHeight/2 + j][i] = c;
            view[screenHeight/2 - j][i] = c;
        }
    }

    print(view);
}

void Map::print(vector<vector<char>> view) {
    cout << view.size() << endl;
    for (int i = 0; i < view.size(); i++) {
        for (int j = 0; j < view[i].size(); j++) {
            cout << view[i][j];
        }
        cout << '\n';
    }
}

