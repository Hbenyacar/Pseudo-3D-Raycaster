#include <iostream>
#include <sys/ioctl.h>
#include <unistd.h>
#include <vector>
#include <array>
#include <sys/select.h>
#include <termios.h>

using namespace std;

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

    vector<int> map = {
                    1, 1, 1, 1, 1, 1, 1, 1,
                    1, 0, 0, 0, 0, 0, 0, 1,
                    1, 0, 0, 0, 0, 0, 0, 1,
                    1, 0, 0, 0, 0, 0, 0, 1,
                    1, 0, 0, 0, 0, 0, 0, 1,
                    1, 0, 0, 0, 0, 0, 0, 1,
                    1, 0, 0, 0, 0, 0, 0, 1,
                    1, 1, 1, 1, 1, 1, 1, 1,
                };

    int num = 0;

    enableRawMode();
    char car = ' ';

    while (true) {
        
        std::cout << "\033[3J\033[H\033[2J";
        struct winsize w;
        ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);
        int width = w.ws_col;
        int height = w.ws_row - 10;
        std::cout << "Width: " << width << " Height: " << height << '\n';
        std::cout << "Press keys (press 'q' to quit)\n";
        std::cout << "You pressed: " << car << std::endl;
        if (kbhit()) {
            char c = getch();
            car = c;
            std::cout << "You pressed: " << c << std::endl;
            if (c == 'q') break;
        }

        for (int i = 0; i < height; i++) {
            for (int j = 0; j < width; j++) {
                cout << 1;
            }
            cout << '\n';
        }
        num++;
        usleep(10000); // small delay to reduce CPU usage
    }

    disableRawMode();

}