#ifndef TEMPLATE_MAPPE_CONSTANTS_H
#define TEMPLATE_MAPPE_CONSTANTS_H

#include <curses.h>
#include "Level.hpp"
#include "Wall.hpp"
#include "LivingEntity.hpp"
#include "GameState.hpp"
#include "Player.hpp"

static int mainWinHeight = 30;
static int mainWinWidth = 90;

static int firstEndMenuWinHeight = 7;
static int firstEndMenuWinWidth = 40;
static int inGameMenuHeight = 9;
static int inGameMenuWidth = 40;

static char closedDoor[] = "nxtlvl";
static char openedDoor[] = "      ";
static char secretDoor[] = "secret";

static int playerColor = 1;
static int enemyColor = 2;
static int artifactColor = 3;
static int powerColor = 4;


/*
 * Metodo per inizializzare le variabili di ncurses
 */
void initializeCurses();

/*
 * Metodo che inizializza i colori utilizzati per la grafica del gioco
 */
void initializeColors();

/*
 * Metodo che stampa il menù di pausa
 */
void initializeInGameMenu(WINDOW* win, int menuSelected, bool secret);

/*
 * Metodo che gestisce la selezione delle scelte all'interno del menù di pausa
 */
void manageInGameMenu(WINDOW* win, int userInput, int &menuSelected, GameState &gs);

/*
 * Metodo che stampa il menù di inizio o fine gioco
 */
void initializeFirstEndMenu(WINDOW* win, int menuSelected, bool secret);

/*
 * Metodo che gestisce la selezione del menù di inizio o fine gioco
 */
void manageFirstEndMenu(WINDOW* win, int userInput, int &menuSelected, GameState &gs);

/*
 * Metodo che interrompe la visualizzazione della WINDOW con le info sul livello e i lifepoints del player
 */
void clearSecretWinUserInfo();

/*
 * Metodo che stampa la WINDOW adibita alla stanza principale del livello
 */
void initializeMainWin(WINDOW* win, int levelNumber);

/*
 * Metodo che interrompe la visualizzazione della stanza principale del livello
 */
void clearMainWinUserInfo();

/*
 * Metodo che stampa la WINDOW della stanza segreta
 */
void initializeSecretWin(WINDOW* win);

/*
 * Metodo che stampa le informazioni relative al livello e ai lifepoints del player
 */
void initializeInfoWin(WINDOW* winTest, int lifePoints, int levelNumber);

/*
 * Metodo utilizzato per eseguire i vari assegnamenti utili ad iniziare una nuova partita
 */
void restartGame(Level* &levels, Player* player, WINDOW* win);

/*
 * Metodo che serve per "pulire" una WINDOW
 */
void resetWindow(WINDOW* win);

/*
 * Metodo che stampa il titolo del gioco
 */
void printTitle(WINDOW* win);

/*
 * Metodo che stampa la scritta di Game Over
 */
void printGameOver();

/*
 * Metodo che serve per stampare la porta superiore utilizzata per passare al livello successivo
 */
void printHigherDoor(WINDOW * win, char doorString[]);

/*
 * Metodo che serve per stampare la porta inferiore utilizzata per passare al livello precedente, se possibile
 */
void printLowerDoor(WINDOW* win, char doorString[]);

/*
 * Metodo che serve per stampare la porta laterale utilizzata per passare alla SecretRoom
 */
void printSecretDoor(WINDOW * win, char doorString[]);

/*
 * Metodo che serve a creare il primo template di muri interni
 */
Wall* template1(WINDOW* win);

/*
 * Metodo che serve a stampare il primo template di muri interni
 */
void printTemplate1(Wall* tmp1, WINDOW* win);

//TODO: commentare

Wall* template2(WINDOW* win);

void printTemplate2(Wall* tmp1, WINDOW* win);

Wall* template3(WINDOW* win);

void printTemplate3(Wall* tmp1, WINDOW* win);

Wall* template4(WINDOW* win);

void printTemplate4(Wall* tmp1, WINDOW* win);

#endif //TEMPLATE_MAPPE_CONSTANTS_H
