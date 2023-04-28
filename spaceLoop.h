/*
    Brian Dean
    Space Invaders
    CPTS 322
    26 March 2023
*/
#include <ncurses.h>
#include <iostream>
#include <cstring>
#include <string>
#include "PlayerShip.h"
#include "Interface.h"

int spaceLoop() {
    WINDOW *mainWindow;
    Interface interface;

    int ch;

    int yMax = 25;
    int xMax = 60;

    int      width = 23, height = 7;
    int      rows  = 25, cols   = 80;
    int      x = (cols - width)  / 2;
    int      y = (rows - height) / 2;

    PlayerShip playerOne;

    //   initscr();


    // Starting the ncurses mode and setting up screen for user input
    /*  Initialize ncurses  */
    if ( (mainWindow = initscr()) == NULL ) {
	    fprintf(stderr, "Error initialising ncurses.\n");
	    exit(EXIT_FAILURE);
    }

    //childWindow = newwin(xMax -2, xMax - 2, 1, 1);

    noecho();
    curs_set(FALSE);
    
   // getmaxyx(stdscr, yMax, xMax);
    int xPos = (xMax-1) / 2;
    int yPos = yMax - 3;

   // mainWindow = newwin(yMax, xMax, 0, 0);

    // if(wborder(mainWindow, '|', '|', '_', '_', '*','*', '*', '*' ) < 0) {
    //     fprintf(stderr, "Error creating border.\n");
	//     exit(EXIT_FAILURE);
    // }

    interface.drawBorder(mainWindow);


   // childWindow = subwin(mainWindow, yMax-1, xMax-1, 1, 1);
    keypad(mainWindow, TRUE);

    // mvaddstr(yPos-1, xPos, playerOne.getTopBody().c_str());
    // mvaddstr(yPos, xPos, playerOne.getMiddleBody().c_str());
    // mvaddstr(yPos+1, xPos, playerOne.getBottomBody().c_str());
    playerOne.draw(yPos, xPos);

    refresh();

    // cout << "Lines - " << LINES << "Cols - " << COLS << endl;
    // cout << "max x - " << xMax << "max y - " << yMax << endl;
    // cout << "x pos - " << xPos << "y pos - " << yPos << endl;
    //     cout << "his x - " << x << "hsi y - " << y << endl;

    bool playerShot = false;
    int playerBulletYPos = yPos-3;
    int playerBulletXPos;


    while ( (ch = getch()) != 'q' ) {
        switch ( ch ) {
            case KEY_LEFT:
                if ( xPos > 0 ) {
                    xPos--;
                }
                break;
        
            case KEY_RIGHT:
                if ( xPos < (xMax-10) ) {
                    xPos++;
                }
                break;

            case ' ':
                playerShot = true;
                playerBulletXPos = xPos;
               // mvaddstr(yPos-3, xPos, "&");
                break;


        }

        if(playerShot) {
            clear();
            if(interface.isPlayerBulletEnd(playerBulletYPos)) {
                //playerOne.drawPlayerShip(yPos, xPos);
                mvaddstr(yPos-1, xPos, playerOne.getTopBody().c_str());
                mvaddstr(yPos, xPos, playerOne.getMiddleBody().c_str());
                mvaddstr(yPos+1, xPos, playerOne.getBottomBody().c_str());
                playerBulletYPos = yPos-3;
                playerShot = false;
            } 
            
            else {
                mvaddstr(playerBulletYPos, xPos+3, "!");
                //playerOne.drawPlayerShip(yPos, xPos);
                mvaddstr(yPos-1, xPos, playerOne.getTopBody().c_str());
                mvaddstr(yPos, xPos, playerOne.getMiddleBody().c_str());
                mvaddstr(yPos+1, xPos, playerOne.getBottomBody().c_str());
                playerBulletYPos--;
            }
            refresh();
            usleep(ESCDELAY);
        } 
        
        else {
            clear();
            playerOne.draw(yPos, xPos);
            // mvaddstr(yPos-1, xPos, playerOne.getTopBody().c_str());
            // mvaddstr(yPos, xPos, playerOne.getMiddleBody().c_str());
            // mvaddstr(yPos+1, xPos, playerOne.getBottomBody().c_str());
            refresh();
        }
    }


    //delwin(childWindow);
    delwin(mainWindow);
    endwin();
    return 0;
}