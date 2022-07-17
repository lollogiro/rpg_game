//
// Created by lollo on 04/07/2022.
//

#include "Artifact.h"

Artifact::Artifact(char mapSymbol, int posX, int posY, WINDOW *win, int givenLifePoints, Artifact *next) : Entity(
        mapSymbol, posX, posY, win){
    this->givenLifePoints = givenLifePoints;
    this->next = next;
}

bool Artifact::checkArtifactPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Artifact* artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXToCheck == artifacts->posX && posYToCheck == artifacts->posY){
            check = false;
        }
        artifacts = artifacts->next;
    }
    while (check && interiorWalls != NULL){
        if(posXToCheck == interiorWalls->posX && posYToCheck == interiorWalls->posY){
            check=false;
        }
        interiorWalls = interiorWalls->next;
    }
    return check;
}