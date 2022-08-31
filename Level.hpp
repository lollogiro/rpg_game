//
// Created by lollo on 17/03/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_LEVEL_HPP
#define PROGETTO_PROGRAMMAZIONE_LEVEL_HPP


#include <iostream>
#include "StaticEntity.hpp"
#include "Enemy.hpp"
#include "Wall.hpp"
#include "GameState.hpp"

#pragma once

class Level {
protected:
    int levelNumber;
    StaticEntity* artifacts;
    StaticEntity* powers;
    Enemy* enemies;
    Wall* walls;
    bool alreadyPassed;
    bool smallRoomOpened;
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
     * Metodo che si occupa di gestire gli assegnamenti utili a passare al livello precedente
     */
    void managePrecLevelAccess();

    /*
     * Metodo che si occupa di gestire gli assegnamenti utili a passare alla SecretRoom
     */
    void manageSecretRoomAccess();

    /*
     * Metodo utilizzato per la generazione di tutte le entità presenti nel livello
     */
    void initializeLevel();

    /*
     * Metodo utilizzato per la scelta del template di muri interni
     */
    void initializeInteriorWalls();

    /*
     * Metodo utilizzato per la generazione di un artefatto
     */
    void initializeArtifact(bool secret);

    /*
     * Metodo utilizzato per la generazione di un potere
     */
    void initializePower(bool secret);

    /*
     * Metodo utilizzato per la generazione di un nemico
     */
    void initializeEnemy(bool muchStronger);

    /*
     * Metodo utilizzato per la stampa degli artefatti in base alla stanza di appartenenza
     */
    void printArtifacts(bool secret);

    /*
     * Metodo utilizzato per la stampa degi poteri in base alla stanza di appartenenza
     */
    void printPowers(bool secret);

    /*
     * Metodo utilizzato per la stampa dei nemici in base alla stanza di appartenenza
     */
    void printEnemies(bool secret);

    /*
     * Metodo utilizzato per la stampa dei muri interni
     */
    void printInteriorWalls();

    /*
     * Metodo utilizzato per la stampa delle entità in base alla stanza di appartenenza
     */
    void printEntities(bool secret);

    /*
     * Metodo utilizzato per la stampa dei proiettili dei nemici in base alla stanza di appartenenza
     */
    void printEnemiesBullets(bool secret);

    /*
     * Metodo utilizzato per l'aggiornamento della posizione dei proiettili in base alla stanza di appartenenza
     */
    void updateEnemiesBullets(bool secret);

    /*
     * Metodo utilizzato per l'aggiornamento della posizione dei nemici in base alla stanza di appartenenza
     */
    void updateEnemiesPosition(LivingEntity* player, bool secret);

    /*
     * Metodo utilizzato per verificare se ci sono collisioni tra LivingEntity
     */
    void checkCollisionsLivingEntity(LivingEntity* shooted, LivingEntity* shooter, bool secret);

    /*
     * Metodo utilizzato per verificare se ci sono collisioni tra player ed artefatti
     */
    void checkCollisionsArtifacts(LivingEntity* player, bool secret);

    /*
     * Metodo utilizzato per verificare se ci sono collisioni tra player e poteri
     */
    void checkCollisionsPowers(LivingEntity* player, bool secret);

    /*
     * Metodo che cerca il nemico di tipo Kamikaze all'interno della lista di nemici, restituisce NULL se non lo trova
     */
    void findAndCheckKamikaze(LivingEntity* player);

    /*
     * Metodo utilizzato per verificare se ci sono collisioni tra tutte le entità
     */
    void checkCollisions(LivingEntity* player, bool secret);

    /*
     * Metodo utilizzato per eliminare nemici con lifepoints < 0
     */
    void deleteNotValidEnemies();

    /*
     * Metodo utilizzato per eliminare entità che non sono più "in gioco"
     */
    GameState deleteUselessEntities(LivingEntity* player);

    /*
     * Metodo utilizzato per eseguire gli assegnamenti utili a spostare il player al livello successivo
     */
    Level* moveToNextLevel(Level* levels);

    /*
     * Metodo utilizzato per eseguire gli assegnamenti utili a spostare il player al livello precedente
     */
    Level* moveToPrecLevel(Level* levels);

    /*
     * Metodo utilizzato per aggiornare, se necessario, l'attributo alreadyPassed
     */
    void checkPassedLevel();

    /*
     * Metodo per verificare se è possibile sbloccare il passaggio all'interno della stanza principale
     */
    bool checkMainWinPowers();

    //TODO: commentare
    void openSmallRoom();

    /*
     * Vari metodi di tipo getter
     */

    int getLevelNumber();

    bool isAlreadyPassed();

    bool isGreaterThanOne();

    bool isSecretRoomAccessible();

    bool isSmallRoomOpened();

    Wall *getWalls();
};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_HPP
