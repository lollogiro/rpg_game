#include <iostream>
#include <curses.h>
#include <ctime>
#include <cstring>
#include "Entity.h"
#include "LivingEntity.h"
#include "Artifact.h"
#include "Power.h"
#include "Level.h"
#include "constants.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    halfdelay(2);//0.2 sec
    curs_set(0);
    srand(time(NULL));

    WINDOW* win = newwin(30, 120, 5, 20);

    keypad(win, true);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    refresh();

    /*
    WINDOW* secretWin = newwin(20,60,5,20);
    keypad(secretWin, true);
    refresh();
    box(secretWin, 0, 0);
    wrefresh(secretWin);
    wborder(secretWin, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();
     */


    WINDOW* winTest = newwin(5, 30, 0, 0);
    box(winTest, 0, 0);
    wrefresh(winTest);
    refresh();

    Level* levels = new Level(1, win);

    char closedDoor[] = "closed";
    char openedDoor[] = "      ";
    char secretDoor[] = "secret";

    LivingEntity* player = new LivingEntity('@', 1, getmaxy(win)-2, win, 30, NULL);

    int preUserInput = '0';
    int userInput = '0';
    bool gameState = true;

    levels->initializeLevel();
    levels->printEntities();

    while(userInput != 'q' && gameState){

        if(player->posX == getmaxx(win)-1){
            //togliere la win principale e stampare la secretWin, vedere se lasciarla stampata sempre e aprire solo la porta
        }

        if(player->posY == 0){
            player->posX = 1;
            player->posY = getmaxy(win)-2;
            levels->clearWindowFromEntities(player);
            if(levels->nextLevel == NULL){
                Level* tmp = new Level(levels->levelNumber+1, win);
                levels->nextLevel = tmp;
                tmp->precLevel = levels;
                levels = levels->nextLevel;
                levels->initializeLevel();
                levels->printEntities();
            }else{
                levels = levels->nextLevel;
                levels->printEntities();
            }
        }else if(player->posY == getmaxy(win)-1){
            player->posX = 1;
            player->posY = getmaxy(win)-2;
            levels->clearWindowFromEntities(player);
            levels = levels->precLevel;
            levels->printEntities();
            if(levels->precLevel == NULL) box(levels->win, 0, 0);
        }

        mvwprintw(winTest, 1, 1, "Lifepoints: %d",player->lifePoints);
        mvwprintw(winTest, 2, 1, "Level: %d",levels->levelNumber);
        mvwprintw(winTest, 3, 1, "Game state: %d",gameState);
        wrefresh(winTest);

        if(levels->levelNumber > 1) levels->printLowerDoor(openedDoor);

        if(levels->alreadyPassed) levels->printHigherDoor(openedDoor);
        else levels->printHigherDoor(closedDoor);

        if(levels->enemies == NULL) levels->printSecretDoor(openedDoor);
        else levels->printSecretDoor(secretDoor);

        levels->checkCollisions(player);
        gameState = levels->deleteUselessEntities(player);

        player->printEntity();//forse inutile
        player->printEntityBullets();

        levels->printEnemiesBullets();

        preUserInput = userInput;
        userInput = wgetch(win);
        if(preUserInput == ' ' && userInput == ' '){
            userInput = '0';
        }

        //PLAYER UPDATES
        player->displayMove(userInput, levels->alreadyPassed, (levels->levelNumber > 1), (levels->enemies == NULL), levels->walls);
        player->updateBulletPosition(levels->walls);

        //ENEMIES UPDATES
        levels->updateEnemiesBullets();
        levels->updateEnemiesPosition(player);
        levels->printEntities();

        if(levels->powers == NULL) levels->alreadyPassed = true;
    }

    delete player;
    delete levels;

    endwin();

    return 0;
}