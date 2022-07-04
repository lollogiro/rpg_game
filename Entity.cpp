//
// Created by lollo on 04/07/2022.
//

#include "Entity.h"

Entity::Entity(char mapSymbol, int posX, int posY, WINDOW *win) {
    this->mapSymbol = mapSymbol;
    this->posX = posX;
    this->posY = posY;
    this->win = win;
}

void Entity::printEntity(){
    mvwaddch(win, posY, posX, mapSymbol);
    wrefresh(win);
}