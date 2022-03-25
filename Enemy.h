//
// Created by rafid on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include <ncurses.h>

using namespace std;
class Enemy {
protected:
    char mapChar;
    int posX;
    int posY;
    int lifePoints;
    WINDOW *win;

public:
    Enemy(char mapChar, int EposX, int EposY, int ElifePoints, WINDOW *win){

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



};



#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
