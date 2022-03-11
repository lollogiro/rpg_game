//
// Created by lollo on 09/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_BULLET_H
#define PROGETTO_PROGRAMMAZIONE_BULLET_H

#include <curses.h>

struct bulletAxisDirection{
    int offset_x;
    int offset_y;
};

class Bullet {
protected:
    char bulletChar;
    int posX;
    int posY;
    int damage;
    struct bulletAxisDirection axisDirection;
    char owner;//P(Player) o N(Nemico)
    WINDOW* win;
    Bullet* next;

public:
    Bullet(char bulletChar, int posX, int posY, int damage, bulletAxisDirection bulletAxisDirection, char owner, WINDOW* win, Bullet* next){
        this->bulletChar = bulletChar;
        this->posX = posX;
        this->posY = posY;
        this->damage = damage;
        this->axisDirection.offset_x = axisDirection.offset_x;
        this->axisDirection.offset_y = axisDirection.offset_y;
        this->owner = owner;
        this->win = win;
        this->next = NULL;
    }

    void printBullet(){
        if(posX >= 1 && posX <= getmaxx(win)-2 && posY >= 1 && posY <= getmaxx(win)-2){
            mvwaddch(win, posY, posX, bulletChar);
            wrefresh(win);
        }
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

    //set per next utilizzato per aggiungere un nuovo bullet alla lista attributo della classe player
    void setNext(Bullet *next) {
        this->next = next;
    }

    //get solo per test, tranne next
    char getBulletChar() const {
        return bulletChar;
    }

    int getPosX() const {
        return posX;
    }

    int getPosY() const {
        return posY;
    }

    int getDamage() const {
        return damage;
    }

    const bulletAxisDirection &getAxisDirection() const {
        return axisDirection;
    }

    char getOwner() const {
        return owner;
    }

    WINDOW *getWin() const {
        return win;
    }

    Bullet *getNext() const {
        return next;
    }
};


#endif //PROGETTO_PROGRAMMAZIONE_BULLET_H
