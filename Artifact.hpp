//
// Created by lollo on 29/04/2022.
//

#ifndef PROGETTO_PROGRAMMAZIONE_ARTIFACT_HPP
#define PROGETTO_PROGRAMMAZIONE_ARTIFACT_HPP

#include "Entity.hpp"
#include "Wall.hpp"

#pragma once

class Artifact : public Entity{
protected:
    int givenLifePoints;
public:
    Artifact* next;

    //TODO: unire Artifact e Power in un'unica entità StaticEntity, la differenza rispetto alle attuali sarà che al metodo
    // check verrà aggiunta una lista StaticEntity e nel creare Power verrà settato givenLifepoints = 0.

public:
    /*
     * Costruttore della classe Artifact
     */
    Artifact(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int givenLifePoints, Artifact *next);

    /*
     * Metodo che, passate delle coordinate, verifica se in quelle coordinate è possibile creare un artefatto
     */
    bool checkArtifactPosition(int posX, int posY, Wall* interiorWalls, Artifact* artifacts);

    /*
     * Metodo di tipo get che restituisce il valore dell'attributo givenLifePoints
     */
    int getGivenLifePoints();
};



#endif //PROGETTO_PROGRAMMAZIONE_ARTIFACT_HPP
