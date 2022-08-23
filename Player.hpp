//
// Created by lollo on 18/08/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_PLAYER_HPP
#define PROGETTO_PROGRAMMAZIONE_PLAYER_HPP

#include "LivingEntity.hpp"

class Player : public LivingEntity{
public:
    Player(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int lifePoints, Bullet *bullets);
    /*
     * Metodo utilizzato per gestire l'input dell'utente o dell'AI e far muovere il Player di conseguenza
     */
    void displayMove(int userInput, bool openedDoor, bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls, int levelNumber);
    bool moveToSecret();
    bool moveToMain();
    void applyRoomChange();
    bool moveToNextLevel();
    bool moveToPrecLevel();
    void restartPlayer();
    void resetPosition(int posX, int posY);
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYER_HPP
