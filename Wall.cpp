//
// Created by lollo on 13/07/2022.
//

#include <iostream>
#include "Wall.h"

Wall::Wall(char mapSymbol, int posX, int posY, WINDOW* win): Entity(mapSymbol, posX, posY, win){
    this->next = NULL;
}

void Wall::printWall(){
    std::cout << posX << " " << posY << "\t";
}
