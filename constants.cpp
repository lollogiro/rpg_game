//
// Created by lollo on 13/07/2022.
//

#include <iostream>
#include "constants.h"

Wall* template1(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, win);
    for (int i = 1; i <= 5; ++i) {
        tmp->posX = i;
        tmp->posY = 5;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = getmaxx(win)-1-i;
        tmp->posY = 25;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }
    for (int i = 1; i <= 3; ++i) {
        tmp->posX = i;
        tmp->posY = 20;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = getmaxx(win)-1-i;
        tmp->posY = 10;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }
    //MURI VERTICALI
    tmp->mapSymbol = 'x';
    for (int i = 1; i <= 10; ++i){
        tmp->posX = 26;
        tmp->posY = i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = 86;
        tmp->posY = getmaxy(win)-1-i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }
    for (int i = 1; i <= 6; ++i){
        tmp->posX = 94;
        tmp->posY = i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = 32;
        tmp->posY = getmaxy(win)-1-i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }
    return interiorWalls;
}

void printTemplate1(Wall* tmp){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(tmp->win, 5, 0, ACS_LTEE);
        mvwaddch(tmp->win, 25 , getmaxx(tmp->win)-1, ACS_RTEE);
        mvwaddch(tmp->win, 20, 0, ACS_LTEE);
        mvwaddch(tmp->win, 10 , getmaxx(tmp->win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(tmp->win, 0, 26, ACS_TTEE);
        mvwaddch(tmp->win, getmaxy(tmp->win)-1, 86, ACS_BTEE);
        mvwaddch(tmp->win, 0, 94, ACS_TTEE);
        mvwaddch(tmp->win, getmaxy(tmp->win)-1, 32, ACS_BTEE);

        while(tmp != NULL){
            mvwaddch(tmp->win, tmp->posY, tmp->posX, NCURSES_ACS(tmp->mapSymbol));
            tmp = tmp->next;
        }
    }
}

//TODO: fare template 2,3 e 4

Wall* listInsert(Wall* walls, Wall* toIns){
    if(walls == NULL){
        walls = new Wall(toIns->mapSymbol, toIns->posX, toIns->posY, toIns->win);
    }else{
        Wall* tmp = walls;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        Wall* tmpForSet = new Wall(toIns->mapSymbol, toIns->posX, toIns->posY, toIns->win);
        tmp->next = tmpForSet;
    }
    return walls;
}

void toString(Wall* walls){
    Wall* tmp = walls;
    while(tmp != NULL){
        tmp->printWall();
        tmp = tmp->next;
    }
}
