#include <iostream>
#include <curses.h>
#include <ctime>
#include <cstring>
#include <unistd.h>
#include "Entity.hpp"
#include "Player.hpp"
#include "Artifact.hpp"
#include "Power.hpp"
#include "Level.hpp"
#include "GameState.hpp"
#include "constants.hpp"

using namespace std;

int main() {
    //inizializzazione variabili della libreria curses/ncurses
    initializeCurses();

    //inizializzazione WINDOW principale di gioco
    WINDOW* win = newwin(30, 120, 5, 20);
    keypad(win, true);
    wrefresh(win);
    refresh();

    //inizializzazione WINDOW che segna i LifePoints, il livello e lo stato di gioco(solo per test)
    WINDOW* winTest = newwin(5, 30, (getmaxy(stdscr)-mainWinHeight)/4*2, 2);
    wrefresh(winTest);
    refresh();

    //dichiarazione e inizializzazione delle variabili utili all'esecuzione del gioco
    int preUserInput = '0';
    int userInput = '0';
    int menuSelected = 1;
    GameState gs = PAUSE;
    bool afterRestart = true;
    bool secret = false;
    int precLifePoints = 0;
    int precLevelNumber = 0;

    printTitle(win);

    //while utilizzato per il Menù di inizio gioco
    while(true){
        initializeFirstEndMenu(win, menuSelected);
        userInput = wgetch(win);
        manageFirstEndMenu(win, userInput, menuSelected, gs);
        if(gs == IN_GAME){
            resetWindow(win);
            break;
        }else if(gs == QUIT){
            endwin();
            return 0;
        }
    }

    //dichiarazione e inizializzazione Player
    Player* player = new Player('@', 1, mainWinHeight/2, false, win, 30, NULL);

    //dichiarazione e inizializzazione del primo livello
    initializeMainWin(win);
    Level* levels = new Level(1, win);
    levels->initializeLevel();

    while(true){
        //controllo per verificare se bisogna spostarsi nella secretRoom
        if(player->moveToSecret()){
            secret = true;
            player->applyRoomChange();
            resetWindow(win);
            initializeSecretWin(win);
            initializeInfoWin(winTest, player->getLifePoints(), levels->getLevelNumber());
            player->resetPosition(2, mainWinHeight/4);
            levels->printSecretEntities();
        }

        //controllo per verificare se bisogna spostarsi nella stanza principale dalla secretRoom
        if(secret && player->moveToMain()){
            secret = false;
            player->applyRoomChange();
            resetWindow(win);
            initializeMainWin(win);
            initializeInfoWin(winTest, player->getLifePoints(), levels->getLevelNumber());
            player->resetPosition(mainWinWidth-3, mainWinHeight/2);
            levels->printEntities();
        }

        //controllo per regolare il transito tra livelli
        if(player->moveToNextLevel()){
            player->resetPosition(mainWinWidth/2-1, mainWinHeight-4);
            wclear(win);
            levels = levels->moveToNextLevel(levels);
        }else if(player->moveToPrecLevel()){
            player->resetPosition(mainWinWidth/2-1, 4);
            wclear(win);
            levels = levels->moveToPrecLevel(levels);
        }

        //operazioni effettuate quando il gioco è in pausa
        if(gs == PAUSE) {
            userInput = wgetch(win);
            manageInGameMenu(win, userInput, menuSelected, gs);
            if(gs == IN_GAME){
                resetWindow(win);
                if(secret){
                    initializeSecretWin(win);
                    initializeInfoWin(winTest, player->getLifePoints(), levels->getLevelNumber());
                }
                else{
                    initializeMainWin(win);
                    initializeInfoWin(winTest, player->getLifePoints(), levels->getLevelNumber());
                }
            }
        }else if(gs == IN_GAME){//operazioni effettuate quando il gioco è in esecuzione
            //controllo fatto affinché non venga eseguito inutilmente wclear facendo laggare il gioco
            if(precLifePoints != player->getLifePoints() || precLevelNumber != levels->getLevelNumber()){
                initializeInfoWin(winTest, player->getLifePoints(), levels->getLevelNumber());
            }
            precLifePoints = player->getLifePoints();
            precLevelNumber = levels->getLevelNumber();

            if(!secret){
                if(afterRestart){
                    afterRestart = false;
                    player->resetPosition(mainWinWidth/2-1, mainWinHeight-4);
                }
                wattron(win, COLOR_PAIR(playerColor));
                player->print();
                wattroff(win, COLOR_PAIR(playerColor));
                levels->printEntities();

                levels->manageNextLevelAccess();
                levels->managePrecLevelAccess();
                levels->manageSecretRoomAccess();
            }else{
                initializeSecretWin(win);
                levels->printLowerDoor(openedDoor);
                wattron(win, COLOR_PAIR(playerColor));
                player->print();
                wattroff(win, COLOR_PAIR(playerColor));
                levels->printSecretEntities();
            }

            //stampa dei proiettili delle varie LivingEntity
            player->printEntityBullets();
            levels->printEnemiesBullets(secret);

            //gestione input dell'utente con controllo per non far sparare raffiche di proiettili
            preUserInput = userInput;
            userInput = wgetch(win);
            if(preUserInput == ' ' && userInput == ' '){
                userInput = '0';
            }

            //aggiornamento della posizione del Player e della posizione dei suoi proiettili
            if(!secret) {
                player->displayMove(userInput, levels->isAlreadyPassed(), levels->isGreaterThanOne(), levels->isSecretRoomAccessible(), levels->getWalls(), levels->getLevelNumber());
                player->updateBulletPosition(levels->getWalls());
            }else{
                player->displayMove(userInput, levels->isAlreadyPassed(), true, levels->isSecretRoomAccessible(), NULL, levels->getLevelNumber());
                player->updateBulletPosition(NULL);
            }

            //aggiornamento della posizione dei nemici, dei loro proiettili, dei poteri e degli artefatti
            levels->updateEnemiesPosition(player, secret);
            levels->updateEnemiesBullets(secret);

            //funzione che verifica se il Player si muove su Artifacts e Powers ed esegue un check sulle entità, eliminandole se serve
            levels->checkCollisions(player, secret);
            gs = levels->deleteUselessEntities(player);

            //controllo che verifica se il livello attuale è stato passato, collezionando tutti i poteri
            levels->checkPassedLevel();

            if(userInput == 'g'){
                gs = PAUSE;
                resetWindow(winTest);
                resetWindow(win);
                menuSelected = 1;
                initializeInGameMenu(win, menuSelected);
            }

            if(gs == LOSS){
                resetWindow(winTest);
                resetWindow(win);
                menuSelected = 1;
                userInput = -1;
                while(userInput == -1){
                    printGameOver();
                    userInput = getch();
                }
                usleep(2500000);
                move(getmaxy(stdscr)/5*2+1, getmaxx(stdscr)/2-45);
                clrtobot();
                initializeFirstEndMenu(win, menuSelected);
            }
        }else if(gs == LOSS) {
            userInput = wgetch(win);
            manageFirstEndMenu(win, userInput, menuSelected, gs);
            if(gs == IN_GAME) {
                gs = RESTART;
            }
        }else if(gs == RESTART){//
            restartGame(levels, player, win);
            resetWindow(win);
            initializeMainWin(win);
            initializeInfoWin(winTest, player->getLifePoints(), levels->getLevelNumber());
            levels->initializeLevel();
            afterRestart = true;
            secret = false;
            gs = IN_GAME;
        }else break; //caso in cui GameState == QUIT
    }

    delete player;
    delete levels;
    delwin(win);
    delwin(winTest);

    endwin();

    return 0;
}