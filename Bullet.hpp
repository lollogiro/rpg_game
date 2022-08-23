#ifndef PROGETTO_PROGRAMMAZIONE_BULLET_HPP
#define PROGETTO_PROGRAMMAZIONE_BULLET_HPP

#include "Entity.hpp"

#pragma once

/*
 * Struct utilizzato per definire gli offset di un Bullet che determinano la sua direzione
 */
struct bulletAxisDirection{
    int offset_x;
    int offset_y;
};

class Bullet : public Entity{
protected:
    int damage;
    bulletAxisDirection axisDirection;
public:
    Bullet* next;

public:
    /*
     * Costruttore della classe Bullet
     */
    Bullet(char charSymbol, int posX, int posY, bool secret, WINDOW* win, int damage, int offset_x, int offset_y, Bullet* next);

    /*
     * Metodo che serve a stampare il Bullet, il quale sfrutta il metodo di ncurses NCURSES_ACS
     */
    void printBullet();

    /*
     * Metodo utilizzato per aggiornare la posizione del Bullet, questo sfrutta l'offset definito
     * nell'attributo axisDirection
     */
    void updateBulletPosition();

    /*
     * Metodo che modifica l'attributo posX ereditato dalla classe Entity, assegnandoli un valore
     * che poi servirà a soddisfare la condizione per eliminare il Bullet
     */
    void invalidBullet();

    /*
     * Metodo di tipo get utilizzato per ritornare l'attributo Damage che descrive i lifePoints
     * tolti dal Bullet
     */
    int getDamage();

    /*
     * Metodo di tipo get utilizzato per ritornare l'attributo axisDirection
     */
    const bulletAxisDirection &getAxisDirection();
};

#endif //PROGETTO_PROGRAMMAZIONE_BULLET_HPP
