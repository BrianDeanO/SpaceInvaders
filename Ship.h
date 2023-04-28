/*
    Class for Parent Ship Class
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int UNAME_LENGTH = 3;

class Ship {
private:
    string topBody;
    string middleBody;
    string bottomBody;
    int x;
    int y;
    char projectileChar;

public:
    Ship() {
        this->topBody = "-------";
        this->middleBody = "-------";
        this->bottomBody = "-------";
        this->projectileChar = '*';
        this->x = 0;
        this->y = 0;
    }

    Ship(string tBod, string mBod, string bBod, char pChar, int x, int y) {
        this->topBody = tBod;
        this->middleBody = mBod;
        this->bottomBody = bBod;
        this->projectileChar = pChar;
        this->x = x;
        this->y = y;  
    }

    void draw() {
        mvaddstr(this->getY()-1, this->getX(), (this->topBody).c_str());
        mvaddstr(this->getY(), this->getX(), (this->middleBody).c_str());
        mvaddstr(this->getY()+1, this->getX(), (this->bottomBody).c_str());
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
    void moveHorizontally(int direction) {
        this->x += direction;
    }
    void moveDown() {
        this->y++;
    }
    void setTopBody(string tBody) {
        this->topBody = tBody; 
    }
    void setMiddleBody(string mBody) {
        this->middleBody = mBody;
    }
    void setBottomBody(string bBody) {
        this->bottomBody = bBody;
    }
    string getTopBody() {
        return this->topBody;
    }
    string getMiddleBody() {
        return this->middleBody;
    }
    string getBottomBody() {
        return this->bottomBody;
    }
};