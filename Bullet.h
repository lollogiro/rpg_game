//
// Created by lollo on 09/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_BULLET_H
#define PROGETTO_PROGRAMMAZIONE_BULLET_H

#include <curses.h>

class Bullet {
protected:
    char bulletChar;
    int posX;
    int posY;
    int damage;
    char owner;//P(Player) o N(Nemico)
    WINDOW* win;

public:
    Bullet(char bulletChar, int posX, int posY, int damage, char owner, WINDOW* win){
        this->bulletChar = bulletChar;
        this->posX = posX;
        this->posY = posY;
        this->damage = damage;
        this->owner = owner;
        this->win = win;
    }

    void printBullet(){
        mvwaddch(win, posY, posX, bulletChar);
        wrefresh(win);
    }

    bool moveBulletUp(){
        mvwaddch(win, posY, posX, ' ');
        posY--;
        if(posY < 1) return false;
        else return true;
        wrefresh(win);
    }

    bool moveBulletDown(){
        mvwaddch(win, posY, posX, ' ');
        posY++;
        if(posY > (getmaxy(win) - 2)) return false;
        else return true;
        wrefresh(win);
    }

    bool moveBulletLeft(){
        mvwaddch(win, posY, posX, ' ');
        posX--;
        if(posX < 1) return false;
        else return true;
        wrefresh(win);
    }

    bool moveBulletRight(){
        mvwaddch(win, posY, posX, ' ');
        posX++;
        if(posX > (getmaxx(win) - 2)) return false;
        else return true;
        wrefresh(win);
    }

    //TODO funzione che faccia il check nel caso in cui un nemico colpisca il player e il contrario, in base al char owner, controllare la lista dell'entità opposta
};


#endif //PROGETTO_PROGRAMMAZIONE_BULLET_H
