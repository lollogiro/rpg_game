//
// Created by lollo on 04/07/2022.
//

#include "Bullet.h"

Bullet::Bullet(char mapSymbol, int posX, int posY, WINDOW *win, int damage, int offset_x, int offset_y, Bullet *next)
        : Entity(mapSymbol, posX, posY, win) {
    this->damage = damage;
    this->axisDirection = {offset_x, offset_y};
    this->next = next;
}

void Bullet::printBullet(){
    Entity::printEntity();
}