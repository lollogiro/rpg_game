//
// Created by lollo on 04/07/2022.
//

#include "Level.hpp"
#include "constants.hpp"
#include <cmath>

Level::Level(int levelNumber, WINDOW* win){
    this->levelNumber = levelNumber;
    this->artifacts = NULL;
    this->powers = NULL;
    this->enemies = NULL;
    else this->walls = NULL;
    this->alreadyPassed = false;
    this->win = win;
    this->nextLevel = NULL;
    this->precLevel = NULL;
    switch(levelNumber % 4) {
        case 0:
            this->walls = template1(win);
            break;
        case 1:
            this->walls = template2(win);
            break;
        case 2:
            this->walls = template3(win);
            break;
        case 3:
            this->walls = template4(win);
            break;
        default:
            break;
    }
}

void Level::manageNextLevelAccess(){
    if(alreadyPassed) {
        printHigherDoor(openedDoor);
    }
    else printHigherDoor(closedDoor);
}

void Level::printHigherDoor(char doorString[]){
    int startPosition = ((getmaxx(win)-2)/2)-2;
    int endPosition = ((getmaxx(win)-2)/2)+3;
    for (int i = startPosition; i <= endPosition; ++i) {
        mvwaddch(win, 0, i, doorString[i-startPosition]);
    }
}

void Level::managePrecLevelAccess(){
    if(levelNumber > 1) {
        printLowerDoor(openedDoor);
    }
}


void Level::printLowerDoor(char doorString[]){
    int startPosition = ((getmaxx(win)-2)/2)-2;
    int endPosition = ((getmaxx(win)-2)/2)+3;
    for (int i = startPosition; i <= endPosition; ++i) {
        mvwaddch(win, getmaxy(win)-1, i, doorString[i-startPosition]);
    }
}

void Level::manageSecretRoomAccess(){
    if(enemies == NULL || (enemies->next == NULL && enemies->getSecret())) printSecretDoor(openedDoor);
    else printSecretDoor(secretDoor);
}

void Level::printSecretDoor(char doorString[]){
    int startPosition = ((getmaxy(win)-2)/2)-2;
    int endPosition = ((getmaxy(win)-2)/2)+3;
    for (int i = startPosition; i <= endPosition; ++i) {
        mvwaddch(win, i, getmaxx(win)-1, doorString[i-startPosition]);
    }
}

void Level::initializeLevel(){
    for (int i = 0; i < (levelNumber/4)+1; ++i) {
        initializeArtifact(false);
    }
    Artifact* tmpSecret1 = new Artifact('A', mainWinWidth/4, mainWinHeight/4, true, win, 10, NULL);
    tmpSecret1->next = artifacts;
    artifacts = tmpSecret1;
    for (int i = 0; i < 4; ++i) {
        initializePower(false);
    }
    for (int i = 0; i < 2; i++){
        Power* tmpSecret2 = new Power('P' ,mainWinWidth/6*2, mainWinHeight/6*(i+1), true, win, NULL);
        tmpSecret2->next = powers;
        powers = tmpSecret2;
    }
    int enemiesUB = 2;
    if(levelNumber > 3) enemiesUB = (levelNumber/4)+1;
    for (int i = 0; i < enemiesUB; ++i) {
        initializeEnemy(false);
    }
    Enemy* tmpSecret3 = new Enemy('E' ,mainWinWidth/6, mainWinHeight/4, true, win, ((int)log2(levelNumber)+2)*levelNumber*2, NULL, NULL);
    tmpSecret3->next = enemies;
    enemies = tmpSecret3;
}

void Level::initializeArtifact(bool secret){
    int posYNew = 0, posXNew = 0;
    do{
        if(!secret) {
            posYNew = rand() % (getmaxy(win) - 2) + 1;
            posXNew = rand() % (getmaxx(win) - 2) + 1;
        }else{
            posYNew = rand() % (getmaxy(win)/2 - 2) + 1;
            posXNew = rand() % (getmaxx(win)/2 - 2) + 1;
        }
    }while(!artifacts->checkArtifactPosition(posXNew, posYNew, walls, artifacts));
    Artifact* tmp = new Artifact('A', posXNew, posYNew, secret, win, ((int)log2(levelNumber)+1)*2, NULL);
    tmp->next = artifacts;
    artifacts = tmp;
}

void Level::initializePower(bool secret){
    int posYNew = 0, posXNew = 0;
    do{
        if(!secret) {
            posYNew = rand() % (getmaxy(win) - 2) + 1;
            posXNew = rand() % (getmaxx(win) - 2) + 1;
        }else{
            posYNew = rand() % (getmaxy(win)/2 - 2) + 1;
            posXNew = rand() % (getmaxx(win)/2 - 2) + 1;
        }
    }while(!powers->checkPowerPosition(posXNew, posYNew, walls, powers, artifacts));
    Power* tmp = new Power('P' ,posXNew, posYNew, secret, win, NULL);
    tmp->next = powers;
    powers = tmp;
}

void Level::initializeEnemy(bool secret){
    int posXNew=rand()%(getmaxx(win)-2)+1, posYNew=0;
    do{
        if(!secret) {
            if (posXNew<(getmaxx(win)-2)/3){
                posYNew=rand()%((getmaxy(win)-2)/2)+1;
            }
            else {
                posYNew=rand()%(getmaxy(win)-2)+1;
            }
        }else{
            if (posXNew<(getmaxx(win)/2-2)/3){
                posYNew=rand()%((getmaxy(win)/2-2)/2)+1;
            }
            else {
                posYNew=rand()%(getmaxy(win)/2-2)+1;
            }
        }
    }while(!enemies->checkEnemyPosition(posXNew, posYNew, walls, enemies, powers, artifacts));
    Enemy* tmp = new Enemy('E' ,posXNew, posYNew, secret, win, ((int)log2(levelNumber)+2)*levelNumber, NULL, NULL);
    tmp->next = enemies;
    enemies = tmp;
}

