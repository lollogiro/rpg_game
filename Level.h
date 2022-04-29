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
    Level(int levelNumber, Artifact* artifacts, Power* powers, WINDOW* win){
        this->levelNumber = levelNumber;
        this->artifacts = artifacts;
        this->powers = powers;
        this->alreadyPassed = false;
        this->win = win;
        this->nextLevel = NULL;
        this->precLevel = NULL;
    }

    void printHigherDoor(char doorString[]){
        int startPosition = ((getmaxx(win)-2)/2)-2;
        int endPosition = ((getmaxx(win)-2)/2)+3;
        for (int i = startPosition; i <= endPosition; ++i) {
            mvwaddch(win, 0, i, doorString[i-startPosition]);
        }
    }

    void printLowerDoor(char doorString[]){
        int startPosition = ((getmaxx(win)-2)/2)-2;
        int endPosition = ((getmaxx(win)-2)/2)+3;
        for (int i = startPosition; i <= endPosition; ++i) {
            mvwaddch(win, getmaxy(win)-1, i, doorString[i-startPosition]);
        }
    }

    void printSecretDoor(char doorString[]){
        int startPosition = ((getmaxy(win)-2)/2)-2;
        int endPosition = ((getmaxy(win)-2)/2)+3;
        for (int i = startPosition; i <= endPosition; ++i) {
            mvwaddch(win, i, getmaxx(win)-1, doorString[i-startPosition]);
        }
    }

    //TODO: stampare in una box piccola differente, tanti artefatti e un solo nemico al suo interno
    void printSecretRoom(){

    }

    //TODO: riempire con artifacts, powers e enemies
    //richiamerà printEntities, una volta con artifacts, una volta con powers e una volta con enemies, infine con il player.
    void initializeLevel(){
        for (int i = 0; i < 4; ++i) {
            initializeArtifact();
        }
        for (int i = 0; i < 4; ++i) {
            initializePower();
        }
    }

    void initializeArtifact(){
        int posYNew = 0, posXNew = 0;
        do{
            posYNew = rand() % (getmaxy(win) - 2) + 1;
            posXNew = rand() % (getmaxx(win) - 2) + 1;
        }while(!artifacts->checkArtifactPosition(posXNew, posYNew, artifacts));
        Artifact* tmp = new Artifact(posXNew, posYNew, 10, 'A', win);
        tmp->setNext(artifacts);
        artifacts = tmp;
    }

    void initializePower(){
        int posYNew = 0, posXNew = 0;
        do{
            posYNew = rand() % (getmaxy(win) - 2) + 1;
            posXNew = rand() % (getmaxx(win) - 2) + 1;
        }while(!powers->checkPowerPosition(posXNew, posYNew, powers, artifacts));
        Power* tmp = new Power(posXNew, posYNew, 'P', win);
        tmp->setNext(powers);
        powers = tmp;
    }

    //TODO: printEntities
    //while che sfrutterà la funzione padre printEntity, scorrendo tutta la lista di entità passata
    void printEntities(){
        artifacts->printArtifact(artifacts);
        powers->printPower(powers);
    }

    //TODO: checkCollisionsPlayerEnemies
    //checkBulletHit(), a cui si passano due entità shooterEntity, controllando se i proiettili della prima entità beccano le seconde entità
    //da richiamare una volta con primo argomento player e una volta con secondo argomento enemy, al suo interno ci sarà un while che scorrerà
    //per ogni nodo del primo argomento, tutti i nodi del secondo.

    //TODO: checkPlayerOnArtifact, in caso eliminare Artifact da lista
    /*
    Artifact* checkPlayerOnArtifact(Player* player, Artifact* artifacts){
        while(artifacts != NULL){
            if(artifacts->getPosX() == player->getPosx() && artifacts->getPosY() == player->getPosY()){
                //eliminazione da lista iterativa
            }
        }
    }
    */



};




#endif //PROGETTO_PROGRAMMAZIONE_LEVEL_H
