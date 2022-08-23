//
// Created by lollo on 04/07/2022.
//

#include "Artifact.hpp"

Artifact::Artifact(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int givenLifePoints, Artifact *next) : Entity(
        mapSymbol, posX, posY, secret, win){
    this->givenLifePoints = givenLifePoints;
    this->next = next;
}

bool Artifact::checkArtifactPosition(int posX, int posY, Wall* interiorWalls, Artifact* artifacts){
    bool check = true;
    while(check && artifacts != NULL){
        if(posX == artifacts->posX && posY == artifacts->posY){
            check = false;
        }
        artifacts = artifacts->next;
    }
    while (check && interiorWalls != NULL){
        if(posX == interiorWalls->getPosX() && posY == interiorWalls->getPosY()){
            check=false;
        }
        interiorWalls = interiorWalls->next;
    }
    return check;
}

int Artifact::getGivenLifePoints(){
    return givenLifePoints;
}

