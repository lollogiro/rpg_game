//
// Created by lollo on 07/03/2022.
//

#include <curses.h>
#include "Bullet.h"

using namespace std;

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

    //utilizzato nella prima inizializzazione
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

    void createBullet(int bulletDirection){
        //TODO switch che generi un proiettile in base alla direzione
        //TODO in ogni switch richiamare moveBullet(Bullet* bullet), il quale si occupa di muovere il Bullet e di richiamare funzione check collisione
    }

    void shootABullet(){
        int bulletDirection = wgetch(win);
        switch (bulletDirection) {
            case KEY_UP | KEY_DOWN | KEY_LEFT | KEY_RIGHT:
            default:
                printf("Bullet Time Expired ");
                break;
        }
    }

    void displayPlayerMove(int userInput){
        switch(userInput){
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
                shootABullet();
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