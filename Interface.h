/*
    Class for Interface
*/
#pragma once
#include <ncurses.h>
#include <unistd.h>
#include <iostream>
#include <cstring>
#include <string>
#include <time.h>
#include "PlayerShip.h"

class Interface {
private:
    int yMax;
    int xMax;
    int middleX;
    int alienDirection;
    int alienMovementTime;
    int projectileMovementTime;
    int timeBetweenAlienShots;
    string lifeShip;
    bool pauseStatus;
    int alienCount;
    bool newLevelStatus;
    int levelCount;
    bool specialUFOActive;
    int specialUFOMovementTime;
    int specialUFODirection;

public:

    // Alien Ship Setup
    void setUpAliens(int middleX, AlienShip alienShips[ALIEN_ROWS][ALIEN_COLUMNS]) {
        for(int i = 0; i < ALIEN_ROWS; i++) {
            for(int j = 0; j < ALIEN_COLUMNS; j++) {
                if(i == 0) {
                    alienShips[i][j].setAlienShip(0, ((middleX-40) + (j*8)), 6);
                }
                else if((i == 1) || (i == 2)) {
                    alienShips[i][j].setAlienShip(1, ((middleX-40) + (j*8)), 6 + (i*3));
                }
                else if((i == 3) || (i == 4)) {
                    alienShips[i][j].setAlienShip(2, ((middleX-40) + (j*8)), 4 + (i*4));
                }
            }
        }
    }

    // Barrier Set Up
    void setUpBarriers(int middleX, int barrierX, int yMax, Barrier barriers[BARRIERS]) {
        for(int i = 0; i < BARRIERS; i++) {
            if((i == 0) || (i == 1)) {
                barriers[i].setBarrier((middleX - (barrierX * (2-i))), (yMax - 6));
            } else {
                barriers[i].setBarrier((middleX + (barrierX * (i-1))), (yMax - 6));
            }
        }
    }

    void setPauseStatus(bool status) {
        this->pauseStatus = status;
    }
    bool getPauseStatus() {
        return this->pauseStatus;
    }

    void setAlienMovementTime(int t) {
        this->alienMovementTime = t;
    }
    int getAlienMovementTime() {
        return this->alienMovementTime;
    }
    void incrementAlienMovementTime() {
        this->alienMovementTime++;
    }

    void setProjectileMovementTime(int t) {
        this->projectileMovementTime = t;
    }
    int getProjectileMovementTime() {
        return this->projectileMovementTime;
    }
    void incrementProjectileMovementTime() {
        this->projectileMovementTime++;
    }

    void setTimeBetweenAlienShots(int t) {
        this->timeBetweenAlienShots = t;
    }
    int getTimeBetweenAlienShots() {
        return this->timeBetweenAlienShots;
    }
    void incrementTimeBetweenAlienShots() {
        this->timeBetweenAlienShots++;
    }

    int getYMax() {
        return this->yMax;
    }
    int getXMax() {
        return this->xMax;
    }
    void setYMax(int y) {
        this->yMax = y;
    }
    void setXMax(int x) {
        this->xMax = x;
    }
    int getPlayerY() {
        return (this->yMax - 3);
    }
    int getMiddleX() {
        return (((this->xMax)-1) / 2);
    }
    int getBarrierX() {
        return (this->getMiddleX() / 3);
    }
    void setAlienDirection(int direction) {
        this->alienDirection = direction;
    }
    void invertAlienDirection() {
        this->alienDirection *= -1;
    }
    bool checkAlienBorder(int xPos) {
        if(((xPos + 10) >= this->getXMax()) || xPos < 2) {
            return true;
        } else {
            return false;
        }
    }
    int getAlienDirection() {
        return this->alienDirection;
    }

    void setLifeShip(string ship) {
        this->lifeShip = ship;
    }
    string getLifeShip() {
        return this->lifeShip;
    }

    void drawNavBar(int highScore, int lifeCount, int currentScore, string userName) {

        string currentScoreTitle = "CURRENT SCORE - " + to_string(currentScore);
        mvaddstr(2, (getMiddleX() - 40), (currentScoreTitle).c_str());

        string highScoreTitle = "HIGH SCORE - " + userName + " " + to_string(highScore);
        mvaddstr(2, (getMiddleX() - 4), (highScoreTitle).c_str());

        string lifeShipString = "LIVES - ";
        mvaddstr(2, (getMiddleX() + 29), (lifeShipString).c_str());

        for(int i = 0; i < lifeCount; i++) {
            mvaddstr(2, ((getMiddleX() + 30) + (7 * (i+1))), (getLifeShip()).c_str());
        }
    }

    void drawBorder(WINDOW* mainWin) {
        if(wborder(mainWin, '|', '|', '_', '_', '*','*', '*', '*' ) < 0) {
            fprintf(stderr, "Error creating border.\n");
            exit(EXIT_FAILURE);
        }
    }

