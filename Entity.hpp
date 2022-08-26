//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ENTITY_HPP
#define PROGETTO_PROGRAMMAZIONE_ENTITY_HPP

#include <curses.h>

#pragma once

class Entity{
protected:
    char mapSymbol;
    int posX;
    int posY;
    bool secret;
    WINDOW* win;

public:
    /*
     * Costruttore della classe Entity
     */
    Entity(char mapSymbol, int posX, int posY, bool secret, WINDOW *win);

    /*
     * Metodo che si occupa di stampare l'Entity sulla mappa
     */
    void print();

    /*
     * Metodo che serve a "pulire" la mappa dal simbolo dell'Entity stampato precedentemente
     */
    void clear();

    /*
     * Metodo di tipo booleano utilizzato per determinare se stampare le Entity appartenenti alla SecretRoom
     * oppure alla stanza principale
     */
    bool checkSecret(bool secret);

    /*
     * Metodo di tipo get che restituisce il valore dell'attributo posX
     */
    int getPosX();

    /*
     * Metodo di tipo get che restituisce il valore dell'attributo posY
     */
    int getPosY();
};

#endif //PROGETTO_PROGRAMMAZIONE_ENTITY_HPP
