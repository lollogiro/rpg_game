//
// Created by lollo on 05/03/2022.
//

#include <curses.h>

#include "Player.cpp"

int main(int argc, char** argv){
    initscr();
    //noecho();
    raw();
    halfdelay(2);//0.2 sec
    curs_set(0);

    WINDOW* win = newwin(30, 60, 5, 10);
    refresh();
    box(win, 0, 0);
    wrefresh(win);
    wborder(win, '|', '|', '-', '-', '+', '+', '+', '+');
    refresh();

    Player player = Player('@', win);
    player.printEntity();

    char userInput = 'a'; //random assignation
    while(userInput != 'q'){
        userInput = getch();
        refresh();
    }

    endwin();
}
