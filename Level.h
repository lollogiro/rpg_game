//
// Created by lollo on 17/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVEL_H
#define PROGETTO_PROGRAMMAZIONE_LEVEL_H


#include <iostream>
#include "Artifact.h"
#include "Power.h"

class Level {
public:
    int levelNumber;
    //Enemy* enemies;
    Artifact* artifacts;
    Power* powers;
    bool alreadyPassed;
    WINDOW* win;
    Level* nextLevel;
    Level* precLevel;

public:
    Level(int levelNumber, Artifact* artifacts, Power* powers, WINDOW* win);

    void printHigherDoor(char doorString[]);

    void printLowerDoor(char doorString[]);

    void printSecretDoor(char doorString[]);

    //TODO: stampare in una box piccola differente, tanti artefatti e un solo nemico al suo interno
    void printSecretRoom();

    //TODO: riempire con artifacts, powers e enemies
    //richiamerà printEntities, una volta con artifacts, una volta con powers e una volta con enemies, infine con il player.
    void initializeLevel();

    void initializeArtifact();

    void initializePower();

    void printArtifacts();

    void printPowers();

    void printEntities();




};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_H
