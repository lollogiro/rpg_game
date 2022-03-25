//
// Created by rafid on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include <ncurses.h>
#include <stdlib.h>
#include <time.h>




using namespace std;

struct Player{
    char playersymbol;
    WINDOW* win;
    int posy;
    int posx;
};

class Enemy {
protected:
    char mapChar;
    int posX;
    int posY;
    int lifePoints;
    WINDOW *win;

public:
    Enemy(char mapChar, int posX, int posY, int lifePoints, WINDOW *win){
        this->mapChar = mapChar;
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
        this->win = win;
    }

    void printPlayer(){
        mvwaddch(win, posY, posX, mapChar);
        wrefresh(win);
    }

    void movePlayerUp(){
        mvwaddch(win, posY, posX, ' ');
        posY--;
        if(posY < 1) posY = 1;
        wrefresh(win);
    }

    void movePlayerDown(){
        mvwaddch(win, posY, posX, ' ');
        posY++;
        if(posY > (getmaxy(win) - 2)) posY = getmaxy(win) - 2;
        wrefresh(win);
    }

    void movePlayerLeft(){
        mvwaddch(win, posY, posX, ' ');
        posX--;
        if(posX < 1) posX = 1;
        wrefresh(win);
    }

    void movePlayerRight(){
        mvwaddch(win, posY, posX, ' ');
        posX++;
        if(posX > (getmaxx(win) - 2)) posX = getmaxx(win) - 2;
        wrefresh(win);
    }

    Enemy initializeEnemy(WINDOW* win){
        srand (time(NULL));
        int x=rand()%(getmaxx(win)-2)+1;
        int y=0;
        if (x<(getmaxx(win)-2)/3){
            y=rand()%((getmaxy(win)-2)/2)+1;
        }
        else {
            y=rand()%(getmaxy(win)-2)+1;
        }
        return Enemy('E', x, y, 20, win);
    }

};



#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
