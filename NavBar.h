/*
    Class for NavBar
*/
#include <ncurses.h>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int ROWS = 2;
const int COLUMNS = 10;

class NavBar {
private:
    int highScore;
    string userName;
    string lifeShip;
    int currentScore;
    
public:
    NavBar() {
        this->highScore = 5000;
        this->userName = "TRD";
        this->lifeShip = "_/^\\_";
        this->currentScore = 0;
    }

    void setNavHighScore(int score) {
        this->highScore = score;
    }
    void setUserName(string name) {
        this->userName = name;
    }
    string getLifeShip() {
        return this->lifeShip;
    }
    void setScore(int score) {
        this->currentScore = score;
    }
    int getScore() {
        return this->currentScore;
    }
    void incrementScore(int points) {
        this->currentScore += points;
    }
    int getNavHighSchore()

    void draw(int middleX) {
        mvaddstr(1, middleX, "High Score");
    }

};