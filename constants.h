//
// Created by lollo on 13/07/2022.
//

#ifndef TEMPLATE_MAPPE_CONSTANTS_H
#define TEMPLATE_MAPPE_CONSTANTS_H

#include <curses.h>
#include "Wall.h"

Wall* template1(WINDOW* win);

void printTemplate1(Wall* tmp1);

void printTemplate2(Wall* tmp2);

void printTemplate3(Wall* tmp3);

void printTemplate4(Wall* tmp4);



Wall* template2(WINDOW* win);

Wall* template3(WINDOW* win);

Wall* template4(WINDOW* win);

Wall* listInsert(Wall* walls, Wall* toIns);

void toString(Wall* walls);

#endif //TEMPLATE_MAPPE_CONSTANTS_H
