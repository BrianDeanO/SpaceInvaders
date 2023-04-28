#include <stdlib.h>
#include <stdio.h>
#include <ncurses.h>
using namespace std;
 
int main(void) {
 
    WINDOW * mainwin, * childwin;
    int ch;
    
    int      width = 23, height = 7;
    int      rows  = 25, cols   = 80;
    int      x = (cols - width)  / 2;
    int      y = (rows - height) / 2;
   
    /*  Initialize ncurses  */
    if ( (mainwin = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(EXIT_FAILURE);
    }
 
    /*  Switch of echoing and enable keypad (for arrow keys)  */
    noecho();
    keypad(mainwin, TRUE);
 
    mvaddstr(y-1, x, "    | ");
    mvaddstr(y, x, " __/\\__");
    mvaddstr(y+1, x, "/______\\");
 
    refresh();
 
 
    /*  Loop until user hits 'q' to quit  */
    

    // This movement code will 
    while ( (ch = getch()) != 'q' ) {
        switch ( ch ) {
            // case KEY_UP:
            //     if ( y > 0 )
            //     --y;
            //     break;
        
            // case KEY_DOWN:
            //     if ( y < (rows - height) )
            //     ++y;
            //     break;
        
            case KEY_LEFT:
                if ( x > 0 )
                --x;
                break;
        
            case KEY_RIGHT:
                if ( x < (cols - width) )
                ++x;
                break;
        
            case KEY_HOME:
                x = 0;
                y = 0;
                break;
        
            case KEY_END:
                x = (cols - width);
                y = (rows - height);
                break;
    
        }

        // This is clearing the screen, repainting, and refreshing
        clear();
	    mvaddstr(y-1, x, "    | ");
        mvaddstr(y, x, " __/\\__");
        mvaddstr(y+1, x, "/______\\");
        refresh();
    }
 
 
    /*  Clean up after ourselves  */
 
    delwin(childwin);
    delwin(mainwin);
    endwin();
    refresh();
 
    return EXIT_SUCCESS;
}