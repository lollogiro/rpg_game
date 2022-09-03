#ifndef PROGETTO_PROGRAMMAZIONE_STATICENTITY_HPP
#define PROGETTO_PROGRAMMAZIONE_STATICENTITY_HPP

#include "Entity.hpp"
#include "Wall.hpp"

class StaticEntity : public Entity{
protected:
    int givenLifePoints;
public:
    StaticEntity* next;

public:
    StaticEntity(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int givenLifePoints, StaticEntity *next);

    /*
     * Metodo utilzzato per verificare che la posizione scelta randomicamente per la posizione della StaticEntity sia validaret
     */
    bool checkStaticEntityPosition(int posXToCheck, int posYToCheck, Wall* interiorWalls, StaticEntity* powers, StaticEntity* artifacts);

    /*
    * Metodo di tipo get che restituisce il valore dell'attributo givenLifePoints
    */
    int getGivenLifePoints();
};


#endif //PROGETTO_PROGRAMMAZIONE_STATICENTITY_HPP
