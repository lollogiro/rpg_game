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
        tmp->posX = getmaxx(win) - 1 - i;
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


Wall* template2(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, win);
        for (int i = 1; i <= 6; ++i) {
            tmp->posX = i;
            tmp->posY = 7;
            tmp->next = NULL;
            interiorWalls = listInsert(interiorWalls, tmp);
            tmp->posX = getmaxx(win)-1-i;
            tmp->posY = 19;
            tmp->next = NULL;
            interiorWalls = listInsert(interiorWalls, tmp);
    }
    //MURI VERTICALI
    tmp->mapSymbol = 'x';
    for (int i = 1; i <= 8; ++i){
        tmp->posX = 28;
        tmp->posY = i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = 71;
        tmp->posY = getmaxy(win)-1-i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }

tmp->posX=23;
tmp->posY=9;
tmp->next= NULL;
interiorWalls = listInsert(interiorWalls, tmp);
tmp->posX=71;
tmp->posY=4;
tmp->next=NULL;
interiorWalls = listInsert(interiorWalls, tmp);

return interiorWalls;


}



void printTemplate2(Wall* tmp){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(tmp->win, 7, 0, ACS_LTEE);
        mvwaddch(tmp->win, 19 , getmaxx(tmp->win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(tmp->win, 0, 28, ACS_TTEE);
        mvwaddch(tmp->win, getmaxy(tmp->win)-1, 71, ACS_BTEE);

        mvwaddch(tmp->win, 23, 9, ACS_TTEE);
        mvwaddch(tmp->win, 71, 4, ACS_TTEE);
        while(tmp != NULL){
            mvwaddch(tmp->win, tmp->posY, tmp->posX, NCURSES_ACS(tmp->mapSymbol));
            tmp = tmp->next;
        }
    }
}
Wall* template3(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, win);
    for (int i = 1; i <= 6; ++i) {
        tmp->posX = i;
        tmp->posY = 7;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = getmaxx(win)-1-i;
        tmp->posY = 19;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }
    //MURI VERTICALI
    tmp->mapSymbol = 'x';
    for (int i = 1; i <= 8; ++i){
        tmp->posX = 28;
        tmp->posY = i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = 71;
        tmp->posY = getmaxy(win)-1-i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }

    tmp->posX=28;
    tmp->posY=6;
    tmp->next= NULL;
    interiorWalls = listInsert(interiorWalls, tmp);
    tmp->posX=69;
    tmp->posY=10;
    tmp->next=NULL;
    interiorWalls = listInsert(interiorWalls, tmp);

    return interiorWalls;


}



void printTemplate3(Wall* tmp){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(tmp->win, 7, 0, ACS_LTEE);
        mvwaddch(tmp->win, 19 , getmaxx(tmp->win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(tmp->win, 0, 28, ACS_TTEE);
        mvwaddch(tmp->win, getmaxy(tmp->win)-1, 71, ACS_BTEE);

        mvwaddch(tmp->win, 28, 6, ACS_TTEE);
        mvwaddch(tmp->win, 71, 4, ACS_TTEE);
        while(tmp != NULL){
            mvwaddch(tmp->win, tmp->posY, tmp->posX, NCURSES_ACS(tmp->mapSymbol));
            tmp = tmp->next;
        }
    }
}


Wall* template4(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, win);
    for (int i = 1; i <= 6; ++i) {
        tmp->posX = i;
        tmp->posY = 7;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = getmaxx(win)-1-i;
        tmp->posY = 19;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }
    //MURI VERTICALI
    tmp->mapSymbol = 'x';
    for (int i = 1; i <= 8; ++i){
        tmp->posX = 28;
        tmp->posY = i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
        tmp->posX = 71;
        tmp->posY = getmaxy(win)-1-i;
        tmp->next = NULL;
        interiorWalls = listInsert(interiorWalls, tmp);
    }

    tmp->posX=37;
    tmp->posY=2;
    tmp->next= NULL;
    interiorWalls = listInsert(interiorWalls, tmp);
    tmp->posX=75;
    tmp->posY=9;
    tmp->next=NULL;
    interiorWalls = listInsert(interiorWalls, tmp);

    return interiorWalls;


}



void printTemplate4(Wall* tmp){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(tmp->win, 7, 0, ACS_LTEE);
        mvwaddch(tmp->win, 19 , getmaxx(tmp->win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(tmp->win, 0, 28, ACS_TTEE);
        mvwaddch(tmp->win, getmaxy(tmp->win)-1, 71, ACS_BTEE);

        mvwaddch(tmp->win, 28, 6, ACS_TTEE);
        mvwaddch(tmp->win, 71, 4, ACS_TTEE);
        while(tmp != NULL){
            mvwaddch(tmp->win, tmp->posY, tmp->posX, NCURSES_ACS(tmp->mapSymbol));
            tmp = tmp->next;
        }
    }
}




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
