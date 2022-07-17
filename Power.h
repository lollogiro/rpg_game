//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_POWER_H
#define PROGETTO_PROGRAMMAZIONE_POWER_H

#include "Entity.h"
#include "Artifact.h"

class Power : public Entity{
public:
    Power* next;

public:
    Power(char mapSymbol, int posX, int posY, WINDOW* win, Power* next);
    bool checkPowerPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Power* powers, Artifact* artifacts);
};

#endif //PROGETTO_PROGRAMMAZIONE_POWER_H
