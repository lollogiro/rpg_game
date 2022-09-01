#include "Player.hpp"
#include "constants.hpp"

Player::Player(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int lifePoints, Bullet *bullets)
        : LivingEntity(mapSymbol, posX, posY, secret, win, lifePoints, bullets) {}

void Player::displayMove(int userInput, bool openedDoor, bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls, int levelNumber){
    switch(userInput){
        case KEY_UP:
            moveUp(openedDoor, secretDoor, interiorWalls);
            break;
        case KEY_DOWN:
            moveDown(levelGreaterThanOne, secretDoor, interiorWalls);
            break;
        case KEY_LEFT:
            moveLeft(openedDoor, levelGreaterThanOne, interiorWalls);
            break;
        case KEY_RIGHT:
            moveRight(openedDoor, levelGreaterThanOne, secretDoor, interiorWalls);
            break;
        case ' ':
            shootBullet(interiorWalls, true, levelNumber);
        default:
            break;
    }
}

bool Player::moveToSecret(){
    return posX == getmaxx(win)-1;
}

bool Player::moveToMain(){
    return posY == getmaxy(win)-1;
}

void Player::applyRoomChange(){
    if(secret) secret = false;
    else secret = true;
}

bool Player::moveToNextLevel(){
    return posY == 0;
}

bool Player::moveToPrecLevel(){
    return posY == getmaxy(win)-1;
}

void Player::restartPlayer(){
    delete bullets;
    bullets = NULL;
    resetPosition(mainWinWidth/2-1, mainWinHeight-4);
    secret = false;
    lifePoints = 30;
}

void Player::resetPosition(int posX, int posY){
    this->posX = posX;
    this->posY = posY;
}
