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

    void movePlayerUp(bool openedDoor, bool secretDoor){
        mvwaddch(win, posY, posX, ' ');
        posY--;
        if((posY < 1 && !openedDoor) || (posY < 1 && openedDoor && (posX < ((getmaxx(win)-2)/2)-2 || posX > ((getmaxx(win)-2)/2)+3))) posY = 1;
        else if(posY < 0 && openedDoor && posX >= ((getmaxx(win)-2)/2)-2 && posX <= ((getmaxx(win)-2)/2)+3) posY = 0;
        else if(posX == getmaxx(win)-1 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posY++;
        wrefresh(win);
    }

    void movePlayerDown(bool levelGreaterThanOne, bool secretDoor){
        mvwaddch(win, posY, posX, ' ');
        posY++;
        if((posY > getmaxy(win)-2 && !levelGreaterThanOne) || (posY > getmaxy(win)-2 && levelGreaterThanOne && (posX < ((getmaxx(win)-2)/2)-2 || posX > ((getmaxx(win)-2)/2)+3))) posY = getmaxy(win) - 2;
        else if(posY > getmaxy(win)-1 && levelGreaterThanOne && posX >= ((getmaxx(win)-2)/2)-2 && posX <= ((getmaxx(win)-2)/2)+3) posY = getmaxy(win)-1;
        else if(posX == getmaxx(win)-1 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posY--;
        wrefresh(win);
    }

    void movePlayerLeft(bool openedDoor, bool levelGreaterThanOne){
        mvwaddch(win, posY, posX, ' ');
        posX--;
        if(posX < 1) posX = 1;
        else if(posY == 0 && openedDoor && posX < ((getmaxx(win)-2)/2)-2) posX++;
        else if(posY == getmaxy(win)-1 && levelGreaterThanOne && posX < ((getmaxx(win)-2)/2)-2) posX++;
        wrefresh(win);
    }

    void movePlayerRight(bool openedDoor, bool levelGreaterThanOne, bool secretDoor){
        mvwaddch(win, posY, posX, ' ');
        posX++;
        if(posX > (getmaxx(win) - 2) && !secretDoor) posX = getmaxx(win) - 2;
        else if(posX > getmaxx(win)-2 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posX--;
        else if(posX > getmaxx(win)-1 && secretDoor && (posY >= ((getmaxy(win)-2)/2)-2 && posY <= ((getmaxy(win)-2)/2)+3)) posX--;
        else if(posY == 0 && openedDoor && posX > ((getmaxx(win)-2)/2)+3) posX--;
        else if(posY == getmaxy(win)-1 && levelGreaterThanOne && posX > ((getmaxx(win)-2)/2)+3) posX--;
        wrefresh(win);
    }

    void createBullet(bulletAxisDirection axisDirection){
        if(bullets == NULL){
            bullets = new Bullet('.', posX+axisDirection.offset_x, posY+axisDirection.offset_y, 2, axisDirection.offset_x, axisDirection.offset_y, 'P', win, NULL);
        }else{
            Bullet* tmp = bullets;
            while(tmp->getNext() != NULL){
                tmp = tmp->getNext();
            }
            Bullet* tmpForSet = new Bullet('.', posX+axisDirection.offset_x, posY+axisDirection.offset_y, 2, axisDirection.offset_x, axisDirection.offset_y, 'P', win, NULL);
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

    void shootABullet(){
        int bulletDirection = wgetch(win);
        bulletAxisDirection axisDirection;
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

    void displayPlayerMove(int userInput, bool openedDoor, bool levelGreaterThanOne, bool secretDoor){
        switch(userInput){
            case KEY_UP:
                movePlayerUp(openedDoor, secretDoor);
                break;
            case KEY_DOWN:
                movePlayerDown(levelGreaterThanOne, secretDoor);
                break;
            case KEY_LEFT:
                movePlayerLeft(openedDoor, levelGreaterThanOne);
                break;
            case KEY_RIGHT:
                movePlayerRight(openedDoor, levelGreaterThanOne, secretDoor);
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