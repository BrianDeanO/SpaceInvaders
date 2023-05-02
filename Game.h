/*
    Class for Game Class
*/
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include "PlayerShip.h"
#include "AlienShip.h"
#include "Barrier.h"
#include "Bomb.h"
#include "Bullet.h"
#include "Interface.h"
using namespace std;

const unsigned long int NAME_LENGTH = 3;
const int DELAY = 15000;
const int BOMB_TIME = 50;
const int BULLET_TIME = 40;
const int PROJECTILE_MOVE_TIME_INDICATOR = 10;
const int ALIEN_MOVE_TIME_INDICATOR = 14;
const int SPECIAL_UFO_TIME_INDICATOR = 500 + (rand() % 300);
bool INVERTED = false;

class Game {
private:
    int highScore = 100; 
    string userName = "TRD";
    int playerInput;
    PlayerShip playerOne;
    AlienShip alienShips[ALIEN_ROWS][ALIEN_COLUMNS];
    AlienShip specialUFO;
    vector<Bullet> bullets;
    vector<Bomb> bombs;
    Barrier barriers[BARRIERS];
    Interface interface;

    WINDOW *mainWindow;

public:
    Game() {
        readFromFile();

        if ( (mainWindow = initscr()) == NULL ) {
            fprintf(stderr, "Error initialising ncurses.\n");
            exit(EXIT_FAILURE);
        }

        cbreak();
        noecho();
        curs_set(FALSE);
        keypad(mainWindow, TRUE);
        nodelay(mainWindow, TRUE);

        int yMax;
        int xMax;
        getmaxyx(stdscr, yMax, xMax);
        interface.setYMax(yMax);
        interface.setXMax(xMax);
        interface.setLevelCount(1);
        playerOne.setX(((xMax-1) / 2));
        int playerXPosition = ((xMax-1) / 2);
        string tempName;
        int gotHighScore = 0;

        // Setting the ships and barriers with their x and y starting coordinates
        initialSetUp();

        interface.drawBorder(mainWindow);
        interface.drawMainMenu(alienShips[0][0], alienShips[1][0], alienShips[2][0], specialUFO);

        while(playerInput != 'q' && playerInput != ' ') {
            playerInput = getch();

            switch (playerInput) {
                case 'q':
                    break;
                case ' ':
                    break;
            }

            if((playerInput != 'q') && (playerInput != ' ')) {
                clear();
                interface.drawBorder(mainWindow);
                interface.drawMainMenu(alienShips[0][0], alienShips[1][0], alienShips[2][0], specialUFO);
                refresh();
                usleep(DELAY); 
            }
        }

        clear();
        interface.drawBorder(mainWindow);
        drawScreen();
        refresh();

        while(playerInput != 'q') {
            playerInput = getch();

            if(playerOne.isAlive()) {
                switch (playerInput) {
                    case 'q':
                        break;

                    case 'p':
                        interface.setPauseStatus(true);
                        break;

                    case KEY_LEFT:
                        if (playerOne.getX() > 1) {
                            playerOne.setX(playerOne.getX() - 1);
                        }
                        break;
                
                    case KEY_RIGHT:
                        if (playerOne.getX() < (interface.getXMax() - 10)) {
                            playerOne.setX(playerOne.getX() + 1);
                        }
                        break;

                    case ' ':
                        if(interface.getPauseStatus()) {
                            interface.setPauseStatus(false);
                        } 
                        else if(interface.getNewLevelStatus()) {
                            interface.setNewLevelStatus(false);
                            clear();
                            playerOne.resetLives();
                            initialSetUp();
                            drawScreen();
                            refresh();
                        }
                        else if(playerOne.getBulletTime() >= BULLET_TIME) {
                            Bullet newBullet(playerOne.getX() + 3, playerOne.getY() - 1);
                            bullets.push_back(newBullet);
                            playerOne.setBulletTime(0);
                        }

                        break;
                }


                if((playerInput != 'q') && (playerInput != 'p')) {
                    clear();
                    if(!(interface.getPauseStatus()) && !(interface.getNewLevelStatus())) {
                        update(playerXPosition);
                    }
                    drawScreen();
                    refresh();
                    usleep(DELAY); 
                }
            } 
            
            else {
                // Game Over Screen when user gets High Score
                if((playerOne.getScore() >= getHighScore()) || gotHighScore) {
                    gotHighScore = 1;
                    switch (playerInput) {
                        case 'q':
                            setHighScore(playerOne.getScore());
                            break;

                        case ' ':
                            setUserName("???");
                            setHighScore(playerOne.getScore());
                            clear();
                            playerOne.resetLives();
                            playerOne.setScore(0);
                            initialSetUp();
                            drawScreen();
                            refresh();
                            break;

                        default:
                            break;
                    }

                    if((playerInput != 'q')) {
                        clear();
                        interface.drawHighScoreGameOver();
                        refresh();
                        usleep(DELAY); 
                    }

                }

                // Basic Game Over Screen
                else {
                    switch (playerInput) {
                        case 'q':
                            break;

                        case ' ':
                            clear();
                            playerOne.resetLives();
                            playerOne.setScore(0);
                            initialSetUp();
                            drawScreen();
                            refresh();
                            break;
                    }

                    if((playerInput != 'q')) {
                        clear();
                        interface.drawBaseGameOver();
                        refresh();
                        usleep(DELAY); 
                    }
                }
            }
        }

        clear();
        refresh();
        endwin();

        cout << "Game Over!!!\n";

        if(gotHighScore) {
            cout << "High Score Score Acheived - " << getHighScore() << endl;
            cout << "Enter Your 3-Digit Initial - ";
            getline(cin, tempName);

            if(tempName.length() == 0) {
                tempName = "???";
                setUserName(tempName);
                cout << "Staying Anonymous, huh? That's fine...\n";
            } 
            
            else {
                string threeDigitName = tempName.substr(0, 3);
                setUserName(threeDigitName);   
                cout << getUserName() << ", You're The Best Pilot In The Galaxy!!!\n";          
            }
        } 
        
        else {
            cout << "Score Acheived - " << playerOne.getScore() << endl;
        }

        saveToFile(getUserName(), getHighScore());
    }

