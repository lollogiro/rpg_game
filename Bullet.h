//
// Created by lollo on 09/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_BULLET_H
#define PROGETTO_PROGRAMMAZIONE_BULLET_H

#include <curses.h>

class Bullet {
protected:
    int posX;
    int posY;
    int damage;
    char owner;//P(Player) o N(Nemico)
    WINDOW* win;

public:
    Bullet(int posX, int posY, int damage, char owner, WINDOW* win){
        this.posX = posX;
        this.posY = posY;
        this.damage = damage;
        this.owner = owner;
        this.win = win;
    }

    void printBullet(){
        mvwaddch(win, posY, posX, mapSymbol);
        wrefresh(win);
    }

    void moveBulletUp(){
        mvwaddch(win, posY, posX, ' ');
        posY--;
        if(posY < 1) posY = 1;
        wrefresh(win);
    }

    void moveBulletDown(){
        mvwaddch(win, posY, posX, ' ');
        posY++;
        if(posY > (getmaxy(win) - 2)) posY = getmaxy(win) - 2;
        wrefresh(win);
    }

    void moveBulletLeft(){
        mvwaddch(win, posY, posX, ' ');
        posX--;
        if(posX < 1) posX = 1;
        wrefresh(win);
    }

    void moveBulletRight(){
        mvwaddch(win, posY, posX, ' ');
        posX++;
        if(posX > (getmaxx(win) - 2)) posX = getmaxx(win) - 2;
        wrefresh(win);
    }

    //TODO funzione che faccia il check nel caso in cui un nemico colpisca il player e il contrario, in base al char owner, controllare la lista dell'entità opposta
};


#endif //PROGETTO_PROGRAMMAZIONE_BULLET_H
