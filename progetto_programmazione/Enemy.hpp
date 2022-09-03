#ifndef PROGETTO_PROGRAMMAZIONE_ENEMY_HPP
#define PROGETTO_PROGRAMMAZIONE_ENEMY_HPP

#include "StaticEntity.hpp"
#include "LivingEntity.hpp"

#pragma once

class Enemy : public LivingEntity{
public:
    Enemy* next;
public:
    /*
     * Costruttore della classe Enemy
     */
    Enemy(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int lifePoints, Bullet *bullets, Enemy* next);

    /*
     * Metodo utilizzato per verificare se è possibile creare un Enemy nelle coordinate passate alla funzione
     */
    bool checkEnemyPosition(int posX, int posY, Wall *interiorWalls, Enemy *enemies, StaticEntity* powers, StaticEntity* artifacts);

    /*
     * Metodo che descrive l'AI del nemico con i criteri per cui debba seguire il Player nei suoi movimenti
     */
    void followPlayer(LivingEntity* Player, Wall* interiorWalls, int levelNumber);

    /*
     * Metodo che determina gli spostamenti dell'Enemy in modo casuale
     */
    void randomMovement(Wall* interiorWalls, int levelNumber);

    /*
     * Metodo che determina se far spostare l'Enemy secondo followPlayer o randomMovement
     */
    void moveChooser(LivingEntity* player, Wall* interiorWalls, int levelNumber);

    /*
     * Metodo di tipo get che restituisce il valore dell'attributo Secret
     */
    bool getSecret();
};


#endif //PROGETTO_PROGRAMMAZIONE_ENEMY_HPP
