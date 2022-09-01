#include "LivingEntity.hpp"
#include "constants.hpp"
#include <cmath>

LivingEntity::LivingEntity(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int lifePoints, Bullet *bullets)
        : Entity(mapSymbol, posX, posY, secret, win) {
    this->lifePoints = lifePoints;
    this->bullets = bullets;
}

void LivingEntity::moveUp(bool openedDoor, bool secretDoor, Wall* interiorWalls){
    mvwaddch(win, posY, posX, ' ');
    posY--;
    if((posY < 1 && !openedDoor) || (posY < 1 && openedDoor && (posX < ((getmaxx(win)-2)/2)-2 || posX > ((getmaxx(win)-2)/2)+3))) posY = 1;
    else if(posY < 0 && openedDoor && posX >= ((getmaxx(win)-2)/2)-2 && posX <= ((getmaxx(win)-2)/2)+3) posY = 0;
    else if(posX == getmaxx(win)-1 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posY++;
    while(interiorWalls != NULL){
        if(posX == interiorWalls->getPosX() && posY == interiorWalls->getPosY()){
            posY++;
            break;
        }
        interiorWalls = interiorWalls->next;
    }
    wrefresh(win);
}

void LivingEntity::moveDown(bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls){
    mvwaddch(win, posY, posX, ' ');
    posY++;
    if((posY > getmaxy(win)-2 && !levelGreaterThanOne) || (posY > getmaxy(win)-2 && levelGreaterThanOne && (posX < ((getmaxx(win)-2)/2)-2 || posX > ((getmaxx(win)-2)/2)+3))) posY = getmaxy(win) - 2;
    else if(posY > getmaxy(win)-1 && levelGreaterThanOne && posX >= ((getmaxx(win)-2)/2)-2 && posX <= ((getmaxx(win)-2)/2)+3) posY = getmaxy(win)-1;
    else if(posX == getmaxx(win)-1 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posY--;
    while(interiorWalls != NULL){
        if(posX == interiorWalls->getPosX() && posY == interiorWalls->getPosY()){
            posY--;
            break;
        }
        interiorWalls = interiorWalls->next;
    }
    wrefresh(win);
}

void LivingEntity::moveLeft(bool openedDoor, bool levelGreaterThanOne, Wall* interiorWalls){
    mvwaddch(win, posY, posX, ' ');
    posX--;
    if(posX < 1) posX = 1;
    else if(posY == 0 && openedDoor && posX < ((getmaxx(win)-2)/2)-2) posX++;
    else if(posY == getmaxy(win)-1 && levelGreaterThanOne && posX < ((getmaxx(win)-2)/2)-2) posX++;
    while(interiorWalls != NULL){
        if(posX == interiorWalls->getPosX() && posY == interiorWalls->getPosY()){
            posX++;
            break;
        }
        interiorWalls = interiorWalls->next;
    }
    wrefresh(win);
}

void LivingEntity::moveRight(bool openedDoor, bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls){
    mvwaddch(win, posY, posX, ' ');
    posX++;
    if(posX > (getmaxx(win) - 2) && !secretDoor) posX = getmaxx(win) - 2;
    else if(posX > getmaxx(win)-2 && secretDoor && (posY < ((getmaxy(win)-2)/2)-2 || posY > ((getmaxy(win)-2)/2)+3)) posX--;
    else if(posX > getmaxx(win)-1 && secretDoor && (posY >= ((getmaxy(win)-2)/2)-2 && posY <= ((getmaxy(win)-2)/2)+3)) posX--;
    else if(posY == 0 && openedDoor && posX > ((getmaxx(win)-2)/2)+3) posX--;
    else if(posY == getmaxy(win)-1 && levelGreaterThanOne && posX > ((getmaxx(win)-2)/2)+3) posX--;
    while(interiorWalls != NULL){
        if(posX == interiorWalls->getPosX() && posY == interiorWalls->getPosY()){
            posX--;
            break;
        }
        interiorWalls = interiorWalls->next;
    }
    wrefresh(win);
}

void LivingEntity::createBullet(bulletAxisDirection axisDirection, Wall* interiorWalls, bool player, int levelNumber){
    if(bullets == NULL){
        if(player) bullets = new Bullet('~', posX+axisDirection.offset_x, posY+axisDirection.offset_y, false, win, 8, axisDirection.offset_x, axisDirection.offset_y, NULL);
        else bullets = new Bullet('~', posX+axisDirection.offset_x, posY+axisDirection.offset_y, false, win, ((int)log2(levelNumber)+1)*2, axisDirection.offset_x, axisDirection.offset_y, NULL);
    }else{
        Bullet* tmp = bullets;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        Bullet* tmpForSet = NULL;
        if(player) tmpForSet = new Bullet('~', posX+axisDirection.offset_x, posY+axisDirection.offset_y, false, win, 8, axisDirection.offset_x, axisDirection.offset_y, NULL);
        else {
            //controllo per assegnare un danno diverso ai due tipi di nemici che possono sparare
            if(mapSymbol == 'e') tmpForSet = new Bullet('~', posX + axisDirection.offset_x, posY + axisDirection.offset_y, false, win,
                                   ((int) log2(levelNumber + 1) * 2), axisDirection.offset_x, axisDirection.offset_y,
                                   NULL);
            else tmpForSet = new Bullet('~', posX + axisDirection.offset_x, posY + axisDirection.offset_y, false, win,
                                        ((int) log2(levelNumber + 1) * 2)*2, axisDirection.offset_x, axisDirection.offset_y,
                                        NULL);
        }
        tmp->next = tmpForSet;
    }
    deleteNotValidBullet(interiorWalls);
}

void LivingEntity::updateBulletPosition(Wall* interiorWalls){
    Bullet* tmp = bullets;
    while(tmp != NULL) {
        tmp->clear();
        tmp->updateBulletPosition();
        tmp = tmp->next;
    }
    delete tmp;
    deleteNotValidBullet(interiorWalls);
}

bool LivingEntity::checkBulletOnInteriorWalls(int posXToCheck, int posYToCheck, Wall* interiorWalls){
    while(interiorWalls != NULL){
        if(posXToCheck == interiorWalls->getPosX() && posYToCheck == interiorWalls->getPosY()) return true;
        interiorWalls = interiorWalls->next;
    }
    return false;
}

void LivingEntity::deleteNotValidBullet(Wall* interiorWalls){
    if(bullets != NULL){
        Bullet* tmp = bullets;
        Bullet* prec = NULL;
        while(tmp != NULL){
            if(tmp->getPosX() < 1 || tmp->getPosX() > (getmaxx(win) - 2) || tmp->getPosY() < 1 || tmp->getPosY() > (getmaxy(win) - 2) ||
                    checkBulletOnInteriorWalls(tmp->getPosX(), tmp->getPosY(), interiorWalls)){
                mvwaddch(win, tmp->getPosY()-tmp->getAxisDirection().offset_y, tmp->getPosX()-tmp->getAxisDirection().offset_x, ' ');
                Bullet* old = tmp;
                if(prec == NULL) bullets = bullets->next;
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

void LivingEntity::printEntityBullets(){
    Bullet* tmp = bullets;
    while(tmp != NULL){
        tmp->printBullet();
        tmp = tmp->next;
    }
    delete tmp;
}

void LivingEntity::shootBullet(Wall* interiorWalls, bool player, int levelNumber){
    int bulletDirection = wgetch(win);
    bulletAxisDirection axisDirection;
    switch (bulletDirection) {
        case KEY_UP:
            axisDirection.offset_x = 0;
            axisDirection.offset_y = -1;
            createBullet(axisDirection, interiorWalls, player, levelNumber);
            break;
        case KEY_DOWN:
            axisDirection.offset_x = 0;
            axisDirection.offset_y = 1;
            createBullet(axisDirection, interiorWalls, player, levelNumber);
            break;
        case KEY_LEFT:
            axisDirection.offset_x = -1;
            axisDirection.offset_y = 0;
            createBullet(axisDirection, interiorWalls, player, levelNumber);
            break;
        case KEY_RIGHT:
            axisDirection.offset_x = 1;
            axisDirection.offset_y = 0;
            createBullet(axisDirection, interiorWalls, player, levelNumber);
            break;
        default:
            //Tempo scaduto per dare una direzione e sparare il proiettile
            break;
    }
}

void LivingEntity::modifyLifepoints(int points, bool hit){
    if(hit) lifePoints -= points;
    else lifePoints += points;
    if(lifePoints > 30 && !hit) lifePoints = 30;
}

bool LivingEntity::isValid(){
    if(lifePoints > 0){
        return true;
    }else return false;
}

bool LivingEntity::checkKamikazeOnPlayer(LivingEntity* player, LivingEntity* kamikaze){
    return player->posX == kamikaze->posX && player->posY == kamikaze->posY && player->secret;
}

int LivingEntity::getLifePoints(){
    return lifePoints;
}