    void drawMainMenu(AlienShip typeOne, AlienShip typeTwo, AlienShip typeThree, AlienShip UFO) {
        string spaceInvadersTitle = "SPACE INVADERS";
        string playMessage = "PRESS SPACEBAR TO PLAY";
        string pointValues[] = {"= 10 pts", "= 15 pts", "= 20 pts", "= ?? pts"};
        string controls[] = {"CONTROLS", "SHOOT - SPACEBAR", "MOVE - LEFT/RIGHT ARROW KEYS"};

        mvaddstr(((getYMax() / 2) - 10), getMiddleX(), (spaceInvadersTitle).c_str());
    
        typeOne.printAlienShipMainMenuStats(((getYMax() / 2) - 6), (getMiddleX() + 30));
        mvaddstr(((getYMax() / 2) - 6), (getMiddleX() + 40), (pointValues[0]).c_str());

        typeTwo.printAlienShipMainMenuStats(((getYMax() / 2) - 3), (getMiddleX() + 30));
        mvaddstr(((getYMax() / 2) - 3), (getMiddleX() + 40), (pointValues[1]).c_str());

        typeThree.printAlienShipMainMenuStats(((getYMax() / 2)), (getMiddleX() + 30));
        mvaddstr(((getYMax() / 2)), (getMiddleX() + 40), (pointValues[2]).c_str());

        UFO.printAlienShipMainMenuStats(((getYMax() / 2) + 3), (getMiddleX() + 30));
        mvaddstr(((getYMax() / 2) + 3), (getMiddleX() + 40), (pointValues[3]).c_str());

        mvaddstr(((getYMax() / 2) - 3), (getMiddleX() - 20), (controls[0]).c_str());
        mvaddstr(((getYMax() / 2) - 2), (getMiddleX() - 24), (controls[1]).c_str());
        mvaddstr(((getYMax() / 2) - 1), (getMiddleX() - 30), (controls[2]).c_str());

        mvaddstr(((getYMax() / 2) + 6), (getMiddleX() - 4), (playMessage).c_str());
    }

    void drawPauseScreen() {
        string pauseMessage = "GAME PAUSED";
        string continueMessage = "PRESS SPACEBAR TO CONTINUE";
        mvaddstr((getYMax() / 2), getMiddleX(), (pauseMessage).c_str());
        mvaddstr(((getYMax() / 2) + 1), (getMiddleX() - 7), (continueMessage).c_str());
    }

    void drawHighScoreGameOver() {
        string gameOverMessage = "GAME OVER!";
        string congratsMessageOne = "CONGRATS YOU GOT THE HIGH SCORE!!!";
        string congratsMessageTwo = "YOU CAN QUIT NOW OR LATER TO ENTER INITIALS AND CEMENT YOUR LEGACY!!";
        string playAgainMessage = "PRESS SPACEBAR TO PLAY AGAIN";

        mvaddstr((getYMax() / 2), (getMiddleX()  + 1), (gameOverMessage).c_str());
        mvaddstr((getYMax() / 2 + 1), (getMiddleX() - 10), (congratsMessageOne).c_str());
        mvaddstr((getYMax() / 2 + 2), (getMiddleX() - 24), (congratsMessageTwo).c_str());
        mvaddstr(((getYMax() / 2) + 3), (getMiddleX() - 7), (playAgainMessage).c_str());
    }

    void drawBaseGameOver() {
        string gameOverMessage = "GAME OVER!!!";
        string playAgainMessage = "PRESS SPACEBAR TO PLAY AGAIN";
        mvaddstr((getYMax() / 2), getMiddleX(), (gameOverMessage).c_str());
        mvaddstr(((getYMax() / 2) + 1), (getMiddleX() - 7), (playAgainMessage).c_str());
    }

    int getAlienCount() {
        return this->alienCount;
    }
    void setAlienCount(int aCount) {
        this->alienCount = aCount;
    }
    void decrementAlienCount() {
        this->alienCount--;
    }

    bool getNewLevelStatus() {
        return this->newLevelStatus;
    }
    void setNewLevelStatus(bool status) {
        this->newLevelStatus = status;
    }

    int getLevelCount() {
        return this->levelCount;
    }
    void setLevelCount(int count) {
        this->levelCount = count;
    }
    void incrementLevelCount() {
        this->levelCount++;
    }

    void drawNewLevelScreen() {
        string congratsMessage = "CONGRATS!!!";
        string levelMessage = "YOU MADE IT TO LEVEL " + to_string(getLevelCount());
        string continuePlayingMessage = "PRESS SPACEBAR TO CONTINUE PLAYING";
        mvaddstr((getYMax() / 2), (getMiddleX() + 1), (congratsMessage).c_str());
        mvaddstr(((getYMax() / 2) + 1), (getMiddleX() - 4), (levelMessage).c_str());
        mvaddstr(((getYMax() / 2) + 2), (getMiddleX() - 10), (continuePlayingMessage).c_str()); 
    }

    void setUpSpecialUFO(AlienShip& ufo, int mainMenu) {
        if(mainMenu) {
            ufo.setAlienShip(3, 1, 3);
            this->setSpecialUFOActive(false);
        } else {
            srand(time(NULL));
            if(rand() % 2) {
                ufo.setAlienShip(3, 1, 3);
                this->setSpecialUFODirection(1);
            } else {
                ufo.setAlienShip(3, ( this->getXMax() - 10), 3);
                this->setSpecialUFODirection(-1);
            }
        }

    }

    void setSpecialUFODirection(int direction) {
        this->specialUFODirection = direction;
    }
    int getSpecialUFODirection() {
        return this->specialUFODirection;
    }

    void setSpecialUFOActive(bool status) {
        this->specialUFOActive = status;
    }
    bool getSpecialUFOActive() {
        return this->specialUFOActive;
    }

    void setSpecialUFOMovementTime(int t) {
        this->specialUFOMovementTime = t;
    }
    int getSpecialUFOMovementTime() {
        return this->specialUFOMovementTime;
    }
    void incrementSpecialUFOMovementTime() {
        this->specialUFOMovementTime++;
    }
};
