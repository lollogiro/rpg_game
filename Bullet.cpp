#include "Bullet.hpp"

Bullet::Bullet(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int damage, int offset_x, int offset_y, Bullet *next)
        : Entity(mapSymbol, posX, posY, secret, win) {
    this->damage = damage;
    this->axisDirection = {offset_x, offset_y};
    this->next = next;
}

void Bullet::printBullet(){
    mvwaddch(win, posY, posX, NCURSES_ACS(mapSymbol));
    wrefresh(win);
}

void Bullet::updateBulletPosition(){
    posX += axisDirection.offset_x;
    posY += axisDirection.offset_y;
}

void Bullet::invalidBullet(){
    posX = -1000;
}

int Bullet::getDamage(){
    return damage;
}

const bulletAxisDirection &Bullet::getAxisDirection(){
    return axisDirection;
}

