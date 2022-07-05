//
// Created by lollo on 05/07/2022.
//

#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(char mapSymbol, int posX, int posY, WINDOW *win, int lifePoints, Bullet *bullets, Enemy* next)
        : LivingEntity(mapSymbol, posX, posY, win, lifePoints, bullets) {
    this->next = NULL;
}

bool Enemy::checkEnemyPosition(int posXEnemy, int posYEnemy, Enemy *enemies, Power *powers, Artifact *artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXEnemy == artifacts->posX && posYEnemy == artifacts->posY){
            check=false;
        }
        artifacts = artifacts->next;
    }
    while (check && powers != NULL){
        if(posXEnemy == powers->posX && posYEnemy == powers->posY){
            check=false;
        }
        powers = powers->next;
    }
    while (check && enemies != NULL){
        if(posXEnemy == enemies->posX && posYEnemy == enemies->posY){
            check=false;
        }
        enemies = enemies->next;
    }
    return check;
}

void Enemy::followPlayer(LivingEntity* player){ //segue il player
    int xDiff = abs(posX-0);
    int yDiff = abs(posY - (getmaxy(win)-2));
    int xPlayer = player->posX;
    int yPlayer = player->posY;
    bulletAxisDirection axisDirection;
    if (yDiff==0 && xDiff>0){
        if (xPlayer>posX){
            moveRight(false, false, false); //muove il giocatore a destra e spara
            axisDirection.offset_x = 1;
            axisDirection.offset_y = 0;
            createBullet(axisDirection);
        }
        else{
            moveLeft(false, false); //muove il giocatore a sinistra e spara
            axisDirection.offset_x = -1;
            axisDirection.offset_y = 0;
            createBullet(axisDirection);
        }
        deleteNotValidBullet();
    }
    else if (xDiff==0 && yDiff>0){
        if(yPlayer>posY){
            moveDown(false, false); //muove il giocatore sotto e spara
            axisDirection.offset_x = 0;
            axisDirection.offset_y = 1;
            createBullet(axisDirection);
        }
        else{
            moveUp(false, false); //muove il giocatore sopra e spara
            axisDirection.offset_x = 0;
            axisDirection.offset_y = -1;
            createBullet(axisDirection);
        }
        deleteNotValidBullet();
    }
    else {
        if (xDiff>yDiff){
            if(yPlayer>posY) moveDown(false, false);
            else moveUp(false, false);
        }
        else {
            if (xPlayer>posX) moveRight(false, false, false);
            else moveLeft(false, false);
        }
    }
}

void Enemy::randomMovement() { //muove di 1 step in una direzione randomica
    int direction = rand() % 6;
    bulletAxisDirection axisDirection;
    int RandomBullet = rand() % 4;
    switch (direction) {
        case 0:
            if (posY == 1) moveDown(false, false);
            else moveUp(false, false);
            break;
        case 1:
            if (posY == getmaxy(win) - 2) moveUp(false, false);
            else moveDown(false, false);
            break;
        case 2:
            if (posX == 1) moveRight(false, false, false);
            else moveLeft(false, false);
            break;
        case 3:
            if (posX == getmaxx(win) - 2) moveLeft(false, false);
            else moveRight(false, false, false);
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

void Enemy::moveChooser(LivingEntity* player){ //decide randomicamente tra il movimento random e tra il movimento verso il player
    int x= rand()%3;
    if (x!=2){
        followPlayer(player);
    }
    else{
        randomMovement();
    }
}