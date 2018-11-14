#ifndef PROJECTILE_H_INCLUDED
#define PROJECTILE_H_INCLUDED
#include <stdlib.h> //math
#include <math.h>
#include <SFML/Graphics.hpp>
class Projectile
{
public:
    Projectile();
    Projectile(int centerX, int centerY, double vecX, double vecY);
    int getPositionX();
    int getPositionY();
    void setPosition(int x, int y);
    int getCenterX();
    int getCenterY();
    void setCenter(int x, int y);
    void setTrajectory(int x1, int y1, int x2, int y2);
    void setMagic(int nMagic);
    void update();
    void setTexture(sf::Texture texture);
    bool notMoving();
    sf::Sprite sprite;
private:
    //Raw X and Y positions
    double rawX;
    double rawY;
    //Direction vectors
    double vecX;
    double vecY;
    int magic;
    int speed = 5;
};

#endif // PROJECTILE_H_INCLUDED
