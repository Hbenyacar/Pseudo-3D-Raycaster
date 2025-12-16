#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <array>
#include <sys/select.h>
#include <termios.h>
#include <iomanip>
#include "Direction.h"
#include "Player.h"
#include "Ray.h"
#include "Wall.h"
#include "globals.h"

using namespace std;
extern bool glo;

#define FOV 60 // in degrees

vector<vector<int>> MAP = {
                            {1, 1, 1, 1, 1, 1, 1, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 1, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1},
                            {1, 0, 0, 0, 0, 0, 0, 1},
                            {1, 1, 1, 1, 1, 1, 1, 1}
                            };

termios orig_termios;

void enableRawMode() {
    tcgetattr(STDIN_FILENO, &orig_termios);
    termios raw = orig_termios;
    raw.c_lflag &= ~(ICANON | ECHO); // disable buffering and echo
    raw.c_cc[VMIN] = 0;              // return immediately if no input
    raw.c_cc[VTIME] = 0;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void disableRawMode() {
    tcsetattr(STDIN_FILENO, TCSANOW, &orig_termios);
}

bool kbhit() {
    fd_set set;
    struct timeval timeout;
    FD_ZERO(&set);
    FD_SET(STDIN_FILENO, &set);

    timeout.tv_sec = 0;
    timeout.tv_usec = 0;

    return select(STDIN_FILENO + 1, &set, nullptr, nullptr, &timeout) > 0;
}

char getch() {
    char c;
    read(STDIN_FILENO, &c, 1);
    return c;
}


int main() {

    int num = 0;

    enableRawMode();
    char car = ' ';

    Map map = Map(MAP);
    Player player = Player(3, 3, map, FOV);
    ld projectedHeight = 0;
    ld dist = 0;

    while (true) {
        
        std::cout << "\033[3J\033[H\033[2J";
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int width = w.ws_col;
        int height = w.ws_row - 20;
        std::cout << "Width: " << width << " Height: " << height << '\n';
        std::cout << "Press keys (press 'q' to quit)\n";
        std::cout << "You pressed: " << car << std::endl;
        std::cout << "Position: " << setprecision(4) << player.x << " " << setprecision(4) << player.y << endl;
        std::cout << "Angle: " << player.angle << endl;
        std::cout << "projected height: " << projectedHeight << endl;
        std::cout << "dist: " << dist << endl;
        map.draw(player);
        if (kbhit()) {
            char c = getch();
            car = c;
            std::cout << "You pressed: " << c << std::endl;
            if (c == 'q') break;
            else if (c == 'w') player.move(Direction::FORWARD);
            else if (c == 's') player.move(Direction::BACKWARD);
            else if (c == 'a') player.move(Direction::LEFT);
            else if (c == 'd') player.move(Direction::RIGHT);
            else if (c == 'C') player.turn(Direction::LEFT);
            else if (c == 'D') player.turn(Direction::RIGHT);
            else if (c == 'r') {
                globalVariable = 1;
                Ray ray = Ray(player.angle, player.x, player.y, map.grid); 
                Wall wall = ray.castRay();
                dist = wall.distToPlayer;
                char c = wall.character();
                projectedHeight = wall.projectedHeight(player.fov, width, height);
                globalVariable = 0;
            }
        }

        player.drawView(width, height);

        // for (int i = 0; i < height; i++) {
        //     for (int j = 0; j < width; j++) {
        //         cout << i;
        //     }
        //     cout << '\n';
        // }
        // num++;
        usleep(5000); // small delay to reduce CPU usage
    }

    disableRawMode();

}