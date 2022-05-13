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
    Bullet* bullets;
    WINDOW *win;

public:
    Enemy(char mapChar, int posX, int posY, int lifePoints, WINDOW *win){
        this->mapChar = mapChar;
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
        this->bullets=NULL;
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
    void FollowPlayer(){ //segue il player
        int xDiff = abs(posX-0);
        int yDiff = abs(posY - (getmaxy(win)-2));
        int xPlayer = 1;
        int yPlayer = getmaxy(win)-2;
        bulletAxisDirection axisDirection;
        if (yDiff==0 && xDiff>0){
            if (xPlayer>posX){
                movePlayerRight(); //muove il giocatore a destra e spara
                axisDirection.offset_x = 1;
                axisDirection.offset_y = 0;
                createBullet(axisDirection);
            }
            else{
                movePlayerLeft(); //muove il giocatore a sinistra e spara
                axisDirection.offset_x = -1;
                axisDirection.offset_y = 0;
                createBullet(axisDirection);
            }
            deleteNotValidBullet();
        }
        else if (xDiff==0 && yDiff>0){
            if(yPlayer>posY){
                movePlayerDown(); //muove il giocatore sotto e spara
                axisDirection.offset_x = 0;
                axisDirection.offset_y = 1;
                createBullet(axisDirection);
            }
            else{
                movePlayerUp(); //muove il giocatore sopra e spara
                axisDirection.offset_x = 0;
                axisDirection.offset_y = -1;
                createBullet(axisDirection);
            }
            deleteNotValidBullet();
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


    void EnemyRandomMovement() { //muove di 1 step in una direzione randomica
        int direction = rand() % 6;
        bulletAxisDirection axisDirection;
        int RandomBullet = rand() % 4;
        switch (direction) {
            case 0:
                if (posY == 1) movePlayerDown();
                else movePlayerUp();
                break;
            case 1:
                if (posY == getmaxy(win) - 2) movePlayerUp();
                else movePlayerDown();
                break;
            case 2:
                if (posX == 1) movePlayerRight();
                else movePlayerLeft();
                break;
            case 3:
                if (posX == getmaxx(win) - 2) movePlayerLeft();
                else movePlayerRight();
                break;
            case 4:

                if (RandomBullet == 0) { //shoots up
                    axisDirection.offset_x = 0;
                    axisDirection.offset_y = -1;
                    createBullet(axisDirection);
                }
                if (RandomBullet == 1){ //shoots down
                    axisDirection.offset_x = 0;
                    axisDirection.offset_y = 1;
                    createBullet(axisDirection);
                }
                deleteNotValidBullet();
                break;
            case 5:

                if (RandomBullet == 0) { //shoots right
                    axisDirection.offset_x = 1;
                    axisDirection.offset_y = 0;
                    createBullet(axisDirection);

                }
                if (RandomBullet == 1){ //shoots left
                    axisDirection.offset_x = -1;
                    axisDirection.offset_y = 0;
                    createBullet(axisDirection);
                }
                deleteNotValidBullet();
                break;

        }
    }

    void createBullet(bulletAxisDirection axisDirection){
        if(bullets == NULL){
            bullets = new Bullet('*', posX+axisDirection.offset_x, posY+axisDirection.offset_y, 2, axisDirection.offset_x, axisDirection.offset_y, 'E', win, NULL);
        }else{
            Bullet* tmp = bullets;
            while(tmp->getNext() != NULL){
                tmp = tmp->getNext();
            }
            Bullet* tmpForSet = new Bullet('*', posX+axisDirection.offset_x, posY+axisDirection.offset_y, 2, axisDirection.offset_x, axisDirection.offset_y, 'E', win, NULL);
            tmp->setNext(tmpForSet);
        }
    }

    void updateBulletPosition(){
        Bullet* tmp = bullets;
        while(tmp != NULL) {
            mvwaddch(win, tmp->getPosY(), tmp->getPosX(), ' ');
            tmp->setPosX(tmp->getPosX() + tmp->getAxisDirectionX());
            tmp->setPosY(tmp->getPosY() + tmp->getAxisDirectionY());
            tmp = tmp->getNext();
        }
        deleteNotValidBullet();
    }

    void deleteNotValidBullet(){
        if(bullets != NULL){
            Bullet* tmp = bullets;
            Bullet* prec = NULL;
            while(tmp != NULL){
                if(tmp->getPosX() < 1 || tmp->getPosX() > (getmaxx(win) - 2) || tmp->getPosY() < 1 || tmp->getPosY() > (getmaxy(win) - 2)){
                    mvwaddch(win, tmp->getPosY()-tmp->getAxisDirectionY(), tmp->getPosX()-tmp->getAxisDirectionX(), ' ');
                    Bullet* old = tmp;
                    if(prec == NULL) bullets = bullets->getNext();
                    else prec->setNext(tmp->getNext());
                    tmp = tmp->getNext();
                    delete old;
                }
                else{
                    prec = tmp;
                    tmp = tmp->getNext();
                }
            }
        }
    }

    void printPlayerBullet(){
        Bullet* tmp = bullets;
        while(tmp != NULL){
            tmp->printBullet();
            tmp = tmp->getNext();
        }
    }



};




#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
