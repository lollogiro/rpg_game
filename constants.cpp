//
// Created by lollo on 13/07/2022.
//

#include <iostream>
#include "constants.hpp"

void initializeCurses(){
    setlocale(LC_ALL, "");
    initscr();
    noecho();
    raw();
    halfdelay(2);//0.2 sec
    curs_set(0);
    srand(time(NULL));
    initializeColors();
}

void initializeColors(){
    start_color();
    //player color
    init_pair(1, COLOR_CYAN, COLOR_BLACK);
    //enemy color
    init_pair(2, COLOR_RED, COLOR_BLACK);
    //artifact color
    init_pair(3, COLOR_YELLOW, COLOR_BLACK);
    //power color
    init_pair(4, COLOR_GREEN, COLOR_BLACK);

}
void initializeInGameMenu(WINDOW* win, int menuSelected){
    wresize(win, inGameMenuHeight, inGameMenuWidth);
    mvwin(win, (getmaxy(stdscr)-inGameMenuHeight)/3, (getmaxx(stdscr)-inGameMenuWidth)/2);
    box(win, 0, 0);
    mvwprintw(win, 2, 4, "Continua a giocare");
    mvwprintw(win, 4, 4, "Nuova partita");
    mvwprintw(win, 6, 4, "Esci");
    mvwaddch(win, menuSelected*2, 2, '>');
    wrefresh(win);
    refresh();
}

