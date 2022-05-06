//
// Created by rafid on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>
#include "bullet.h"



using namespace std;

struct Player{
    char playersymbol;
    WINDOW* win;
    int posy;
    int posx;
};

class Enemy {
protected:
    char mapChar;
    int posX;
    int posY;
    int lifePoints;
    WINDOW *win;

public:
    Enemy(char mapChar, int posX, int posY, int lifePoints, WINDOW *win){
        this->mapChar = mapChar;
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
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
        printPlayer();
        wrefresh(win);
    }

    void movePlayerDown(){
        mvwaddch(win, posY, posX, ' ');
        posY++;
        if(posY > (getmaxy(win) - 2)) posY = getmaxy(win) - 2;
        printPlayer();

    }

    void movePlayerLeft(){
        mvwaddch(win, posY, posX, ' ');
        posX--;
        if(posX < 1) posX = 1;
        printPlayer();

    }

    void movePlayerRight(){
        mvwaddch(win, posY, posX, ' ');
        posX++;
        if(posX > (getmaxx(win) - 2)) posX = getmaxx(win) - 2;
        printPlayer();
    }

    Enemy initializeEnemy(WINDOW* win){
        srand (time(NULL));
        int x=rand()%(getmaxx(win)-2)+1;
        int y=0;
        if (x<(getmaxx(win)-2)/3){
            y=rand()%((getmaxy(win)-2)/2)+1;
        }
        else {
            y=rand()%(getmaxy(win)-2)+1;
        }
        return Enemy('E', x, y, 20, win);
    }

    void MoveChoser(){ //decide randomicamente tra il movimento random e tra il movimento verso il player
        int x= rand()%3;
        if (x!=2){
            FollowPlayer();
        }
        else{
            EnemyRandomMovement();
        }
    }
    void FollowPlayer(){
        int xDiff = abs(posX-0);
        int yDiff = abs(posY - (getmaxy(win)-2));
        int xPlayer = 1;
        int yPlayer = getmaxy(win)-2;
        if (yDiff==0 && xDiff>0){
            if (xPlayer>posX){
                movePlayerRight();
            }
            else{
                movePlayerLeft();
            }

        }
        else if (xDiff==0 && yDiff>0){
            if(yPlayer>posY){
                movePlayerDown();
            }
            else{
                movePlayerUp();
            }
        }
        else {
            if (xDiff>yDiff){
                if(yPlayer>posY) movePlayerDown();
                else movePlayerUp();
            }
            else {
                if (xPlayer>posX) movePlayerRight();
                else movePlayerLeft();
            }
        }
    }

    void EnemyRandomMovement(){ //muove il nemico di 1 step in una direzione randomica
        //int steps= (rand()%5)+1;
        int direction= rand()%4;
        switch (direction) {
            case 0:

                    if (posY==1) movePlayerDown();
                    else movePlayerUp();

                break;
            case 1:
                    if (posY==getmaxy(win)-2) movePlayerUp();
                    else movePlayerDown();
                break;
            case 2:
                    if (posX==1) movePlayerRight();
                    else movePlayerLeft();
                break;
            case 3:
                    if (posX==getmaxx(win)-2) movePlayerLeft();
                    else movePlayerRight();
                break;
        }
    }

    /*void EnemyBullet{

    };*/

};



#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
