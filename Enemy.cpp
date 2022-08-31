//
// Created by lollo on 05/07/2022.
//

#include "Enemy.hpp"
#include <cstdlib>

Enemy::Enemy(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int lifePoints, Bullet *bullets, Enemy* next)
        : LivingEntity(mapSymbol, posX, posY, secret, win, lifePoints, bullets) {
    this->next = NULL;
}

bool Enemy::checkEnemyPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Enemy *enemies, StaticEntity* powers, StaticEntity* artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXToCheck == artifacts->getPosX() && posYToCheck == artifacts->getPosY()){
            check=false;
        }
        artifacts = artifacts->next;
    }
    while (check && powers != NULL){
        if(posXToCheck == powers->getPosX() && posYToCheck == powers->getPosY()){
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
        if(posXToCheck == interiorWalls->getPosX() && posYToCheck == interiorWalls->getPosY()){
            check=false;
        }
        interiorWalls = interiorWalls->next;
    }

    //TODO: check per non far spawnare entità nello stanzino

    return check;
}

void Enemy::followPlayer(LivingEntity* player, Wall* interiorWalls, int levelNumber){ //segue il player
    int xPlayer = player->getPosX();
    int yPlayer = player->getPosY();
    int xDiff = posX-xPlayer;
    int yDiff = posY - yPlayer;
    bulletAxisDirection axisDirection;
    int shoot = rand()%2;
    if(yDiff==0){
        if (xDiff<=0){
            moveRight(false, false, false, interiorWalls); //muove il giocatore a destra e spara
            axisDirection.offset_x = 1;
            axisDirection.offset_y = 0;
            if(shoot == 1 && !secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
        }
        else{
            moveLeft(false, false, interiorWalls); //muove il giocatore a sinistra e spara
            axisDirection.offset_x = -1;
            axisDirection.offset_y = 0;
            if(shoot == 1 && !secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
        }
        //deleteNotValidBullet(interiorWalls);
    }
    else if(xDiff==0){
        if(yDiff<=0){
            moveDown(false, false, interiorWalls); //muove il giocatore sotto e spara
            axisDirection.offset_x = 0;
            axisDirection.offset_y = 1;
            if(shoot == 1 && !secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
        }
        else{
            moveUp(false, false, interiorWalls); //muove il giocatore sopra e spara
            axisDirection.offset_x = 0;
            axisDirection.offset_y = -1;
            if(shoot == 1 && !secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
        }
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

void Enemy::randomMovement(Wall* interiorWalls, int levelNumber) { //muove di 1 step in una direzione randomica
    int direction = rand() % 8;
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
                if(!secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
            }
            if (RandomBullet == 1){ //shoots down
                axisDirection.offset_x = 0;
                axisDirection.offset_y = 1;
                if(!secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
            }
            deleteNotValidBullet(interiorWalls);
            break;
        case 5:
            if (RandomBullet == 0) { //shoots right
                axisDirection.offset_x = 1;
                axisDirection.offset_y = 0;
                if(!secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
            }
            if (RandomBullet == 1){ //shoots left
                axisDirection.offset_x = -1;
                axisDirection.offset_y = 0;
                if(!secret) createBullet(axisDirection, interiorWalls, false, levelNumber);
            }
            deleteNotValidBullet(interiorWalls);
            break;
        default:
            //no movement
            break;
    }
}

void Enemy::moveChooser(LivingEntity* player, Wall* interiorWalls, int levelNumber){ //decide randomicamente tra il movimento random e tra il movimento verso il player
    //inizialmente 1/4 cosi cosi, 3/16 buono, 6/16 molto buono
    int x=rand()%16;
    if (x<6){
        followPlayer(player, interiorWalls, levelNumber);
    }
    else{
        randomMovement(interiorWalls, levelNumber);
    }
}

bool Enemy::getSecret(){
    return secret;
}