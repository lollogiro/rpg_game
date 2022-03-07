//
// Created by lollo on 05/03/2022.
//

#include <curses.h>

int main(int argc, char** argv){
    initscr();
    //noecho();
    raw();
    halfdelay(2);//0.2 sec
    curs_set(0);
    char userInput = 'a'; //random assignation

    while(userInput != 'q'){
        userInput = getch();
        refresh();
    }
    endwin();
}
