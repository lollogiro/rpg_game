//
// Created by lollo on 04/07/2022.
//

#include "Level.h"
#include <cmath>
#include <cstring>

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
    delete tmp;
}

void Level::printPowers(){
    Power* tmp = powers;
    while(tmp != NULL){
        tmp->printEntity();
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::printEnemies(){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->printEntity();
        tmp = tmp->next;
    }
    delete tmp;
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
    delete tmp;
}

void Level::updateEnemiesBullets(){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->updateBulletPosition();
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::updateEnemiesPosition(LivingEntity* player){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        tmp->moveChooser(player);
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::checkCollisionsLivingEntity(LivingEntity* hit, LivingEntity* shooter){
    int posXHit = hit->posX, posYHit = hit->posY;
    Bullet* tmp = shooter->bullets;
    while(tmp != NULL){
        if(tmp->posX == posXHit && tmp->posY == posYHit){
            hit->lifePoints -= tmp->damage;
            tmp->posX = -1000;//per invalidare il bullet
        }
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::checkCollisionsArtifacts(LivingEntity* player){
    if(artifacts != NULL){
        Artifact* tmp = artifacts;
        Artifact* prec = NULL;
        while(tmp != NULL){
            if(player->posX == tmp->posX && player->posY == tmp->posY){
                player->lifePoints += tmp->givenLifePoints;
                mvwaddch(win, tmp->posY, tmp->posX, ' ');
                Artifact* old = tmp;
                if(prec == NULL) artifacts = artifacts->next;
                else prec->next = tmp->next;
                tmp = tmp->next;
                delete old;
            }
            else{
                prec = tmp;
                tmp = tmp->next;
            }
        }
        delete tmp;
    }
}

void Level::checkCollisionsPowers(LivingEntity* player){
    if(powers != NULL){
        Power* tmp = powers;
        Power* prec = NULL;
        while(tmp != NULL){
            if(player->posX == tmp->posX && player->posY == tmp->posY){
                mvwaddch(win, tmp->posY, tmp->posX, ' ');
                Power* old = tmp;
                if(prec == NULL) powers = powers->next;
                else prec->next = tmp->next;
                tmp = tmp->next;
                delete old;
            }
            else{
                prec = tmp;
                tmp = tmp->next;
            }
        }
        delete tmp;
    }
}

void Level::checkCollisions(LivingEntity* player){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        checkCollisionsLivingEntity(player, tmp);//FUNZIONA
        checkCollisionsLivingEntity(tmp, player);
        tmp = tmp->next;
    }
    delete tmp;
    checkCollisionsArtifacts(player);
    checkCollisionsPowers(player);
    deleteUselessEntities(player);
}

void Level::deleteNotValidEnemies(){
    if(enemies != NULL){
        Enemy* tmp = enemies;
        Enemy* prec = NULL;
        while(tmp != NULL){
            if(tmp->lifePoints <= 0){
                //TODO: cancellare anche bullet dell'enemy per non sprecare memoria(?)
                mvwaddch(win, tmp->posY, tmp->posX, ' ');
                Enemy* old = tmp;
                if(prec == NULL) enemies = enemies->next;
                else prec->next = tmp->next;
                tmp = tmp->next;
                delete old;
            }
            else{
                prec = tmp;
                tmp = tmp->next;
            }
        }
        delete tmp;
    }
}

bool Level::deleteUselessEntities(LivingEntity* player){
    if(player->lifePoints <= 0){
        //GAME OVER
        return false;
    }
    deleteNotValidEnemies();
    return true;
}

void Level::clearWindowFromEntities(LivingEntity* player){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        mvwaddch(win, tmp->posY, tmp->posX, ' ');
        tmp = tmp->next;
    }
    delete tmp;
    Artifact* tmp1 = artifacts;
    while(tmp1 != NULL){
        mvwaddch(win, tmp1->posY, tmp1->posX, ' ');
        tmp1 = tmp1->next;
    }
    delete tmp1;
    Power* tmp2 = powers;
    while(tmp2 != NULL){
        mvwaddch(win, tmp2->posY, tmp2->posX, ' ');
        tmp2 = tmp2->next;
    }
    delete tmp2;
    Bullet* tmp3 = player->bullets;
    while(tmp3 != NULL){
        tmp3->posX = -1000;
        tmp3 = tmp3->next;
    }
    player->deleteNotValidBullet();
    delete tmp3;
}
