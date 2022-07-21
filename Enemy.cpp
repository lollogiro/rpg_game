//
// Created by lollo on 05/07/2022.
//

#include "Enemy.h"
#include <cstdlib>

Enemy::Enemy(char mapSymbol, int posX, int posY, WINDOW *win, int lifePoints, Bullet *bullets, Enemy* next)
        : LivingEntity(mapSymbol, posX, posY, win, lifePoints, bullets) {
    this->next = NULL;
}

bool Enemy::checkEnemyPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Enemy *enemies, Power *powers, Artifact *artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXToCheck == artifacts->posX && posYToCheck == artifacts->posY){
            check=false;
        }
        artifacts = artifacts->next;
    }
    while (check && powers != NULL){
        if(posXToCheck == powers->posX && posYToCheck == powers->posY){
            check=false;
        }
        powers = powers->next;
    }
    while (check && enemies != NULL){
        if(posXToCheck == enemies->posX && posYToCheck == enemies->posY){
            check=false;
        }
        enemies = enemies->next;
    }
    while (check && interiorWalls != NULL){
        if(posXToCheck == interiorWalls->posX && posYToCheck == interiorWalls->posY){
            check=false;
        }
        interiorWalls = interiorWalls->next;
    }
    return check;
}

void Enemy::followPlayer(LivingEntity* player, Wall* interiorWalls){ //segue il player
    int xDiff = abs(posX-0);
    int yDiff = abs(posY - (getmaxy(win)-2));
    int xPlayer = player->posX;
    int yPlayer = player->posY;
    bulletAxisDirection axisDirection;
    if (yDiff==0 && xDiff>0){
        if (xPlayer>posX){
            moveRight(false, false, false, interiorWalls); //muove il giocatore a destra e spara
            axisDirection.offset_x = 1;
            axisDirection.offset_y = 0;
            createBullet(axisDirection, interiorWalls);
        }
        else{
            moveLeft(false, false, interiorWalls); //muove il giocatore a sinistra e spara
            axisDirection.offset_x = -1;
            axisDirection.offset_y = 0;
            createBullet(axisDirection, interiorWalls);
        }
        deleteNotValidBullet(interiorWalls);
    }
    else if (xDiff==0 && yDiff>0){
        if(yPlayer>posY){
            moveDown(false, false, interiorWalls); //muove il giocatore sotto e spara
            axisDirection.offset_x = 0;
            axisDirection.offset_y = 1;
            createBullet(axisDirection, interiorWalls);
        }
        else{
            moveUp(false, false, interiorWalls); //muove il giocatore sopra e spara
            axisDirection.offset_x = 0;
            axisDirection.offset_y = -1;
            createBullet(axisDirection, interiorWalls);
        }
        deleteNotValidBullet(interiorWalls);
    }
    else {
        if (xDiff>yDiff){
            if(yPlayer>posY) moveDown(false, false, interiorWalls);
            else moveUp(false, false, interiorWalls);
        }
        else {
            if (xPlayer>posX) moveRight(false, false, false, interiorWalls);
            else moveLeft(false, false, interiorWalls);
        }
    }
}

void Enemy::randomMovement(Wall* interiorWalls) { //muove di 1 step in una direzione randomica
    int direction = rand() % 6;
    bulletAxisDirection axisDirection;
    int RandomBullet = rand() % 4;
    switch (direction) {
        case 0:
            if (posY == 1) moveDown(false, false, interiorWalls);
            else moveUp(false, false, interiorWalls);
            break;
        case 1:
            if (posY == getmaxy(win) - 2) moveUp(false, false, interiorWalls);
            else moveDown(false, false, interiorWalls);
            break;
        case 2:
            if (posX == 1) moveRight(false, false, false, interiorWalls);
            else moveLeft(false, false, interiorWalls);
            break;
        case 3:
            if (posX == getmaxx(win) - 2) moveLeft(false, false, interiorWalls);
            else moveRight(false, false, false, interiorWalls);
            break;
        case 4:
            if (RandomBullet == 0) { //shoots up
                axisDirection.offset_x = 0;
                axisDirection.offset_y = -1;
                createBullet(axisDirection, interiorWalls);
            }
            if (RandomBullet == 1){ //shoots down
                axisDirection.offset_x = 0;
                axisDirection.offset_y = 1;
                createBullet(axisDirection, interiorWalls);
            }
            deleteNotValidBullet(interiorWalls);
            break;
        case 5:
            if (RandomBullet == 0) { //shoots right
                axisDirection.offset_x = 1;
                axisDirection.offset_y = 0;
                createBullet(axisDirection, interiorWalls);
            }
            if (RandomBullet == 1){ //shoots left
                axisDirection.offset_x = -1;
                axisDirection.offset_y = 0;
                createBullet(axisDirection, interiorWalls);
            }
            deleteNotValidBullet(interiorWalls);
            break;
    }
}

void Enemy::moveChooser(LivingEntity* player, Wall* interiorWalls){ //decide randomicamente tra il movimento random e tra il movimento verso il player
    int x= rand()%5;
    if (x!=2){
        followPlayer(player, interiorWalls);
    }
    else{
        randomMovement(interiorWalls);
    }
}