#include <curses.h>
#include "Player.h"
#include "Level.h"
#includa "Artifact.h"
#include "Power.h"

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

    //player: x=1, y=getmaxy(win)-2

    //TODO: create a Level class, in the main create a List of Level
    //TODO: Level attributes: prec, next, list of powers, list of artifacts, list of enemies, already entered flag, total numbers of powers so with 3/4 the secret door can be open

    int userInput = 'a';

    Artifact* a = NULL;
    Power* p= NULL;
    for (int i = 0; i < 2; ++i) {
        a=a->initializeArtifact(a);
        a->printArtifact()

    }
    for (int i = 0; i < 2; ++i) {
       p=p->initializePower(a,p) ;
       p->printPower()
    }



    while(userInput != 'q'){

        userInput = wgetch(win);

    }

    endwin();
}