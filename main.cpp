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

    Level* levels = new Level(1);

    Player* player = new Player('@', win);

    //TODO: create a Level class, in the main create a List of Level
    //TODO: Level attributes: prec, next, list of powers, list of artifacts, list of enemies, already entered flag, total numbers of powers so with 3/4 the secret door can be open

    int userInput = 'a';

    while(userInput != 'q'){
        if(levels->alreadyPassed){
            //TODO: funzione nella classe Level che deve stampare degli spazi dove c'è la porta
        }else{
            //TODO: checkare nella classe Level se non sono gia stampate delle X
            //TODO: in caso funzione nella classe Level che deve stampare delle X dove c'è la porta
        }

        player->printPlayer();
        player->printPlayerBullet();
        userInput = wgetch(win);

        //TODO: check if any bullet touched other entities
        //TODO: if the upper method is true update entities' lifepoints

        //TODO: check if the door is open and the player is going out there
        //TODO: if the upper method is true, move to the next or prev level

        //TODO: passare al displayPlayerMove anche le posizioni dei nemici, affinché se in quelle coordinate c'è un nemico, il player non si muove

        //TODO: checkare se il player è sopra un artefatto o un potere, in caso fare opportune considerazioni

        player->displayPlayerMove(userInput);
        player->updateBulletPosition();
    }

    endwin();
}
