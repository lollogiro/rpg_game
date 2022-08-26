//
// Created by lollo on 17/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVEL_HPP
#define PROGETTO_PROGRAMMAZIONE_LEVEL_HPP


#include <iostream>
#include "Artifact.hpp"
#include "Power.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "GameState.hpp"

#pragma once

class Level {
protected:
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
    /*
     * Costruttore della classe Level
     */
    Level(int levelNumber, WINDOW* win);

    /*
     * Metodo che si occupa di gestire gli assegnamenti utili a passare al livello successivo
     */
    void manageNextLevelAccess();

    /*
     * Metodo che serve per stampare la porta superiore utilizzata per passare al livello successivo
     */
    void printHigherDoor(char doorString[]);

    /*
     * Metodo che si occupa di gestire gli assegnamenti utili a passare al livello precedente
     */
    void managePrecLevelAccess();

    /*
     * Metodo che serve per stampare la porta inferiore utilizzata per passare al livello precedente, se possibile
     */
    void printLowerDoor(char doorString[]);

    /*
     * Metodo che si occupa di gestire gli assegnamenti utili a passare alla SecretRoom
     */
    void manageSecretRoomAccess();

    /*
     * Metodo che serve per stampare la porta laterale utilizzata per passare alla SecretRoom
     */
    void printSecretDoor(char doorString[]);

    /*
     * Metodo utilizzato per la generazione di tutte le entità presenti nel livello
     */
    void initializeLevel();

    /*
     * Metodo utilizzato per la generazione di un artefatto
     */
    void initializeArtifact(bool secret);

    void initializePower(bool secret);

    void initializeEnemy(bool secret);

    void printArtifacts(bool secret);

    void printPowers(bool secret);

    void printEnemies(bool secret);

    void printEntities();

    void printSecretEntities();

    void printEnemiesBullets(bool secret);

    void updateEnemiesBullets(bool secret);

    void updateEnemiesPosition(LivingEntity* player, bool secret);

    void checkCollisionsLivingEntity(LivingEntity* shooted, LivingEntity* shooter, bool secret);

    void checkCollisionsArtifacts(LivingEntity* player, bool secret);

    void checkCollisionsPowers(LivingEntity* player, bool secret);

    void checkCollisions(LivingEntity* player, bool secret);

    void deleteNotValidEnemies();

    GameState deleteUselessEntities(LivingEntity* player);

    Level* moveToNextLevel(Level* levels);

    Level* moveToPrecLevel(Level* levels);

    void checkPassedLevel();

    int getLevelNumber();

    bool isAlreadyPassed();

    bool isGreaterThanOne();

    bool isSecretRoomAccessible();

    Wall *getWalls();
};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_HPP
