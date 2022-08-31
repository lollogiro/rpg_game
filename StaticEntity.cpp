//
// Created by lollo on 24/08/2022.
//

#include "StaticEntity.hpp"

StaticEntity::StaticEntity(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int givenLifePoints,
                           StaticEntity *next) : Entity(mapSymbol, posX, posY, secret, win),
                                                 givenLifePoints(givenLifePoints), next(next) {}

bool StaticEntity::checkStaticEntityPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, StaticEntity *powers, StaticEntity *artifacts){
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

    //TODO: check per non far spawnare entità nello stanzino

    return check;
}

int StaticEntity::getGivenLifePoints(){
    return givenLifePoints;
}