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
    bool checkEnemyPosition(int posXEnemy, int posYEnemy, Enemy *enemies, Power *powers, Artifact *artifacts);
    void followPlayer(LivingEntity* Player);
    void randomMovement();
    void moveChooser(LivingEntity* player);
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_H
