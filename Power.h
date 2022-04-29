//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_POWER_H
#define PROGETTO_PROGRAMMAZIONE_POWER_H

#include <curses.h>

class Power {
protected:
    char symbol;
    int posX;
    int posY;
    WINDOW *win;
    Power* next;

public:
    Power(int posX, int posY, char symbol, WINDOW* win){
        this->posX = posX;
        this->posY = posY;
        this->symbol = symbol;
        this->win = win;
    }

    bool checkPowerPosition(int posXPower, int posYPower, Power* powers, Artifact* artifacts){
        bool check = true;
        while(check && artifacts != NULL){
            if(posXPower == artifacts->getPosX() && posYPower == artifacts->getPosY()){
                check=false;
            }
            artifacts = artifacts->getNext();
        }
        while (check && powers != NULL){
            if(posXPower == powers->posX && posYPower == powers->posY){
                check=false;
            }
            powers = powers->next;
        }
        return check;
    }

    void printPower(Power* powers){
        Power* tmp = powers;
        while(tmp != NULL){
            mvwaddch(tmp->win, tmp->posY, tmp->posX, tmp->symbol);
            wrefresh(win);
            tmp = tmp->next;
        }
    }

    char getSymbol() const {
        return symbol;
    }

    int getPosX() const {
        return posX;
    }

    int getPosY() const {
        return posY;
    }

    WINDOW *getWin() const {
        return win;
    }

    Power *getNext() const {
        return next;
    }

    void setSymbol(char symbol) {
        Power::symbol = symbol;
    }

    void setPosX(int posX) {
        Power::posX = posX;
    }

    void setPosY(int posY) {
        Power::posY = posY;
    }

    void setWin(WINDOW *win) {
        Power::win = win;
    }

    void setNext(Power *next) {
        Power::next = next;
    }

};

#endif //PROGETTO_PROGRAMMAZIONE_POWER_H
