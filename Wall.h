//
// Created by lollo on 13/07/2022.
//

#ifndef TEMPLATE_MAPPE_WALL_H
#define TEMPLATE_MAPPE_WALL_H

#include "Entity.h"

class Wall : public Entity{
public:
    Wall* next;

public:
    Wall(char mapSymbol, int posX, int posY, WINDOW* win);

    void printWall();
};


#endif //TEMPLATE_MAPPE_WALL_H
