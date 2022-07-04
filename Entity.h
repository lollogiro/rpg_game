//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENTITY_H
#define PROGETTO_PROGRAMMAZIONE_ENTITY_H

#include <curses.h>

class Entity{
public:
    char mapSymbol;
    int posX;
    int posY;
    WINDOW* win;

public:
    Entity(char mapSymbol, int posX, int posY, WINDOW *win);
    void printEntity();

};

#endif //PROGETTO_PROGRAMMAZIONE_ENTITY_H
