//
// Created by rafid on 15/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include <ncurses.h>
#include <iostream>
#include <stdlib.h>
#include <time.h>




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
    void movechoser(){
        int x= rand()%3;
        if
    }
    void FollowPlayer(){
        int x = abs(posX-0);
        int y = abs(posY - (getmaxy(win)-2));
        if (y>=x && posX-0>4){
            if (posX-abs(0)>=5){
                movePlayerLeft();
            }
            else{
                movePlayerRight();
            }
        }
        if (x>y && posY-(getmaxy(win)-2)>4){
            if (posY-abs((getmaxy(win)-2))>0){
                movePlayerUp();
            }
            else {
                movePlayerDown();
            }
        }
    }
    void EnemyMovement(){
        //int steps= (rand()%5)+1;
        int direction= rand()%4;
        switch (direction) {
            case 0:
                //for (int i=0; i<steps;i++){

                    movePlayerUp();
                //}
                break;
            case 1:
                // for (int i=0 ;i<steps;i++){

                    movePlayerDown();
                //}
                break;
            case 2:
                //for (int i=0; i<steps;i++){

                    movePlayerLeft();
                //}
                break;
            case 3:
                //for (int i=0; i<steps;i++){

                    movePlayerRight();
                //}
                break;
        }
    }

};



#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
