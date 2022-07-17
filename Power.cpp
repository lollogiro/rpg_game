//
// Created by lollo on 04/07/2022.
//

#include "Power.h"

Power::Power(char mapSymbol, int posX, int posY, WINDOW* win, Power* next)
        : Entity(mapSymbol, posX, posY, win){
    this->next = next;
}

bool Power::checkPowerPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Power *powers, Artifact *artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXToCheck == artifacts->posX && posYToCheck == artifacts->posY){
            check=false;
        }
        artifacts = artifacts->next;
    }
    while (check && powers != NULL){
        if(posXToCheck == powers->posX && posYToCheck == powers->posY){
            check=false;
        }
        powers = powers->next;
    }
    while (check && interiorWalls != NULL){
        if(posXToCheck == interiorWalls->posX && posYToCheck == interiorWalls->posY){
            check=false;
        }
        interiorWalls = interiorWalls->next;
    }
    return check;
}