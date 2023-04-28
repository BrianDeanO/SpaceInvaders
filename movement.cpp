    //movement is in a for loop going from side to side

#include <ncurses.h>
#include <unistd.h>
#include <iostream>
using namespace std;
#define DELAY 30000

int main(int argc, char *argv[]) {
 int x = 0, y = 0;
 int max_y = 0, max_x = 0;
 int next_x = 0;
 int direction = 1;

 initscr();
 noecho();
 curs_set(FALSE);


// // WINDOW FOR TEXT BOX
// WINDOW *win ...
//  box(win, o,o);

//WINDOW * mainwin, * childwin;

 // Global var `stdscr` is created by the call to `initscr()`
 getmaxyx(stdscr, max_y, max_x);

 for(int i = 0; i < max_y; i++) {
    mvaddstr(i, max_x-10, "|");
    mvaddstr(i, 10, "    | ");
 }

  for(int j = 0; j < max_x; j++) {
    mvaddstr(10, j, "_");
 }

    cout << "Max-y:" << max_y << "Max-x" << max_x << endl;
    mvaddstr(max_y, 10, "mmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmmm");


        mvaddstr(y-1, x, "    | ");
        mvaddstr(y, x, " __/\\__");
        mvaddstr(y+1, x, "/______\\");


 while(1) {
    clear();
        mvaddstr(y-1, x, "    | ");
        mvaddstr(y, x, " __/\\__");
        mvaddstr(y+1, x, "/______\\");
    refresh();

    usleep(DELAY);

    next_x = x + direction;

    if (next_x+10 >= max_x || next_x < 0) {
        direction*= -1;
    } else {
        x+= direction;
    }
    }

   endwin();
}