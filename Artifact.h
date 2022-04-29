//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ARTIFACT_H
#define PROGETTO_PROGRAMMAZIONE_ARTIFACT_H

#include <curses.h>

class Artifact {
protected:
    char symbol;
    int lifePoints;
    int posX;
    int posY;
    WINDOW* win;
    Artifact* next;

public:
    Artifact(int posX, int posY, int lifePoints, char symbol, WINDOW* win){
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
        this->symbol = symbol;
        this->win = win;
    }

    bool checkArtifactPosition(int posXArtifact, int posYArtifact, Artifact* artifacts){
        bool check = true;
        while(check && artifacts != NULL){
            if(posXArtifact == artifacts->posX && posYArtifact == artifacts->posY){
                check = false;
            }
            artifacts = artifacts->next;
        }
        return check;
    }

    void printArtifact(Artifact* artifacts){
        Artifact* tmp = artifacts;
        while(tmp != NULL){
            mvwaddch(tmp->win, tmp->posY, tmp->posX, tmp->symbol);
            wrefresh(win);
            tmp = tmp->next;
        }
    }


    char getSymbol() const {
        return symbol;
    }

    int getLifePoints() const {
        return lifePoints;
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

    Artifact *getNext() const {
        return next;
    }

    void setSymbol(char symbol) {
        Artifact::symbol = symbol;
    }

    void setLifePoints(int lifePoints) {
        Artifact::lifePoints = lifePoints;
    }

    void setPosX(int posX) {
        Artifact::posX = posX;
    }

    void setPosY(int posY) {
        Artifact::posY = posY;
    }

    void setWin(WINDOW *win) {
        Artifact::win = win;
    }

    void setNext(Artifact *next) {
        Artifact::next = next;
    }

};


#endif //PROGETTO_PROGRAMMAZIONE_ARTIFACT_H
