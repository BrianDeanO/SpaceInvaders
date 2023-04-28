/*
    Class for Player Bullet
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "Sprite.h"
using namespace std;


class Bullet: public Sprite {
private:
    char bulletChar = '^';

public:
    Bullet() {
        this->setX(0);
        this->setY(0);
    }

    Bullet(int x, int y): Sprite(x, y, this->getBulletChar()) {
        this->setX(x);
        this->setY(y); 
    }
    void moveUp() {
        this->setY(this->getY() - 1);
    }

    void drawBullet() {
        mvaddstr(this->getY(), this->getX(), &(this->bulletChar));
    }

    bool checkEndOfScreen() {
        if(this->getY() <= 2) {
            return true;
        } else {
            return false;
        }
    }
    char getBulletChar() {
        return this->bulletChar;
    }
};