#include <curses.h>
#include "Player.h"
#include "Level.h"

using namespace std;

int main(int argc, char** argv){
    initscr();
    noecho();
    raw();
    halfdelay(2);//0.5 sec
    curs_set(0);

    WINDOW* win = newwin(30, 60, 5, 10);
    keypad(win, true);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();

    Level* levels = new Level(2, win);
    char* closedDoor = "closed";
    char* openedDoor = "      ";


    Player* player = new Player('@', win);

    //TODO: create a Level class, in the main create a List of Level
    //TODO: Level attributes: prec, next, list of powers, list of artifacts, list of enemies, already entered flag, total numbers of powers so with 3/4 the secret door can be open

    int userInput = 'a';

    while(userInput != 'q'){
        if(levels->alreadyPassed){
            levels->printHigherDoor(openedDoor);
        }else{
            levels->printHigherDoor(closedDoor);
        }
        if(levels->levelNumber > 1){
            levels->printLowerDoor(openedDoor);
        }
        if(player->getPosY() == 0){
            //TODO: muoversi al livello successivo, creandolo se non ancora inizializzato
        }
        else if(player->getPosY() == getmaxy(win)-1){
            //TODO: muoversi al livello precedente
        }

        player->printPlayer();
        player->printPlayerBullet();
        userInput = wgetch(win);

        //TODO: checkare collisioni con altre entità
        //TODO: in caso modificare lifepoints delle varie entità

        //TODO: passare al displayPlayerMove anche le posizioni dei nemici, affinché se in quelle coordinate c'è un nemico, il player non si muove

        //TODO: checkare se il player è sopra un artefatto o un potere, in caso fare opportune considerazioni

        //TODO: passare anche un parametro che segnala se il livello è stato passato, affinché il player possa muoversi anche nello spazio vuoto

        //TODO: modificare spostamenti se il livello è > 1
        player->displayPlayerMove(userInput, levels->alreadyPassed, (levels->levelNumber > 1));
        player->updateBulletPosition();
    }

    endwin();
}
