//
// Created by lollo on 13/07/2022.
//

#include <iostream>
#include "Wall.hpp"

Wall::Wall(char mapSymbol, int posX, int posY, bool secret, WINDOW* win): Entity(mapSymbol, posX, posY, secret, win){
    this->next = NULL;
}

void Wall::print(){
    mvwaddch(win, posY, posX, NCURSES_ACS(mapSymbol));
}

void Wall::printDoor(){
    mvwaddch(win, posY, posX, mapSymbol);

}

void Wall::printOpenDoor(){
    mvwaddch(win, posY, posX, ' ');
}

Wall* Wall::listInsert(Wall* walls, Wall* toIns){
    if(walls == NULL){
        walls = new Wall(toIns->mapSymbol, toIns->posX, toIns->posY, false, toIns->win);
    }else{
        Wall* tmp = walls;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        Wall* tmpForSet = new Wall(toIns->mapSymbol, toIns->posX, toIns->posY, false, toIns->win);
        tmp->next = tmpForSet;
    }
    return walls;
}

char Wall::getMapSymbol(){
    return mapSymbol;
}
