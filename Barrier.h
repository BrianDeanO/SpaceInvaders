/*
    Class for Barrier
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
#include "Bomb.h"
using namespace std;

const int BARRIERS = 4;
const int B_ROWS = 2;
const int B_COLUMNS = 9;

class Barrier {
private:
    char pieces[B_ROWS][B_COLUMNS];
    char barrierChar;
    int leftX;
    int rightX;
    int topY;
    int bottomY;

public:
    Barrier() {
        this->setBarrierChar('#');
        for(int i = 0; i < B_ROWS; i++) {
            for(int j = 0; j < B_COLUMNS; j++) {
                this->pieces[i][j] = '#';
            }
        }
    }

    bool checkCollision(vector<Bomb>& bombs) {
        for(int i = 0; i < B_ROWS; i++) {
            for(int j = 0; j < B_COLUMNS; j++) {
                for(long unsigned int k = 0; k < bombs.size(); k++) {
                    if(i == 0) {
                        if((bombs[k].getY() == (this->getTopY())) && (bombs[k].getX() == (this->getLeftX() + j))) {
                            this->pieces[i][j] = '?';
                            bombs.erase(bombs.begin() + k);
                            return true;
                        }
                    } 
                    else {
                        if((bombs[k].getY() == (this->getBottomY())) && (bombs[k].getX() == (this->getLeftX() + j))) {
                            this->pieces[i][j] = '?';
                            bombs.erase(bombs.begin() + k);
                            return true;
                        }
                    }
                }
            }
        }

        return false;
    }

    void drawBarrier() {
        for(int i = 0; i < B_ROWS; i++) {
            for(int j = 0; j < B_COLUMNS; j++) {
                const char* bChar = "#";
                if(this->pieces[i][j] == '#') {
                    if(i == 0) {
                        mvaddstr(this->getTopY(), (this->getLeftX() + j), bChar);
                    } else {
                        mvaddstr(this->getBottomY(), (this->getLeftX() + j), bChar);
                    }
                }
            }
        }
    }

    void setBarrier(int x, int y) {
        this->leftX = (x-4);
        this->rightX = (x+4);
        this->topY = y;
        this->bottomY = y + 1;

        for(int i = 0; i < B_ROWS; i++) {
            for(int j = 0; j < B_COLUMNS; j++) {
                this->pieces[i][j] = '#';
            }
        }
    }

    char getBarrierChar() {
        return this->barrierChar;
    }
    void setBarrierChar(char c) {
        this->barrierChar = c;
    }

    int getLeftX() {
        return this->leftX;
    }
    int getRightX() {
        return this->rightX;
    }
    int getTopY() {
        return this->topY;
    }
    int getBottomY() {
        return this->bottomY;
    }
};