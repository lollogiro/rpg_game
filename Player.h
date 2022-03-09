//
// Created by lollo on 07/03/2022.
//

#include <curses.h>
#include "Bullet.h"

using namespace std;

class Player {
protected:
    char mapChar;
    int posX;
    int posY;
    int lifePoints;
    WINDOW *win;

public:
    //da usare quando si transita tra livelli
    Player(char mapChar, int posX, int posY, int lifePoints, WINDOW *win) {
        this->mapChar = mapChar;
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
        this->win = win;
    }

    //utilizzato nella prima inizializzazione
    Player(char mapChar, WINDOW *win) {
        this->mapChar = mapChar;
        this->posX = 1;
        this->posY = getmaxy(win)-2;
        this->lifePoints = 20;
        this->win = win;
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

    void createBullet(int bulletDirection){
        switch (bulletDirection) {
            case KEY_UP:
                if(posY > 1){
                    Bullet* bullet = new Bullet('|', posX, posY-1, 2, 'P', win);
                    bullet->printBullet();
                    while(bullet->moveBulletUp()){
                        bullet->printBullet();
                        //TODO richiama funzione check collisione
                    }
                    delete bullet;
                }
                break;
            case KEY_DOWN:
                if(posY < getmaxy(win)-2){
                    Bullet* bullet = new Bullet('|', posX, posY+1, 2, 'P', win);
                    bullet->printBullet();
                    while(bullet->moveBulletDown()){
                        bullet->printBullet();
                        //TODO richiama funzione check collisione
                    }
                    delete bullet;
                }
                break;
            case KEY_LEFT:
                if(posX > 1){
                    Bullet* bullet = new Bullet('-', posX-1, posY, 2, 'P', win);
                    bullet->printBullet();
                    while(bullet->moveBulletLeft()){
                        bullet->printBullet();
                        //TODO richiama funzione check collisione
                    }
                    delete bullet;
                }
                break;
            case KEY_RIGHT:
                if(posX < getmaxx(win)-2){
                    Bullet* bullet = new Bullet('-', posX+1, posY, 2, 'P', win);
                    bullet->printBullet();
                    while(bullet->moveBulletRight()){
                        bullet->printBullet();
                        //TODO richiama funzione check collisione
                    }
                    delete bullet;
                }
                break;
        }
    }

    void shootABullet(){
        int bulletDirection = wgetch(win);
        switch (bulletDirection) {
            case KEY_UP:
                printf("Bullet ");
                createBullet(bulletDirection);
                break;
            case KEY_DOWN:
                printf("Bullet ");
                createBullet(bulletDirection);
                break;
            case KEY_LEFT:
                printf("Bullet ");
                createBullet(bulletDirection);
                break;
            case KEY_RIGHT:
                printf("Bullet ");
                createBullet(bulletDirection);
                break;
            default:
                //Tempo scaduto per dare una direzione e sparare il proiettile
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
    char getMapChar() const {
        return mapChar;
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