#include "Entity.h"
#include "Bullet.h"
#include "Wall.h"

#pragma once //altrimenti da redefinition error

class LivingEntity : public Entity{
public:
    int lifePoints;
    Bullet* bullets;

public:
    LivingEntity(char mapSymbol, int posX, int posY, WINDOW *win, int lifePoints, Bullet *bullets);
    void moveUp(bool openedDoor, bool secretDoor, Wall* interiorWalls);
    void moveDown(bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls);
    void moveLeft(bool openedDoor, bool levelGreaterThanOne, Wall* interiorWalls);
    void moveRight(bool openedDoor, bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls);
    void createBullet(bulletAxisDirection axisDirection, Wall* interiorWalls);
    void updateBulletPosition(Wall* interiorWalls);
    bool checkBulletOnInteriorWalls(int posXToCheck, int posYToCheck, Wall* interiorWalls);
    void deleteNotValidBullet(Wall* interiorWalls);
    void printEntityBullets();
    void shootBullet(Wall* interiorWalls);
    void displayMove(int userInput, bool openedDoor, bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls);
};