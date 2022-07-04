#ifndef PROGETTO_PROGRAMMAZIONE_BULLET_H
#define PROGETTO_PROGRAMMAZIONE_BULLET_H

#include "Entity.h"

struct bulletAxisDirection{
    int offset_x;
    int offset_y;
};

class Bullet : public Entity{
public:
    int damage;
    bulletAxisDirection axisDirection;
    Bullet* next;
public:
    Bullet(char charSymbol, int posX, int posY, WINDOW* win, int damage, int offset_x, int offset_y, Bullet* next);
    void printBullet();
};

#endif //PROGETTO_PROGRAMMAZIONE_BULLET_H
