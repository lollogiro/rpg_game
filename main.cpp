//
// Created by rafid on 22/03/2022.
//

#include <curses.h>
#include "Enemy.h"

int main(int argc, char** argv){
    initscr();
    noecho();
    raw();
    halfdelay(5);//0.5 sec
    curs_set(0);

    srand(time(0));

    WINDOW* win = newwin(30, 60, 5, 10);
    keypad(win, true);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();

    Enemy enemy = enemy.initializeEnemy(win);


    Player test = { '@',win,getmaxy(win)-2,1 };

    enemy.printPlayer();


    mvwaddch(test.win, test.posy, test.posx, test.playersymbol);


    int userInput = 'a';

    while(userInput != 'q'){


        userInput = wgetch(win);
        enemy.MoveChoser();

    }

    endwin();
}