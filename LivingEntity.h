#include "Entity.h"
#include "Bullet.h"

class LivingEntity : public Entity{
public:
    int lifePoints;
    Bullet* bullets;

public:
    LivingEntity(char mapSymbol, int posX, int posY, WINDOW *win, int lifePoints, Bullet *bullets);
    void printLivingEntity();
    void moveUp(bool openedDoor, bool secretDoor);
    void moveDown(bool levelGreaterThanOne, bool secretDoor);
    void moveLeft(bool openedDoor, bool levelGreaterThanOne);
    void moveRight(bool openedDoor, bool levelGreaterThanOne, bool secretDoor);
    void createBullet(bulletAxisDirection axisDirection);
    void updateBulletPosition();
    void deleteNotValidBullet();
    void printEntityBullets();
    void shootBullet();
    void displayMove(int userInput, bool openedDoor, bool levelGreaterThanOne, bool secretDoor);
};