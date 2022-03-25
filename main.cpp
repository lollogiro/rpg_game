//
// Created by rafid on 22/03/2022.
//

#include <curses.h>
#include "Enemy.h"
struct Player{
    char playersymbol;
    WINDOW* win;
    int posy;
    int posx;
};
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

    Player test = { '@',win,15,30 };


    mvwaddch(test.win, test.posy, test.posx, test.playersymbol);

    int userInput = 'a';

    while(userInput != 'q'){

    userInput = wgetch(win);

    }

    endwin();
}