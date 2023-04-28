/*
    Class for Alien Ship
*/
#pragma once
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
#include "Ship.h"
#include "Bullet.h"
using namespace std;

const int ALIEN_ROWS = 5;
const int ALIEN_COLUMNS = 11;

const string ALIEN_BUILDER[4][3] = {{" \\---/", "| @ @ |", " \\---/"}, 
                                    {" _____ ", "( o o )", " )~~~( "}, 
                                    {" /_ _\\ ", "[ . . ]", " \\___/"},
                                    {"", "{ _ _ }", " \\=^=/"}};

class AlienShip: public Ship {
private:
    bool alive;
    int type;

public:
    AlienShip(): Ship() {
        this->alive = true;
        this->type = 0;
    }

    AlienShip(string tBod, string mBod, string bBod,char pChar, int x, int y): Ship(tBod, mBod, bBod, pChar, x, y) {
        this->alive = true;
        this->type = 0;
    }

    void setAlienShip(int type, int x, int y) {
        if(type == 3) {
            this->setTopBody("BOOOB");
        }
        this->setTopBody(ALIEN_BUILDER[type][0]);
        this->setMiddleBody(ALIEN_BUILDER[type][1]);
        this->setBottomBody(ALIEN_BUILDER[type][2]);
        this->setX(x);
        this->setY(y);
        this->setType(type);
        this->setAliveStatus(true);
    }

    void printAlienShipMainMenuStats(int overrideY, int overrideX) {
        mvaddstr(overrideY-1, overrideX, (this->getTopBody()).c_str());
        mvaddstr(overrideY, overrideX, (this->getMiddleBody()).c_str());
        mvaddstr(overrideY+1, overrideX, (this->getBottomBody()).c_str());
    }

    bool checkCollision(PlayerShip& pOne, vector<Bullet>& bullets) {
        // First checking for collision with bullets        
        for(long unsigned int i = 0; i < bullets.size(); i++) {
            // Checking for the bottom layer and top layer with the OR
            if( ((bullets[i].getY() == (this->getY() + 1)) && 
                    (((bullets[i].getX() >= (this->getX() + 1)) && (bullets[i].getX() <= (this->getX() + 5))))) || 
                (((bullets[i].getY() == (this->getY())) && 
                    (((bullets[i].getX() >= (this->getX())) && (bullets[i].getX() <= (this->getX() + 6))))))) {
                    bullets.erase(bullets.begin() + i);
                    return true;
                }
        }

        // Now checking for the collision with the player ship
        if( (((this->getY() + 1) == (pOne.getY() - 1)) && 
                (((this->getX() + 5) == pOne.getX()) || (this->getX() == (pOne.getX() + 5)))) || 
            ((this->getY() > (pOne.getY() - 1)) && 
                (((this->getX() + 6) == pOne.getX()) || (this->getX() == (pOne.getX() + 5))))) {
            pOne.instantDeath();
            return true;
        } else {
            return false;
        }
    }

    void destroyAlien() {
        this->alive = false;
    }
    void setAliveStatus(bool status) {
        this->alive = status;
    }
    bool getAliveStatus() {
        return this->alive;
    }
    void setType(int type) {
        this->type = type;
    }
    int getType() {
        return this->type;
    }
 };