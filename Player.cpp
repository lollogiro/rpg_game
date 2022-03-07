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

    void displayPlayerMove(){
        int mv = wgetch(win);
        switch(mv){
            case KEY_UP:
                movePlayerUp();
                break;
            case KEY_DOWN:
                movePlayerDown();
                break;
            case KEY_LEFT:
                movePlayerLeft();
                break;
            case KEY_RIGHT:
                movePlayerRight();
                break;
            case ' ':
                //TODO implementare metodo per sparare
            default:
                break;
        }
    }

    //metodi get solo per test
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