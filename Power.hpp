//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_POWER_HPP
#define PROGETTO_PROGRAMMAZIONE_POWER_HPP

#include "Entity.hpp"
#include "Artifact.hpp"

#pragma once

class Power : public Entity{
public:
    Power* next;

public:
    Power(char mapSymbol, int posX, int posY, bool secret, WINDOW* win, Power* next);
    bool checkPowerPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, Power* powers, Artifact* artifacts);
};

#endif //PROGETTO_PROGRAMMAZIONE_POWER_HPP
