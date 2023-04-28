/*
    Class for Parent Sprite Class
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

class Sprite {
private:
    int x;
    int y;
    char character;

public:
    Sprite() {
        this->x = 0;
        this->y = 0;
        character = '?';
    }
    Sprite(int x, int y, char c) {
        setX(x);
        setY(y);
        setCharacter(c);
    }
    void setCharacter(char c) {
        this->character = c;
    }
    char getCharacter() {
        return this->character;
    }
    void setX(int x) {
        this->x = x;
    }
    void setY(int y) {
        this->y = y;
    }
    int getX() {
        return this->x;
    }
    int getY() {
        return this->y;
    }
};