#include <iostream>
#include <curses.h>
#include <time.h>
#include "Entity.h"
#include "LivingEntity.h"
#include "Artifact.h"
#include "Power.h"
#include "Level.h"

using namespace std;

int main() {
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
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();

    Artifact* artifacts = NULL;
    Power* powers = NULL;
    Enemy* enemies = NULL;

    Level* levels = new Level(8, artifacts, powers, enemies, win);
    levels->alreadyPassed = true;

    char closedDoor[] = "closed";
    char openedDoor[] = "      ";
    char secretDoor[] = "secret";

    LivingEntity* player = new LivingEntity('@', 1, getmaxy(win)-2, win, 30, NULL);

    int userInput = '0';


    //inizializzazione powers e artifacts del primo livello
    levels->initializeLevel();
    levels->printEntities();

    while(userInput != 'q'){

        if(levels->alreadyPassed) levels->printHigherDoor(openedDoor);
        else levels->printHigherDoor(closedDoor);

        if(levels->levelNumber > 1) levels->printLowerDoor(openedDoor);

        //TODO: sostituire condizione con powers == NULL
        if(levels->levelNumber == 1) levels->printSecretDoor(openedDoor);
        else levels->printSecretDoor(secretDoor);

        if(player->posX == getmaxx(win)-1){
            //TODO: generare la secretRoom, con all'interno i suoi artefatti e UN nemico
        }


        if(player->posY == 0){
            //TODO: muoversi al livello successivo, creandolo se non ancora inizializzato
            /*
            if(levels->nextLevel == NULL){
                Level* tmp = new Level(levels->levelNumber+1, win);
                levels->nextLevel = tmp;
                tmp->precLevel = levels;
                levels = levels->nextLevel;
                delete(tmp);
            }else{
                levels = levels->nextLevel;
            }
            //generare nemici, artefatti e poteri, stamparli tutti per la prima volta
            */
        }
        else if(player->posY == getmaxy(win)-1){
            //TODO: spostarsi al livello precedente, pulendo la window e stampare entità ancora presenti
            //levels = levels->precLevel;
            //TODO: pulire window dal livello da cui stiamo uscendo e stampare entità ancora presenti nel livello in cui stiamo entrando
        }

        //TODO: levels->checkCollisions();
        //TODO: levels->updateEntitiesLifepoints();

        player->printEntity();
        player->printEntityBullets();

        levels->printEnemiesBullets();

        userInput = wgetch(win);

        //TODO: passare al displayPlayerMove anche le posizioni dei nemici, affinché se in quelle coordinate c'è un nemico, il player non si muove
        //TODO: checkare se il player è sopra un artefatto o un potere, in caso aumentare i lifepoints del player

        player->displayMove(userInput, /*levels->alreadyPassed*/ true, /*(levels->levelNumber > 1)*/ false, /*(levels->levelNumber == 1)*/ true);//sostituire secretDoor con levels->enemies == NULL
        player->updateBulletPosition();

        levels->updateEnemiesBullets();
        levels->updateEnemiesPosition(player);
        levels->printEntities();


        //if(enemies != NULL) enemies->displayEnemiesMove
        //enemies->updateEnemiesBulletPosition

        //if powers == NULL && artifacts == NULL -> levels->alreadyPassed = True
    }

    endwin();

    return 0;
}