//
// Created by lollo on 04/07/2022.
//

#include "LivingEntity.h"

LivingEntity::LivingEntity(char mapSymbol, int posX, int posY, WINDOW *win, int lifePoints, Bullet *bullets)
        : Entity(mapSymbol, posX, posY, win) {
    this->lifePoints = lifePoints;
    this->bullets = bullets;
}

//TODO: aggiungere inizializzazione di livello (pos=...)

void LivingEntity::moveUp(bool openedDoor, bool secretDoor){
    mvwaddch(win, posY, posX, ' ');
    posY--;
    if((posY < 1 && !openedDoor) || (posY < 1 && openedDoor && (posX < ((getmaxx(win)-2)/2)-2 || posX > ((getmaxx(win)-2)/2)+3))) posY = 1;
    else if(posY < 0 && openedDoor && posX >= ((getmaxx(win)-2)/2)-2 && posX <= ((getmaxx(win)-2)/2)+3) posY = 0;
    else if(posX == getmaxx(win)-1 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posY++;
    wrefresh(win);
}

void LivingEntity::moveDown(bool levelGreaterThanOne, bool secretDoor){
    mvwaddch(win, posY, posX, ' ');
    posY++;
    if((posY > getmaxy(win)-2 && !levelGreaterThanOne) || (posY > getmaxy(win)-2 && levelGreaterThanOne && (posX < ((getmaxx(win)-2)/2)-2 || posX > ((getmaxx(win)-2)/2)+3))) posY = getmaxy(win) - 2;
    else if(posY > getmaxy(win)-1 && levelGreaterThanOne && posX >= ((getmaxx(win)-2)/2)-2 && posX <= ((getmaxx(win)-2)/2)+3) posY = getmaxy(win)-1;
    else if(posX == getmaxx(win)-1 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posY--;
    wrefresh(win);
}

void LivingEntity::moveLeft(bool openedDoor, bool levelGreaterThanOne){
    mvwaddch(win, posY, posX, ' ');
    posX--;
    if(posX < 1) posX = 1;
    else if(posY == 0 && openedDoor && posX < ((getmaxx(win)-2)/2)-2) posX++;
    else if(posY == getmaxy(win)-1 && levelGreaterThanOne && posX < ((getmaxx(win)-2)/2)-2) posX++;
    wrefresh(win);
}

void LivingEntity::moveRight(bool openedDoor, bool levelGreaterThanOne, bool secretDoor){
    mvwaddch(win, posY, posX, ' ');
    posX++;
    if(posX > (getmaxx(win) - 2) && !secretDoor) posX = getmaxx(win) - 2;
    else if(posX > getmaxx(win)-2 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posX--;
    else if(posX > getmaxx(win)-1 && secretDoor && (posY >= ((getmaxy(win)-2)/2)-2 && posY <= ((getmaxy(win)-2)/2)+3)) posX--;
    else if(posY == 0 && openedDoor && posX > ((getmaxx(win)-2)/2)+3) posX--;
    else if(posY == getmaxy(win)-1 && levelGreaterThanOne && posX > ((getmaxx(win)-2)/2)+3) posX--;
    wrefresh(win);
}

void LivingEntity::createBullet(bulletAxisDirection axisDirection){
    if(bullets == NULL){
        bullets = new Bullet('.', posX+axisDirection.offset_x, posY+axisDirection.offset_y, win, 2, axisDirection.offset_x, axisDirection.offset_y, NULL);
    }else{
        Bullet* tmp = bullets;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        Bullet* tmpForSet = new Bullet('.', posX+axisDirection.offset_x, posY+axisDirection.offset_y, win, 2, axisDirection.offset_x, axisDirection.offset_y, NULL);
        tmp->next = tmpForSet;
    }
}

void LivingEntity::updateBulletPosition(){
    Bullet* tmp = bullets;
    while(tmp != NULL) {
        mvwaddch(win, tmp->posY, tmp->posX, ' ');
        tmp->posX = tmp->posX + tmp->axisDirection.offset_x;
        tmp->posY = tmp->posY + tmp->axisDirection.offset_y;
        tmp = tmp->next;
    }
    deleteNotValidBullet();
}

void LivingEntity::deleteNotValidBullet(){
    if(bullets != NULL){
        Bullet* tmp = bullets;
        Bullet* prec = NULL;
        while(tmp != NULL){
            if(tmp->posX < 1 || tmp->posX > (getmaxx(win) - 2) || tmp->posY < 1 || tmp->posY > (getmaxy(win) - 2)){
                mvwaddch(win, tmp->posY-tmp->axisDirection.offset_y, tmp->posX-tmp->axisDirection.offset_x, ' ');
                Bullet* old = tmp;
                if(prec == NULL) bullets = bullets->next;
                else prec->next = tmp->next;
                tmp = tmp->next;
                delete old;
            }
            else{
                prec = tmp;
                tmp = tmp->next;
            }
        }
    }
}

void LivingEntity::printEntityBullets(){
    Bullet* tmp = bullets;
    while(tmp != NULL){
        tmp->printBullet();
        tmp = tmp->next;
    }
}

void LivingEntity::shootBullet(){
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

void LivingEntity::displayMove(int userInput, bool openedDoor, bool levelGreaterThanOne, bool secretDoor){
    switch(userInput){
        case KEY_UP:
            moveUp(openedDoor, secretDoor);
            break;
        case KEY_DOWN:
            moveDown(levelGreaterThanOne, secretDoor);
            break;
        case KEY_LEFT:
            moveLeft(openedDoor, levelGreaterThanOne);
            break;
        case KEY_RIGHT:
            moveRight(openedDoor, levelGreaterThanOne, secretDoor);
            break;
        case ' ':
            shootBullet();
        default:
            break;
    }
}