    void initialSetUp() {
        int yMax = interface.getYMax();
        interface.setLifeShip("_/^\\_");
        interface.setTimeBetweenAlienShots(0);
        interface.setAlienDirection(1);
        interface.setAlienMovementTime(0);
        interface.setProjectileMovementTime(0);
        interface.setSpecialUFOMovementTime(0);
        interface.setPauseStatus(false);
        interface.setNewLevelStatus(false);
        interface.setAlienCount(ALIEN_ROWS * ALIEN_COLUMNS);
        playerOne.setLives(3);
        bullets.clear();
        bombs.clear();

        // Player Set up
        playerOne.setShip(interface.getMiddleX(), interface.getPlayerY(), BULLET_TIME);

        // Alien Set Up
        interface.setUpAliens(interface.getMiddleX(), alienShips);
        interface.setUpSpecialUFO(specialUFO, 1);

        // Barrier Set Up
        interface.setUpBarriers(interface.getMiddleX(), interface.getBarrierX(), yMax, barriers);
    }

    void drawScreen() {
        interface.drawBorder(mainWindow);
        interface.drawNavBar(getHighScore(), playerOne.getLives(), playerOne.getScore(), getUserName());

        if(interface.getPauseStatus()) {
            interface.drawPauseScreen();
        } 
        else if(interface.getNewLevelStatus()) {
            interface.drawNewLevelScreen();
        }
        else {
            playerOne.draw();
            drawBarriers();
            drawBullets();
            drawBombs();
            drawAlienShips();
        }
    }


