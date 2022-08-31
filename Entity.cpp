//
// Created by lollo on 04/07/2022.
//

#include "Entity.hpp"

Entity::Entity(char mapSymbol, int posX, int posY, bool secret, WINDOW *win) {
    this->mapSymbol = mapSymbol;
    this->posX = posX;
    this->posY = posY;
    this->secret = secret;
    this->win = win;
}

void Entity::print(){
    mvwaddch(win, posY, posX, mapSymbol);
    wrefresh(win);
}

void Entity::clear(){
    mvwaddch(win, posY, posX, ' ');
}

bool Entity::checkSecret(bool secret){
    return this->secret == secret;
}

int Entity::getPosX(){
    return posX;
}

int Entity::getPosY(){
    return posY;
}
