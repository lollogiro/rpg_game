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

    /*
     * Metodo per verificare se è necessario spostare il player nella stanza segreta
     */
    bool moveToSecret();

    /*
     * Metodo per verificare se è necessario spostare il player nella stanza principale
     */
    bool moveToMain();

    /*
     * Metodo utilizzato per aggiorare il parametro secret del player in caso di cambio di stanza
     */
    void applyRoomChange();

    /*
     * Metodo per verificare se è necessario spostare il player nel livello successivo
     */
    bool moveToNextLevel();

    /*
     * Metodo per verificare se è necessario spostare il player nel livello precedente
     */
    bool moveToPrecLevel();

    /*
     * Metodo utilizzato per "resettare" il player in caso di una nuova partita
     */
    void restartPlayer();

    /*
     * Metodo utilizzato per modificare la posizione del player
     */
    void resetPosition(int posX, int posY);
};


#endif //PROGETTO_PROGRAMMAZIONE_PLAYER_HPP
