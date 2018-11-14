#include "projectile.h"

Projectile::Projectile(){}

Projectile::Projectile(int centerX, int centerY, double vecX, double vecY)
{
    this->vecX = vecX;
    this->vecY = vecY;
    this->rawX = (float)centerX-8;
    this->rawY = (float)centerY-8;
}

int Projectile::getPositionX()
{
    return (int)rawX;
}

int Projectile::getPositionY()
{
    return (int)rawY;
}

void Projectile::setPosition(int x, int y)
{
    rawX = x;
    rawY = y;
}

int Projectile::getCenterX()
{
    return (int)rawX+8;
}

int Projectile::getCenterY()
{
    return (int)rawY+8;
}

void Projectile::setCenter(int x, int y)
{
    rawX = x-8;
    rawY = y-8;
}

void Projectile::setTrajectory(int x1, int y1, int x2, int y2)
{
    int dy = y2 - y1;
    int dx = x2 - x1;
    double hyp = sqrt( pow(dy,2) + pow(dx,2) );
    double rad = atan2(dy,dx);
    vecX = cos(rad);
    vecY = sin(rad);
}

void Projectile::setMagic(int nMagic)
{
    magic = nMagic;
}

void Projectile::update()
{
    rawX = rawX + vecX*speed;
    rawY = rawY + vecY*speed;
}

bool Projectile::notMoving()
{
    return (vecX == 0 && vecY == 0);
}