    // update x and y for everything
    void update(int x) {
        updatePlayer();
        updateBarriers();
        updateAliens();

        if(interface.getSpecialUFOMovementTime() == SPECIAL_UFO_TIME_INDICATOR) {
            interface.setUpSpecialUFO(specialUFO, 0);
            interface.setSpecialUFOActive(true);
        }

        if(interface.getProjectileMovementTime() >= PROJECTILE_MOVE_TIME_INDICATOR) {
            updateBullets();
            updateBombs();
            interface.setProjectileMovementTime(0);
        } 

        interface.incrementAlienMovementTime();
        interface.incrementProjectileMovementTime(); 
        interface.incrementSpecialUFOMovementTime();
        playerOne.incrementBulletTime();
    }
    void updatePlayer() {
        if(playerOne.checkCollision(bombs)) {
            playerOne.resetShip(interface.getMiddleX());
        }
    }
    void updateAliens() {
        if(interface.getTimeBetweenAlienShots() == BOMB_TIME) {
            // Getting a random variable for which alien will shoot next
            int shooterRow = rand() % 3;
            int shooterColumn = rand() % 10;

            // Making sure the alien is alive
            while(!alienShips[shooterRow][shooterColumn].getAliveStatus()) {
                shooterRow = rand() % 3;
                shooterColumn = rand() % 10;
            }

            // Creating the new bomb
            Bomb newBomb(alienShips[shooterRow][shooterColumn].getX() + 3, 
                        alienShips[shooterRow][shooterColumn].getY() + 1);
            bombs.push_back(newBomb);
            
            interface.setTimeBetweenAlienShots(0);
        } else {
            interface.incrementTimeBetweenAlienShots();
        }

        if( (interface.getSpecialUFOActive()) && 
            ((interface.getAlienMovementTime() == (ALIEN_MOVE_TIME_INDICATOR - 3)) || (interface.getAlienMovementTime() == ALIEN_MOVE_TIME_INDICATOR))) {
            
            if((specialUFO.getX() > interface.getXMax()) || (specialUFO.getX() < 0)) {
                interface.setSpecialUFOActive(false);
                interface.setSpecialUFOMovementTime(0);
            }
            else {
                specialUFO.moveHorizontally(interface.getSpecialUFODirection());
            }
        }        

        if(interface.getAlienMovementTime() == ALIEN_MOVE_TIME_INDICATOR) {
            for(int i = 0; i < ALIEN_ROWS; i++) {
                if(INVERTED) {
                    break;
                } else {
                    for(int j = 0; j < ALIEN_COLUMNS; j++) {
                        if(alienShips[i][j].getAliveStatus()) {
                            if(((alienShips[i][j].getX() + 10) >= interface.getXMax()) || alienShips[i][j].getX() < 2) {
                                interface.invertAlienDirection();
                                INVERTED = true;
                                break;
                            } 
                            else {
                                alienShips[i][j].moveHorizontally(interface.getAlienDirection());
                                interface.setAlienMovementTime(0);
                            }
                        }                        
                    }
                }
            } 

            if(INVERTED) {
                for(int i = 0; i < ALIEN_ROWS; i++) {
                    for(int j = 0; j < ALIEN_COLUMNS; j++) {
                        if((i == 0) && (interface.getAlienDirection() == -1) && (j != (ALIEN_COLUMNS - 1))) {
                            alienShips[i][j].moveHorizontally(interface.getAlienDirection());
                        }
                        alienShips[i][j].moveDown();
                        alienShips[i][j].moveHorizontally(interface.getAlienDirection());
                    }
                }
                interface.setAlienMovementTime(0);
                INVERTED = false;
            }
        }

        for(int i = 0; i < ALIEN_ROWS; i++) {
            for(int j = 0; j < ALIEN_COLUMNS; j++) {
                if((alienShips[i][j].getAliveStatus()) && 
                   (alienShips[i][j].checkCollision(playerOne, bullets))) {
                    alienShips[i][j].destroyAlien();
                    interface.decrementAlienCount();
                    if(playerOne.isAlive()) {
                        playerOne.incrementScore(10 + (5 * alienShips[i][j].getType()));
                    }
                    if(interface.getAlienCount() == 0) {
                        interface.setNewLevelStatus(true);
                        interface.incrementLevelCount();
                    }
                }
            }
        }

        if(interface.getSpecialUFOActive()) {
            if(specialUFO.checkCollision(playerOne, bullets)) {
                interface.setSpecialUFOActive(false);
                interface.setSpecialUFOMovementTime(0);

                if(playerOne.isAlive()) {
                    playerOne.incrementScore(100 + (rand() % 69));
                }
            }
        }  
    }

    void updateBarriers() {
        for(int i = 0; i < BARRIERS; i++) {
            barriers[i].checkCollision(bombs);
        }
    }

    void drawBarriers() {
        for(int i = 0; i < BARRIERS; i++) {
            barriers[i].drawBarrier();
        }
    }

    void drawAlienShips() {
        for(int i = 0; i < ALIEN_ROWS; i++) {
            for(int j = 0; j < ALIEN_COLUMNS; j++) {
                if(alienShips[i][j].getAliveStatus()) {
                    alienShips[i][j].draw();
                }
            }
        }

        if(interface.getSpecialUFOActive()) {
            specialUFO.draw();
        }
    }

    // Update and Draw Functions for Bullets
    void updateBullets() {
        for(long unsigned int i = 0; i < bullets.size(); i++) {
            bullets[i].moveUp();

            if(bullets[i].checkEndOfScreen()) {
                bullets.erase(bullets.begin() + i);
            }
        }
    }
    void drawBullets() {
        for(long unsigned int i = 0; i < bullets.size(); i++) {
            bullets[i].drawBullet();
        }
    }

    // Update and Draw Functions for Bombs
    void updateBombs() {
        for(long unsigned int j = 0; j < bombs.size(); j++) {
            bombs[j].moveDown();

            if(bombs[j].checkEndOfScreen(interface.getYMax() - 1)) {
                bombs.erase(bombs.begin() + j);
            }
        }
    }
    void drawBombs() {
        for(long unsigned int j = 0; j < bombs.size(); j++) {
            bombs[j].drawBomb();
        }
    }


    // Function to save to file
    void saveToFile(string userName, int highScore) {
        fstream saveFile("highScore.txt", ios::out);
        if(saveFile) {
            saveFile << userName;
            saveFile << endl;
            saveFile << highScore;
        }
        saveFile.close();
    }
    // Function to read from file
    void readFromFile() {
        string fileTemp;
        int count = 0;
        fstream readFile("highScore.txt", ios::in);

        if(readFile) {
            getline(readFile, fileTemp);

            while(readFile) {
                // Username will always be first, then high score.
                if(count == 0) {
                    setUserName(fileTemp);
                } else {
                    setHighScore(stoi(fileTemp));
                }

                getline(readFile, fileTemp);
                count++;
            }  
        }

        readFile.close();
    }
    // Getters and setters for the username and highscore
    void setUserName(string name) {
        this->userName = name;
    }
    string getUserName() {
        return this->userName;
    }
    void setHighScore(int score) {
        this->highScore = score;
    }
    int getHighScore() {
        return this->highScore;
    }
};