//
// Created by lollo on 04/07/2022.
//

#include "Level.h"
#include <math.h>

Level::Level(int levelNumber, Artifact* artifacts, Power* powers, Enemy* enemies, WINDOW* win){
    this->levelNumber = levelNumber;
    this->artifacts = artifacts;
    this->powers = powers;
    this->enemies = enemies;
    this->alreadyPassed = false;
    this->win = win;
    this->nextLevel = NULL;
    this->precLevel = NULL;
}

void Level::printHigherDoor(char doorString[]){
    int startPosition = ((getmaxx(win)-2)/2)-2;
    int endPosition = ((getmaxx(win)-2)/2)+3;
    for (int i = startPosition; i <= endPosition; ++i) {
        mvwaddch(win, 0, i, doorString[i-startPosition]);
    }
}

void Level::printLowerDoor(char doorString[]){
    int startPosition = ((getmaxx(win)-2)/2)-2;
    int endPosition = ((getmaxx(win)-2)/2)+3;
    for (int i = startPosition; i <= endPosition; ++i) {
        mvwaddch(win, getmaxy(win)-1, i, doorString[i-startPosition]);
    }
}

void Level::printSecretDoor(char doorString[]){
    int startPosition = ((getmaxy(win)-2)/2)-2;
    int endPosition = ((getmaxy(win)-2)/2)+3;
    for (int i = startPosition; i <= endPosition; ++i) {
        mvwaddch(win, i, getmaxx(win)-1, doorString[i-startPosition]);
    }
}

//TODO: stampare in una box piccola differente, tanti artefatti e un solo nemico al suo interno
void Level::printSecretRoom(){

}

//TODO: riempire con artifacts, powers e enemies
//richiamerà printEntities, una volta con artifacts, una volta con powers e una volta con enemies, infine con il player.
void Level::initializeLevel(){
    for (int i = 0; i < (levelNumber/4)+1; ++i) {
        initializeArtifact();
    }
    for (int i = 0; i < 5; ++i) {
        initializePower();
    }
    int enemiesUB = 2;
    if(levelNumber > 3) enemiesUB = (int)log2(levelNumber);
    for (int i = 0; i < enemiesUB; ++i) {
        initializeEnemy();
    }
}

void Level::initializeArtifact(){
    int posYNew = 0, posXNew = 0;
    do{
        posYNew = rand() % (getmaxy(win) - 2) + 1;
        posXNew = rand() % (getmaxx(win) - 2) + 1;
    }while(!artifacts->checkArtifactPosition(posXNew, posYNew, artifacts));
    Artifact* tmp = new Artifact('A', posXNew, posYNew, win, 10, NULL);
    tmp->next = artifacts;
    artifacts = tmp;
}

void Level::initializePower(){
    int posYNew = 0, posXNew = 0;
    do{
        posYNew = rand() % (getmaxy(win) - 2) + 1;
        posXNew = rand() % (getmaxx(win) - 2) + 1;
    }while(!powers->checkPowerPosition(posXNew, posYNew, powers, artifacts));
    Power* tmp = new Power('P' ,posXNew, posYNew, win, NULL);
    tmp->next = powers;
    powers = tmp;
}

void Level::initializeEnemy(){
    int posXNew=rand()%(getmaxx(win)-2)+1, posYNew=0;
    do{
        if (posXNew<(getmaxx(win)-2)/3){
            posYNew=rand()%((getmaxy(win)-2)/2)+1;
        }
        else {
            posYNew=rand()%(getmaxy(win)-2)+1;
        }
    }while(!enemies->checkEnemyPosition(posXNew, posYNew, enemies, powers, artifacts));
    Enemy* tmp = new Enemy('E' ,posXNew, posYNew, win, 10, NULL, NULL);
    tmp->next = enemies;
    enemies = tmp;
}

void Level::printArtifacts(){
    Artifact* tmp = artifacts;
    while(tmp != NULL){
        tmp->printEntity();
        tmp = tmp->next;
    }
}

void Level::printPowers(){
    Power* tmp = powers;
    while(tmp != NULL){
        tmp->printEntity();
        tmp = tmp->next;
    }
}

//TODO: void Level::printEnemies()
void Level::printEnemies(){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->printEntity();
        tmp = tmp->next;
    }
}

void Level::printEntities(){
    printArtifacts();
    printPowers();
    printEnemies();
}

void Level::printEnemiesBullets(){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->printEntityBullets();
        tmp = tmp->next;
    }
}

void Level::updateEnemiesBullets(){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->updateBulletPosition();
        tmp = tmp->next;
    }
}

void Level::updateEnemiesPosition(LivingEntity* player){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->moveChooser(player);
        tmp = tmp->next;
    }
}

//TODO: checkCollisionsPlayerEnemies
//checkBulletHit(), a cui si passano due entità shooterEntity, controllando se i proiettili della prima entità beccano le seconde entità
//da richiamare una volta con primo argomento player e una volta con secondo argomento enemy, al suo interno ci sarà un while che scorrerà
//per ogni nodo del primo argomento, tutti i nodi del secondo.

//TODO: checkPlayerOnArtifact, in caso eliminare Artifact da lista
/*
Artifact* Level::checkPlayerOnArtifact(LivingEntity* player, Artifact* artifacts){
    while(artifacts != NULL){
        if(artifacts->getPosX() == player->getPosx() && artifacts->getPosY() == player->getPosY()){
            //eliminazione da lista iterativa
        }
    }
}
*/
