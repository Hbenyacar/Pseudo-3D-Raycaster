#include <vector>
#include "Player.h"

using namespace std;

struct Map {

    Player player;
    vector<vector<int>> grid;

    Map(Player player, vector<vector<int>> grid);
    void draw();
    
};