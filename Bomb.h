/*
    Class for Alien Bomb Class
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include "Sprite.h"
using namespace std;

class Bomb: public Sprite {
private:
    char bombChar = '*';

public:
    Bomb(): Sprite() {
        this->setX(0);
        this->setY(0);
    }

    Bomb(int x, int y): Sprite(x, y, this->getBombChar()) {
        this->setX(x);
        this->setY(y); 
    }

    char getBombChar() {
        return this->bombChar;
    }

    void moveDown() {
        this->setY(this->getY() + 1);
    }

    void drawBomb() {
        mvaddstr(this->getY(), this->getX(), &(this->bombChar));
    }

    bool checkEndOfScreen(int yPos) {
        if(this->getY() >= yPos) {
            return true;
        } else {
            return false;
        }
    }
};