//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ARTIFACT_H
#define PROGETTO_PROGRAMMAZIONE_ARTIFACT_H

#include "Entity.h"
#include "Wall.h"

class Artifact : public Entity{
public:
    int givenLifePoints;
    Artifact* next;

public:
    Artifact(char mapSymbol, int posX, int posY, WINDOW *win, int givenLifePoints, Artifact *next);
    bool checkArtifactPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Artifact* artifacts);
};



#endif //PROGETTO_PROGRAMMAZIONE_ARTIFACT_H
