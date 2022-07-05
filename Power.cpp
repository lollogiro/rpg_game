//
// Created by lollo on 04/07/2022.
//

#include "Power.h"

Power::Power(char mapSymbol, int posX, int posY, WINDOW* win, Power* next)
        : Entity(mapSymbol, posX, posY, win){
    this->next = next;
}

bool Power::checkPowerPosition(int posXPower, int posYPower, Power *powers, Artifact *artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXPower == artifacts->posX && posYPower == artifacts->posY){
            check=false;
        }
        artifacts = artifacts->next;
    }
    while (check && powers != NULL){
        if(posXPower == powers->posX && posYPower == powers->posY){
            check=false;
        }
        powers = powers->next;
    }
    return check;
}