//
// Created by lollo on 04/07/2022.
//

#include "Power.hpp"

Power::Power(char mapSymbol, int posX, int posY, bool secret, WINDOW* win, Power* next)
        : Entity(mapSymbol, posX, posY, secret, win){
    this->next = next;
}

bool Power::checkPowerPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Power *powers, Artifact *artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXToCheck == artifacts->getPosX() && posYToCheck == artifacts->getPosY()){
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
        if(posXToCheck == interiorWalls->getPosX() && posYToCheck == interiorWalls->getPosY()){
            check=false;
        }
        interiorWalls = interiorWalls->next;
    }
    return check;
}