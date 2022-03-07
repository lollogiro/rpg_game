//
// Created by lollo on 07/03/2022.
//

#include <curses.h>

class Player {
protected:
    char mapSymbol;
    int posX;
    int posY;
    int lifePoints;
    WINDOW *win;

public:
    //da usare quando si transita tra livelli
    Player(char mapSymbol, int posX, int posY, int lifePoints, WINDOW *win) {
        this->mapSymbol = mapSymbol;
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
        this->win = win;
    }

    //utilizzato nell prima inizializzazione
    Player(char mapSymbol, WINDOW *win) {
        this->mapSymbol = mapSymbol;
        this->posX = 1;
        this->posY = getmaxy(win)-2;
        this->lifePoints = 20;
        this->win = win;
    }

    void printPlayer(){
        mvwaddch(win, posY, posX, mapSymbol);
        wrefresh(win);
    }

    char getMapSymbol() const {
        return mapSymbol;
    }

    int getPosX() const {
        return posX;
    }

    int getPosY() const {
        return posY;
    }

    int getLifePoints() const {
        return lifePoints;
    }
};