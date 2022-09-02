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
    this->walls = NULL;
    this->alreadyPassed = false;
    this->smallRoomOpened = false;
    this->win = win;
    this->nextLevel = NULL;
    this->precLevel = NULL;

}

void Level::manageNextLevelAccess(){
    if(alreadyPassed) {
        printHigherDoor(win, openedDoor);
    }
    else printHigherDoor(win, closedDoor);
}

void Level::managePrecLevelAccess(){
    if(levelNumber > 1) {
        printLowerDoor(win, openedDoor);
    }
}

void Level::manageSecretRoomAccess(){
    if(enemies == NULL || (enemies->next == NULL && enemies->getSecret())) printSecretDoor(win, openedDoor);
    else printSecretDoor(win, secretDoor);
}

void Level::initializeLevel(){
    initializeInteriorWalls();

    for (int i = 0; i < 2; ++i) {
        initializeArtifact(false, false, 0);
    }
    for (int i = 0; i < 2; i++){
        initializeArtifact(false, true, i);
    }
    for (int i = 0; i < 2; i++){
        initializeArtifact(true, false, i);
    }
    for (int i = 0; i < (levelNumber/4)+2; ++i) {
        initializePower(false);
    }
    StaticEntity* tmpPower = new StaticEntity('P', mainWinWidth/4, mainWinHeight/4, true, win, 30, NULL);
    tmpPower->next = powers;
    powers = tmpPower;

    int enemiesUB = 2;
    if(levelNumber > 3) enemiesUB = log2(levelNumber)+2;
    for (int i = 0; i < enemiesUB; ++i) {
        initializeEnemy(false);
    }
    initializeEnemy(true);

    Enemy* kamikaze = new Enemy ('K',getmaxx(win)/8,getmaxy(win)/4, true, win, 20, NULL, NULL);
    kamikaze->next = enemies;
    enemies = kamikaze;

}

void Level::initializeInteriorWalls(){
    switch(levelNumber % 4){
        case 1:
            this->walls = template1(win);
            break;
        case 2:
            this->walls = template2(win);
            break;
        case 3:
            this->walls = template3(win);
            break;
        case 0:
            this->walls = template4(win);
            break;
        default:
            break;
    }
}

void Level::initializeArtifact(bool secret, bool smallRoom, int inc){
    int posYNew = 0, posXNew = 0;
    if(!secret && !smallRoom){
        do {
            posYNew = rand() % (getmaxy(win) - 2) + 1;
            posXNew = rand() % (getmaxx(win) - 2) + 1;
        } while (!artifacts->checkStaticEntityPosition(posXNew, posYNew, walls, NULL, artifacts));
    }
    StaticEntity* tmp;
    if(!secret && !smallRoom) tmp = new StaticEntity('a', posXNew, posYNew, secret, win, ((int)log2(levelNumber))+1, NULL);
    else if(!secret && smallRoom) tmp = new StaticEntity('A' ,15*(inc+1), 5, false, win, ((int)log2(levelNumber)+1)*2, NULL);
    else tmp = new StaticEntity('A' ,mainWinWidth/6*2, mainWinHeight/6*(inc+1), true, win, ((int)log2(levelNumber)+1)*2, NULL);
    tmp->next = artifacts;
    artifacts = tmp;
}

void Level::initializePower(bool secret){
    int posYNew = 0, posXNew = 0;
    if(!secret){
        do {
            posYNew = rand() % (getmaxy(win) - 2) + 1;
            posXNew = rand() % (getmaxx(win) - 2) + 1;
        } while (!powers->checkStaticEntityPosition(posXNew, posYNew, walls, powers, artifacts));
    }
    StaticEntity* tmp;
    if(!secret) tmp = new StaticEntity('P' ,posXNew, posYNew, secret, win, 30, NULL);
    else tmp = new StaticEntity('P', mainWinWidth/4, mainWinHeight/4, true, win, 30, NULL);
    tmp->next = powers;
    powers = tmp;
}

