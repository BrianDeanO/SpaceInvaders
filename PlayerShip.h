/*
    Class for Player Ship
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include "Ship.h"
#include "Bomb.h"
using namespace std;

class PlayerShip: public Ship {
private:
    int numberOfLives;
    int score;
    int bulletTime;

public:
    PlayerShip(): Ship() {
        this->numberOfLives = 3;
        this->score = 0;
    }

    PlayerShip(string tBod, string mBod, string bBod,char pChar, int x, int y): Ship(tBod, mBod, bBod, pChar, x, y) {
        this->numberOfLives = 3;
        this->score = 0;
    }

    bool checkCollision(vector<Bomb>& bombs) {
        for(long unsigned int i = 0; i < bombs.size(); i++) {
            // Checking for the top layer
            if( ((bombs[i].getY() == (this->getY() - 1)) && 
                    (((bombs[i].getX() >= (this->getX() + 2)) && (bombs[i].getX() <= (this->getX() + 4))))) || 
                ((((bombs[i].getY() == this->getY()) || (bombs[i].getY() == (this->getY() + 1)))) && 
                    (((bombs[i].getX() >= (this->getX())) && (bombs[i].getX() <= (this->getX() + 6)))))) {
                    bombs.erase(bombs.begin() + i);
                    return true;
                }
        }
        return false;
    }
    void setShip(int x, int y, int bTime) {
        this->setTopBody("  /^\\  ");
        this->setMiddleBody("$[---]$");
        this->setBottomBody("/_____\\");
        this->setX(x);
        this->setY(y);
        this->setBulletTime(bTime);
    }
    void resetShip(int x) {
        this->decrementLives();
        this->setX(x);
    }

    void setScore(int score) {
        this->score = score;
    }
    int getScore() {
        return this->score;
    }
    void incrementScore(int points) {
        this->score += points;
    }
    int getLives() {
        return this->numberOfLives;
    }
    void resetLives() {
        this->numberOfLives = 3;
    }
    void setLives(int l) {
        this->numberOfLives = l;
    }
    void decrementLives() {
        this->numberOfLives--;
    }
    void instantDeath() {
        this->numberOfLives = 0;
    }
    bool isAlive() {
        if(this->numberOfLives > 0) {
            return true;
        } else {
            return false;
        }
    }
    void setBulletTime(int t) {
        this->bulletTime = t;
    }
    int getBulletTime() {
        return this->bulletTime;
    }
    void incrementBulletTime() {
        this->bulletTime++;
    }
};