//
// Created by lollo on 13/07/2022.
//

#ifndef TEMPLATE_MAPPE_CONSTANTS_H
#define TEMPLATE_MAPPE_CONSTANTS_H

#include <curses.h>
#include "Level.hpp"
#include "Wall.hpp"
#include "LivingEntity.hpp"
#include "GameState.hpp"
#include "Player.hpp"

static int mainWinHeight = 30;
static int mainWinWidth = 120;

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

void initializeCurses();

void initializeColors();

void initializeInGameMenu(WINDOW* win, int menuSelected);

void manageInGameMenu(WINDOW* win, int userInput, int &menuSelected, GameState &gs);

void initializeFirstEndMenu(WINDOW* win, int menuSelected);

void manageFirstEndMenu(WINDOW* win, int userInput, int &menuSelected, GameState &gs);

void initializeMainWin(WINDOW* win);

void initializeSecretWin(WINDOW* win);

void initializeInfoWin(WINDOW* winTest, int lifePoints, int levelNumber);

void restartGame(Level* levels, Player* player, WINDOW* win);

void resetWindow(WINDOW* win);

void printTitle(WINDOW* win);

void printGameOver();

Wall* template1(WINDOW* win);

void printTemplate1(Wall* tmp1, WINDOW* win);

#endif //TEMPLATE_MAPPE_CONSTANTS_H
