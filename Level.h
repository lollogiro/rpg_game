//
// Created by lollo on 17/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVEL_H
#define PROGETTO_PROGRAMMAZIONE_LEVEL_H


#include <iostream>
#include "Artifact.h"
#include "Power.h"
#include "Enemy.h"
#include "Wall.h"

class Level {
public:
    int levelNumber;
    Artifact* artifacts;
    Power* powers;
    Enemy* enemies;
    Wall* walls;
    bool alreadyPassed;
    WINDOW* win;
    Level* nextLevel;
    Level* precLevel;

public:
    Level(int levelNumber, WINDOW* win);

    void printHigherDoor(char doorString[]);

    void printLowerDoor(char doorString[]);

    void printSecretDoor(char doorString[]);

    //TODO: stampare in una box piccola differente, tanti artefatti e un solo nemico al suo interno
    void printSecretRoom();

    void initializeLevel();

    void initializeArtifact();

    void initializePower();

    void initializeEnemy();

    void printArtifacts();

    void printPowers();

    void printEnemies();

    void printEntities();

    void printEnemiesBullets();

    void updateEnemiesBullets();

    void updateEnemiesPosition(LivingEntity* player);

    void checkCollisionsLivingEntity(LivingEntity* shooted, LivingEntity* shooter);

    void checkCollisionsArtifacts(LivingEntity* player);

    void checkCollisionsPowers(LivingEntity* player);

    void checkCollisions(LivingEntity* player);

    void deleteNotValidEnemies();

    bool deleteUselessEntities(LivingEntity* player);

    void clearWindowFromEntities(LivingEntity* player);
};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_H
