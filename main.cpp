//
// Created by lollo on 05/03/2022.
//

#include <curses.h>

int main(int argc, char** argv){
    initscr();
    //noecho();
    //raw();
    halfdelay(0.5);
    curs_set(0);
    char userInput;
    do{
        userInput = getch();


    }while(userInput != 'q');
    endwin();
}
