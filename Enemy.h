//
// Created by lollo on 05/07/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_H
#define PROGETTO_PROGRAMMAZIONE_ENEMY_H

#include "Power.h"
#include "LivingEntity.h"

class Enemy : public LivingEntity{
public:
    Enemy* next;
public:
    Enemy(char mapSymbol, int posX, int posY, WINDOW *win, int lifePoints, Bullet *bullets, Enemy* next);
    bool checkEnemyPosition(int posXToCheck, int posYToCheck, Wall *interiorWalls, Enemy *enemies, Power *powers, Artifact *artifacts);
    void followPlayer(LivingEntity* Player, Wall* interiorWalls);
    void randomMovement(Wall* interiorWalls);
    void moveChooser(LivingEntity* player, Wall* interiorWalls);
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
