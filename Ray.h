#define ld long double

using namespace std;

struct Wall;

struct Ray {
    ld angle;
    ld startX;
    ld startY;
    vector<vector<int>> grid;

    Ray(ld angle, ld startX, ld startY, vector<vector<int>> grid);
    ld distHoriWall();
    ld distVertWall();
    bool outOfBounds(ld x, ld y);
    Wall hitWall();
};