void manageInGameMenu(WINDOW* win, int userInput, int &menuSelected, GameState &gs){
    switch(userInput){
        case KEY_UP:
            mvwaddch(win, (menuSelected)*2, 2, ' ');
            menuSelected--;
            if(menuSelected == 0) menuSelected = 3;
            mvwaddch(win, (menuSelected)*2, 2, '>');
            break;
        case KEY_DOWN:
            mvwaddch(win, (menuSelected)*2, 2, ' ');
            menuSelected++;
            if(menuSelected == 4) menuSelected = 1;
            mvwaddch(win, (menuSelected)*2, 2, '>');
            break;
        case ' ':
            switch(menuSelected){
                case 1:
                    gs = IN_GAME;
                    wclear(win);
                    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                    wrefresh(win);//INDISPENSABILE!!!
                    refresh();
                    break;
                case 2:
                    gs = RESTART;
                    wclear(win);
                    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
                    wrefresh(win);//INDISPENSABILE!!!
                    refresh();
                    menuSelected = 1;
                    break;
                case 3:
                    gs = QUIT;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void initializeFirstEndMenu(WINDOW* win, int menuSelected){
    wresize(win, firstEndMenuWinHeight, firstEndMenuWinWidth);
    mvwin(win, (getmaxy(stdscr)-firstEndMenuWinHeight)/3, (getmaxx(stdscr)-firstEndMenuWinWidth)/2);
    box(win, 0, 0);
    mvwprintw(win, 2, 4, "Nuova partita");
    mvwprintw(win, 4, 4, "Esci");
    mvwaddch(win, menuSelected*2, 2, '>');
    box(win, 0, 0);
    wrefresh(win);
    refresh();
}

void manageFirstEndMenu(WINDOW* win, int userInput, int &menuSelected, GameState &gs){
    switch(userInput){
        case KEY_UP:
            mvwaddch(win, (menuSelected)*2, 2, ' ');
            menuSelected--;
            if(menuSelected == 0) menuSelected = 2;
            mvwaddch(win, (menuSelected)*2, 2, '>');
            break;
        case KEY_DOWN:
            mvwaddch(win, (menuSelected)*2, 2, ' ');
            menuSelected++;
            if(menuSelected == 3) menuSelected = 1;
            mvwaddch(win, (menuSelected)*2, 2, '>');
            break;
        case ' ':
            switch(menuSelected) {
                case 1:
                    gs = IN_GAME;
//                    wclear(win);
//                    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
//                    wrefresh(win);
//                    refresh();
                    break;
                case 2:
                    gs = QUIT;
                    break;
                default:
                    break;
            }
            break;
        default:
            break;
    }
}

void initializeMainWin(WINDOW* win){
    wresize(win, mainWinHeight, mainWinWidth);
    mvwin(win, (getmaxy(stdscr)-mainWinHeight)/4*2, (getmaxx(stdscr)-mainWinWidth)/2);
    box(win, 0, 0);
}

void initializeSecretWin(WINDOW* win){
    wresize(win, mainWinHeight/2, mainWinWidth/2);
    mvwin(win, (getmaxy(stdscr)-mainWinHeight/2)/4*2, (getmaxx(stdscr)-mainWinWidth/2)/2);
    box(win, 0, 0);
}

void initializeInfoWin(WINDOW* winTest, int lifePoints, int levelNumber){
    wresize(winTest, 7, 30);
    wclear(winTest);
    box(winTest, 0, 0);
    mvwprintw(winTest, 2, 1, "LifePoints: %d",lifePoints);
    mvwprintw(winTest, 4, 1, "Level Number: %d",levelNumber);
    wrefresh(winTest);
    refresh();
}

void restartGame(Level* levels, Player* player, WINDOW* win){
    delete levels;
    levels = new Level(1, win);
    player->restartPlayer();
}

void resetWindow(WINDOW* win){
    wclear(win);
    wborder(win, ' ', ' ', ' ', ' ', ' ', ' ', ' ', ' ');
    wrefresh(win);
    refresh();
}

void printTitle(WINDOW* win){
    const char* t1 = "______ ______  _____   _____   ___  ___  ___ _____\n";
    const char* t2 = "| ___ \\| ___ \\|  __ \\ |  __ \\ / _ \\ |  \\/  ||  ___|\n";
    const char* t3 = "| |_/ /| |_/ /| |  \\/ | |  \\// /_\\ \\| .  . || |__\n";
    const char* t4 = "|    / |  __/ | | __  | | __ |  _  || |\\/| ||  __|\n";
    const char* t5 = "| |\\ \\ | |    | |_\\ \\ | |_\\ \\| | | || |  | || |___\n";
    const char* t6 = "\\_| \\_|\\_|     \\____/  \\____/\\_| |_/\\_|  |_/\\____/\n";
    mvaddstr(1, getmaxx(stdscr)/2-26, t1);
    mvaddstr(2, getmaxx(stdscr)/2-26, t2);
    mvaddstr(3, getmaxx(stdscr)/2-26, t3);
    mvaddstr(4, getmaxx(stdscr)/2-26, t4);
    mvaddstr(5, getmaxx(stdscr)/2-26, t5);
    mvaddstr(6, getmaxx(stdscr)/2-26, t6);
}

void printGameOver(){
    const char* t1 = " _______    ________   ___ __ __   ______       ______   __   __   ______   ______\n";
    const char* t2 = "/______/\\  /_______/\\ /__//_//_/\\ /_____/\\     /_____/\\ /_/\\ /_/\\ /_____/\\ /_____/\\\n";
    const char* t3 = "\\::::__\\/__\\::: _  \\ \\\\::\\| \\| \\ \\\\::::_\\/_    \\:::_ \\ \\\\:\\ \\\\ \\ \\\\::::_\\/_\\:::_ \\ \\\n";
    const char* t4 = " \\:\\ /____/\\\\::(_)  \\ \\\\:.      \\ \\\\:\\/___/\\    \\:\\ \\ \\ \\\\:\\ \\\\ \\ \\\\:\\/___/\\\\:(_) ) )_\n";
    const char* t5 = "  \\:\\\\_  _\\/ \\:: __  \\ \\\\:.\\-/\\  \\ \\\\::___\\/_    \\:\\ \\ \\ \\\\:\\_/.:\\ \\\\::___\\/_\\: __ `\\ \\\n";
    const char* t6 = "   \\:\\_\\ \\ \\  \\:.\\ \\  \\ \\\\. \\  \\  \\ \\\\:\\____/\\    \\:\\_\\ \\ \\\\ ..::/ / \\:\\____/\\\\ \\ `\\ \\ \\\n";
    const char* t7 = "    \\_____\\/   \\__\\/\\__\\/ \\__\\/ \\__\\/ \\_____\\/     \\_____\\/ \\___/_(   \\_____\\/ \\_\\/ \\_\\/\n";

    mvaddstr(getmaxy(stdscr)/5*2+1, getmaxx(stdscr)/2-45, t1);
    mvaddstr(getmaxy(stdscr)/5*2+2, getmaxx(stdscr)/2-45, t2);
    mvaddstr(getmaxy(stdscr)/5*2+3, getmaxx(stdscr)/2-45, t3);
    mvaddstr(getmaxy(stdscr)/5*2+4, getmaxx(stdscr)/2-45, t4);
    mvaddstr(getmaxy(stdscr)/5*2+5, getmaxx(stdscr)/2-45, t5);
    mvaddstr(getmaxy(stdscr)/5*2+6, getmaxx(stdscr)/2-45, t6);
    mvaddstr(getmaxy(stdscr)/5*2+7, getmaxx(stdscr)/2-45, t7);
    mvaddstr(getmaxy(stdscr)/5*2+10, getmaxx(stdscr)/2-45, "\t\t\t\tPremere un tasto per continuare");

}


Wall* template1(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, false, win);
    for (int i = 1; i <= 5; ++i) {
        tmp = new Wall('q', i, 5, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
        tmp = new Wall('q', getmaxx(win)-1-i, 25, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
    }
    for (int i = 1; i <= 3; ++i) {
        tmp = new Wall('q', i, 20, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
        tmp = new Wall('q', getmaxx(win)-1-i, 10, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
    }
    //MURI VERTICALI
    tmp = new Wall('x', 0, 0, false, win);

    for (int i = 1; i <= 10; ++i){
        tmp = new Wall('x', 26, i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
        tmp = new Wall('x', 86, getmaxy(win)-1-i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
    }
    for (int i = 1; i <= 6; ++i){
        tmp = new Wall('x', 94, i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
        tmp = new Wall('x', 32, getmaxy(win)-1-i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
    }
    return interiorWalls;
}

void printTemplate1(Wall* tmp, WINDOW* win){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(win, 5, 0, ACS_LTEE);
        mvwaddch(win, 25 , getmaxx(win)-1, ACS_RTEE);
        mvwaddch(win, 20, 0, ACS_LTEE);
        mvwaddch(win, 10 , getmaxx(win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(win, 0, 26, ACS_TTEE);
        mvwaddch(win, getmaxy(win)-1, 86, ACS_BTEE);
        mvwaddch(win, 0, 94, ACS_TTEE);
        mvwaddch(win, getmaxy(win)-1, 32, ACS_BTEE);

        while(tmp != NULL){
            tmp->print();
            tmp = tmp->next;
        }
    }
}



Wall* template2(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, false, win);
    for (int i = 1; i <= 14; ++i) {
        tmp = new Wall('q', i, 9, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
        tmp = new Wall('q', getmaxx(win) - 1 - i, 25, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
    }
    for (int i = 1; i <= 7; ++i) {
            tmp = new Wall('q', i, 39, false, win);
            interiorWalls = tmp->listInsert(interiorWalls, tmp);
            tmp = new Wall('q', getmaxx(win)-1-i, 80, false, win);
            interiorWalls = tmp->listInsert(interiorWalls, tmp);

    }

    //MURI VERTICALI
    tmp = new Wall('x', 0, 0, false, win);

    for (int i = 1; i <= 9; ++i){
        tmp = new Wall('x', 24, i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
        tmp = new Wall('x', 67, getmaxy(win)-1-i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
    }

    return interiorWalls;
}

void printTemplate2(Wall* tmp, WINDOW* win){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(win, 9, 0, ACS_LTEE);
        mvwaddch(win, 30, getmaxx(win)-1, ACS_RTEE);
        mvwaddch(win, 80, 0, ACS_LTEE);
        mvwaddch(win, 30, getmaxx(win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(win, 0, 24, ACS_TTEE);
        mvwaddch(win, getmaxy(win)-1, 67, ACS_BTEE);

        while(tmp != NULL){
            tmp->print();
            tmp = tmp->next;
        }
    }
}

Wall* template3(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, false, win);
    for (int i = 1; i <= 3; ++i) {
        tmp = new Wall('q', i, 9, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
        tmp = new Wall('q', getmaxx(win)-1-i, 40, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
    }

    //MURI VERTICALI
    tmp = new Wall('x', 0, 0, false, win);

    for (int i = 1; i <= 6; ++i){
        tmp = new Wall('x', 29, i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
        tmp = new Wall('x', 71, getmaxy(win)-1-i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
    }

    return interiorWalls;
}

void printTemplate3(Wall* tmp, WINDOW* win){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(win, 9, 0, ACS_LTEE);
        mvwaddch(win, 40, getmaxx(win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(win, 0, 29, ACS_TTEE);
        mvwaddch(win, getmaxy(win)-1, 71, ACS_BTEE);

        while(tmp != NULL){
            tmp->print();
            tmp = tmp->next;
        }
    }
}

Wall* template4(WINDOW* win){
    Wall* interiorWalls = NULL;
    //MURI ORIZZONTALI
    Wall* tmp = new Wall('q', 0, 0, false, win);
    for (int i = 1; i <= 4; ++i) {
        tmp = new Wall('q', i, 7, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
        tmp = new Wall('q', getmaxx(win)-1-i, 19, false, win);
        interiorWalls = tmp->listInsert(interiorWalls, tmp);
    }

    //MURI VERTICALI
    tmp = new Wall('x', 0, 0, false, win);

    for (int i = 1; i <= 11; ++i){
        tmp = new Wall('x', 32, i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
        tmp = new Wall('x', 68, getmaxy(win)-1-i, false, win);
        interiorWalls->listInsert(interiorWalls, tmp);
    }

    return interiorWalls;
}

void printTemplate4(Wall* tmp, WINDOW* win){
    if(tmp != NULL){
        //MURI ORIZZONTALI x BORDI
        mvwaddch(win, 7, 0, ACS_LTEE);
        mvwaddch(win, 19, getmaxx(win)-1, ACS_RTEE);
        //MURI VERTICALI x BORDI
        mvwaddch(win, 0, 32, ACS_TTEE);
        mvwaddch(win, getmaxy(win)-1, 68, ACS_BTEE);

        while(tmp != NULL){
            tmp->print();
            tmp = tmp->next;
        }
    }
}
