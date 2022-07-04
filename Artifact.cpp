//
// Created by lollo on 04/07/2022.
//

#include "Artifact.h"

Artifact::Artifact(char mapSymbol, int posX, int posY, WINDOW *win, int givenLifePoints, Artifact *next) : Entity(
        mapSymbol, posX, posY, win){
    this->givenLifePoints = givenLifePoints;
    this->next = next;
}

void Artifact::printArtifact(){
    Entity::printEntity();
}

bool Artifact::checkArtifactPosition(int posXToCheck, int posYToCheck, Artifact* artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posXToCheck == artifacts->posX && posYToCheck == artifacts->posY){
            check = false;
        }
        artifacts = artifacts->next;
    }
    return check;
}