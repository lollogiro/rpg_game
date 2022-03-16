//
// Created by lollo on 05/03/2022.
//

#include <curses.h>
#include "Player.h"

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

    Player* player = new Player('@', win);

    //player->printPlayer();

    int userInput = 'a';

    while(userInput != 'q'){
        player->printPlayer();
        player->printPlayerBullet();
        userInput = wgetch(win);


        //TODO: check if the bullet touched other entities
        //TODO: if the upper method is true update entities' lifepoints

        //TODO: check if the door is open and the player is going out there
        //TODO: if the upper method is true, move to the next or prev level

        player->displayPlayerMove(userInput);
        player->updateBulletPosition();
        //player->deleteNotValidBullet();


    }

    endwin();
}