void Level::initializeEnemy(bool muchStronger){
    int posXNew=rand()%(getmaxx(win)-2)+1, posYNew=0;
    if(!muchStronger){
        do {
            if (posXNew < (getmaxx(win) - 2) / 3) {
                posYNew = rand() % ((getmaxy(win) - 2) / 2) + 1;
            } else {
                posYNew = rand() % (getmaxy(win) - 2) + 1;
            }
        } while (!enemies->checkEnemyPosition(posXNew, posYNew, walls, enemies, powers, artifacts));
    }
    Enemy* tmp;
    if(muchStronger) tmp = new Enemy('E' ,22, 1, false, win, ((int)log2(levelNumber)+2)*levelNumber*2, NULL, NULL);
    else tmp = new Enemy('e' ,posXNew, posYNew, false, win, ((int)log2(levelNumber)+2)*levelNumber, NULL, NULL);
    tmp->next = enemies;
    enemies = tmp;


}

void Level::printArtifacts(bool secret){
    StaticEntity* tmp = artifacts;
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
    StaticEntity* tmp = powers;
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

void Level::printInteriorWalls(){
    switch(levelNumber % 4){
        case 1:
            printTemplate1(walls, win);
            break;
        case 2:
            printTemplate2(walls, win);
            break;
        case 3:
            printTemplate3(walls, win);
            break;
        case 0:
            printTemplate4(walls, win);
            break;
        default:
            break;
    }
}

void Level::printEntities(bool secret){
    printArtifacts(secret);
    printPowers(secret);
    printEnemies(secret);
    box(win, 0, 0);
    if(!secret) printInteriorWalls();
}

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
        StaticEntity* tmp = artifacts;
        StaticEntity* prec = NULL;
        while(tmp != NULL){
            if(player->getPosX() == tmp->getPosX() && player->getPosY() == tmp->getPosY() && (player->checkSecret(secret) == tmp->checkSecret(secret))){
                player->modifyLifepoints(tmp->getGivenLifePoints(), false);
                tmp->clear();
                StaticEntity* old = tmp;
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
        StaticEntity* tmp = powers;
        StaticEntity* prec = NULL;
        while(tmp != NULL){
            if(player->getPosX() == tmp->getPosX() && player->getPosY() == tmp->getPosY() && (player->checkSecret(secret) == tmp->checkSecret(secret))){
                player->modifyLifepoints(tmp->getGivenLifePoints(), false);
                tmp->clear();
                StaticEntity* old = tmp;
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

void Level::findAndCheckKamikaze(LivingEntity* player){
    Enemy* tmp = enemies;
    bool found = false;
    while(tmp != NULL && !found){
        if(tmp->getSecret()) found = true;
        else tmp = tmp->next;
    }
    if(found){
        if(player->checkKamikazeOnPlayer(player, tmp)) player->modifyLifepoints(15, true);
    }
}

void Level::checkCollisions(LivingEntity* player, bool secret){
    Enemy* tmp = enemies;
    while(tmp != NULL){
        checkCollisionsLivingEntity(player, tmp, secret);//FUNZIONA
        checkCollisionsLivingEntity(tmp, player, secret);
        tmp = tmp->next;
    }
    findAndCheckKamikaze(player);
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

void Level::restartLevels(Level* levels){
    while(levels->precLevel != NULL){
        levels = levels->precLevel;
        delete levels->nextLevel;
        levels->nextLevel = NULL;
    }
}

void Level::checkPassedLevel(){
    if(artifacts == NULL) alreadyPassed = true;
}

bool Level::checkMainWinPowers(){
    bool isPossible = true;
    StaticEntity* tmp = powers;
    while(tmp != NULL && isPossible){
        if(tmp->checkSecret(false)) isPossible = false;
        tmp = tmp->next;
    }
    return isPossible;
}

void Level::openSmallRoom(){
    smallRoomOpened = true;
    Wall* tmp = walls;
    for (int i = 0; i < 6; ++i) {
        walls = walls->next;
        tmp->printOpenDoor();
        delete tmp;
        tmp = walls;
    }
    walls = tmp;
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

Wall* Level::getWalls(){
    return walls;
}

bool Level::isSmallRoomOpened(){
    return smallRoomOpened;
}