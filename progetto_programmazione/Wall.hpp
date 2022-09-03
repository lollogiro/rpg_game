#ifndef TEMPLATE_MAPPE_WALL_H
#define TEMPLATE_MAPPE_WALL_H

#include "Entity.hpp"

#pragma once

class Wall : public Entity{
public:
    Wall* next;

public:
    /*
     * Costruttore della classe Wall
     */
    Wall(char mapSymbol, int posX, int posY, bool secret, WINDOW* win);

    /*
     * Metodo utilizzato per stampare il muro sulla mappa tramite la funzione NCURSES_ACS di ncurses
     */
    void print();

    /*
     * Metodo utilizzato per stampare la porta chiusa interna alla stanza principale
     */
    void printDoor();

    /*
     * Metodo utilizzato per stampare la porta aperta interna alla stanza principale
     */
    void printOpenDoor();

    /*
     * Metodo utilizzato per l'inserimento in lista dei muri interni
     */
    Wall* listInsert(Wall* walls, Wall* toIns);

    /*
     * Metodo di tipo getter
     */

    char getMapSymbol();
};


#endif //TEMPLATE_MAPPE_WALL_H