void Level::printArtifacts(bool secret){
    Artifact* tmp = artifacts;
    while(tmp != NULL){
        if(tmp->checkSecret(secret)){
            wattron(win, COLOR_PAIR(artifactColor));
            tmp->print();
            wattroff(win, COLOR_PAIR(artifactColor));
        };
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::printPowers(bool secret){
    Power* tmp = powers;
    while(tmp != NULL){
        if(tmp->checkSecret(secret)){
            wattron(win, COLOR_PAIR(powerColor));
            tmp->print();
            wattroff(win, COLOR_PAIR(powerColor));
        }
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::printEnemies(bool secret){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        if(tmp->checkSecret(secret)){
            wattron(win, COLOR_PAIR(enemyColor));
            tmp->print();
            wattroff(win, COLOR_PAIR(enemyColor));
        }
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::printEntities(){
    printArtifacts(false);
    printPowers(false);
    printEnemies(false);
    box(win, 0, 0);
    switch(levelNumber % 4) {
        case 0:
            printTemplate1(template1(win));
            break;
        case 1:
            printTemplate2(template2(win));
            break;
        case 2:
            printTemplate3(template3(win));
            break;
        case 3:
            printTemplate4(template4(win));
            break;
        default:
            break;
    }




    }
}

void Level::printSecretEntities(){
    printArtifacts(true);
    printPowers(true);
    printEnemies(true);
}

//TODO: printWalls fatto dalla carol

void Level::printEnemiesBullets(bool secret){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        if(tmp->checkSecret(secret)) tmp->printEntityBullets();
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::updateEnemiesBullets(bool secret){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        if(tmp->checkSecret(secret)) tmp->updateBulletPosition(walls);
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::updateEnemiesPosition(LivingEntity* player, bool secret){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        if(tmp->checkSecret(secret)) tmp->moveChooser(player, walls, levelNumber);
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::checkCollisionsLivingEntity(LivingEntity* hit, LivingEntity* shooter, bool secret){
    int posXHit = hit->getPosX(), posYHit = hit->getPosY();
    Bullet* tmp = shooter->bullets;
    while(tmp != NULL){
        if(tmp->getPosX() == posXHit && tmp->getPosY() == posYHit && (hit->checkSecret(secret) == shooter->checkSecret(secret))){
            hit->modifyLifepoints(tmp->getDamage(), true);
            tmp->invalidBullet();
        }
        tmp = tmp->next;
    }
    delete tmp;
}

void Level::checkCollisionsArtifacts(LivingEntity* player, bool secret){
    if(artifacts != NULL){
        Artifact* tmp = artifacts;
        Artifact* prec = NULL;
        while(tmp != NULL){
            if(player->getPosX() == tmp->getPosX() && player->getPosY() == tmp->getPosY() && (player->checkSecret(secret) == tmp->checkSecret(secret))){
                player->modifyLifepoints(tmp->getGivenLifePoints(), false);
                tmp->clear();
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

void Level::checkCollisionsPowers(LivingEntity* player, bool secret){
    if(powers != NULL){
        Power* tmp = powers;
        Power* prec = NULL;
        while(tmp != NULL){
            if(player->getPosX() == tmp->getPosX() && player->getPosY() == tmp->getPosY() && (player->checkSecret(secret) == tmp->checkSecret(secret))){
                tmp->clear();
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

void Level::checkCollisions(LivingEntity* player, bool secret){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        checkCollisionsLivingEntity(player, tmp, secret);//FUNZIONA
        checkCollisionsLivingEntity(tmp, player, secret);
        tmp = tmp->next;
    }
    delete tmp;
    checkCollisionsArtifacts(player, secret);
    checkCollisionsPowers(player, secret);
    deleteUselessEntities(player);
}

void Level::deleteNotValidEnemies(){
    if(enemies != NULL){
        Enemy* tmp = enemies;
        Enemy* prec = NULL;
        while(tmp != NULL){
            if(!tmp->isValid()){
                delete tmp->bullets;
                tmp->clear();
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

GameState Level::deleteUselessEntities(LivingEntity* player){
    if(!player->isValid()){
        //GAME OVER
        return LOSS;
    }
    deleteNotValidEnemies();
    return IN_GAME;
}

Level* Level::moveToNextLevel(Level* levels){
    if(levels->nextLevel == NULL){
        Level* tmp = new Level(levels->getLevelNumber()+1, win);
        levels->nextLevel = tmp;
        tmp->precLevel = levels;
        levels = levels->nextLevel;
        levels->initializeLevel();
    }else{
        levels = levels->nextLevel;
    }
    return levels;
}

Level* Level::moveToPrecLevel(Level *levels){
    levels = levels->precLevel;
    if(levels->precLevel == NULL) box(win, 0, 0);
    return levels;
}

void Level::checkPassedLevel(){
    if(powers == NULL) alreadyPassed = true;
}

int Level::getLevelNumber(){
    return levelNumber;
}

bool Level::isAlreadyPassed(){
    return alreadyPassed;
}

bool Level::isGreaterThanOne(){
    return levelNumber > 1;
}

bool Level::isSecretRoomAccessible(){
    return enemies == NULL || (enemies->next == NULL && enemies->getSecret());
}

Wall *Level::getWalls(){
    return walls;
}
