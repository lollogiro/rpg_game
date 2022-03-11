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
    Bullet* bullets;
    WINDOW *win;

public:
    //da usare quando si transita tra livelli
    Player(char mapChar, int posX, int posY, int lifePoints, Bullet* bullets, WINDOW *win) {
        this->mapChar = mapChar;
        this->posX = posX;
        this->posY = posY;
        this->lifePoints = lifePoints;
        this->bullets = NULL;
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

    void createBullet(struct bulletAxisDirection axisDirection){
        if(bullets == NULL){
            bullets = new Bullet('.', posX+axisDirection.offset_x, posY+axisDirection.offset_y, 2, axisDirection, 'P', win, NULL);
        }else{
            Bullet* tmp = bullets;
            while(tmp->getNext() != NULL){
                tmp = tmp->getNext();
            }
            Bullet* tmpForSet = new Bullet('.', posX+axisDirection.offset_x, posY+axisDirection.offset_y, 2, axisDirection, 'P', win, NULL);
            tmp->setNext(tmpForSet);
        }
    }

    //TODO: implementare il metodo update bullet che va a scorrere la lista dei bullets e applica il metodo moveBullet

    //TODO: implementarre metodo per eliminare i bullet non più validi dalla lista, dato che il print ad un certo punto non li printa più, modificare i moveBullet se non permettono la generazione di questo errore.

    void shootABullet(){
        int bulletDirection = wgetch(win);
        struct bulletAxisDirection axisDirection;
        switch (bulletDirection) {
            case KEY_UP:
                axisDirection.offset_x = 0;
                axisDirection.offset_y = -1;
                createBullet(axisDirection);
                break;
            case KEY_DOWN:
                axisDirection.offset_x = 0;
                axisDirection.offset_y = 1;
                createBullet(axisDirection);
                break;
            case KEY_LEFT:
                axisDirection.offset_x = -1;
                axisDirection.offset_y = 0;
                createBullet(axisDirection);
                break;
            case KEY_RIGHT:
                axisDirection.offset_x = 1;
                axisDirection.offset_y = 0;
                createBullet(axisDirection);
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