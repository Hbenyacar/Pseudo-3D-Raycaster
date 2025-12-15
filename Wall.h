#define ld long double

enum class WallType {
    HORIZONTAL, VERTICAL
};

struct Wall {
    WallType type;
    ld distToPlayer;
    ld height;

    Wall(WallType type, ld distToPlayer, ld height);
    
    ld projectedHeight(ld FOV, ld screenWidth);
    char character();
};