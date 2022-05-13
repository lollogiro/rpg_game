//
// Created by rafid on 22/03/2022.
//

#ifndef PLAYER_H_BULLET_H
#define PLAYER_H_BULLET_H


#include <curses.h>

struct bulletAxisDirection{
    int offset_x;
    int offset_y;
};

class Bullet {
protected://maybe it can be public, so we may not use getter and setter
    char bulletChar;
    int posX;
    int posY;
    int damage;
    bulletAxisDirection axisDirection;
    char owner;//P(Player) o E(Enemy)
    WINDOW* win;
    Bullet* next;

public:
    Bullet(char bulletChar, int posX, int posY, int damage, int offset_x, int offset_y, char owner, WINDOW* win, Bullet* next){
        this->bulletChar = bulletChar;
        this->posX = posX;
        this->posY = posY;
        this->damage = damage;
        this->axisDirection.offset_x = offset_x;
        this->axisDirection.offset_y = offset_y;
        this->owner = owner;
        this->win = win;
        this->next = NULL;
    }

    void printBullet(){
        mvwaddch(win, posY, posX, bulletChar);
        wrefresh(win);
    }

    void setBulletChar(char bulletChar) {
        this->bulletChar = bulletChar;
    }

    void setPosX(int posX) {
        this->posX = posX;
    }

    void setPosY(int posY) {
        this->posY = posY;
    }

    void setDamage(int damage) {
        this->damage = damage;
    }

    void setAxisDirection(bulletAxisDirection axisDirection) {
        this->axisDirection.offset_x = axisDirection.offset_x;
        this->axisDirection.offset_y = axisDirection.offset_y;
    }

    void setOwner(char owner) {
        this->owner = owner;
    }

    void setWin(WINDOW *win) {
        this->win = win;
    }

    void setNext(Bullet *next) {
        this->next = next;
    }

    //get solo per test, tranne next
    char getBulletChar(){
        return bulletChar;
    }

    int getPosX(){
        return posX;
    }

    int getPosY(){
        return posY;
    }

    int getDamage(){
        return damage;
    }

    int getAxisDirectionX(){
        return axisDirection.offset_x;
    }

    int getAxisDirectionY(){
        return axisDirection.offset_y;
    }

    char getOwner(){
        return owner;
    }

    WINDOW *getWin(){
        return win;
    }

    Bullet *getNext(){
        return next;
    }
};




#endif //PLAYER_H_BULLET_H

