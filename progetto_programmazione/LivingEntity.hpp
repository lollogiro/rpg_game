#include "Entity.hpp"
#include "Bullet.hpp"
#include "Wall.hpp"

#pragma once //altrimenti da redefinition error

class LivingEntity : public Entity{
protected:
    int lifePoints;
public:
    Bullet* bullets;

public:
    /*
     * Costruttore della classe LivingEntity
     */
    LivingEntity(char mapSymbol, int posX, int posY, bool secret, WINDOW *win, int lifePoints, Bullet *bullets);

    /*
     * Metodo utilizzato per gli spostamenti in alto all'interno della mappa
     */
    void moveUp(bool openedDoor, bool secretDoor, Wall* interiorWalls);

    /*
     * Metodo utilizzato per lo spostamento in basso all'interno della mappa
     */
    void moveDown(bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls);

    /*
     * Metodo utilizzato per lo spostamento a sinistra all'interno della mappa
     */
    void moveLeft(bool openedDoor, bool levelGreaterThanOne, Wall* interiorWalls);
    /*
     * Metodo utilizzato per lo spostamento a destra all'interno della mappa
     */
    void moveRight(bool openedDoor, bool levelGreaterThanOne, bool secretDoor, Wall* interiorWalls);

    /*
     * Metodo utilizzato per creare un proiettile
     */
    void createBullet(bulletAxisDirection axisDirection, Wall* interiorWalls, bool player, int levelNumber);

    /*
     * Metodo utilizzato per aggiornare la posizione dei proiettili appartenenti alla LivingEntity
     */
    void updateBulletPosition(Wall* interiorWalls);

    /*
     * Metodo utilizzato per verificare le collisioni tra proiettili e muri interni
     */
    bool checkBulletOnInteriorWalls(int posXToCheck, int posYToCheck, Wall* interiorWalls);

    /*
     * Metodo utilizzato per l'eliminazione dei proiettili non validi dalla lista
     */
    void deleteNotValidBullet(Wall* interiorWalls);

    /*
     * Metodo utilizzato per stampare nella mappa i proiettili appartenenti alla LivingEntity
     */
    void printEntityBullets();

    /*
     * Metodo utilizzato per gestire lo sparo di un proiettile
     */
    void shootBullet(Wall* interiorWalls, bool player, int levelNumber);

    /*
     * Metodo utilizzato per modificare l'attributo lifePoints in caso di collisione con Artefatti o proiettili
     */
    void modifyLifepoints(int points, bool hit);

    /*
     * Metodo per vedere se l'entità è ancora valida
     */

    bool isValid();

    /*
     * Metodo per verificare se il nemico di tipo kamikaze è nella stessa posizione del player
     */

    bool checkKamikazeOnPlayer(LivingEntity* player, LivingEntity* kamikaze);

    /*
     * Metodo di tipo getter
     */

    int getLifePoints();
};