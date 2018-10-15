#include "weapon.h"

Weapon::Weapon()
{
    int x = 0;
    int y = 0;
    setVisible(false);
    active = false;
    melee = true;
    returnable = false;
    name = "knife";
}

Weapon::Weapon(sf::Texture &rTexture)
{
    int x = 0;
    int y = 0;
    setTexture(rTexture);
    setVisible(false);
    active = false;
    melee = true;
    returnable = false;
    name = "knife";
}

void Weapon::setTexture(sf::Texture &rTexture)
{
    timeElapsed = 0;
    texture = rTexture;
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect(0,0,16,16));
}


void Weapon::draw(sf::RenderWindow &renderWindow)
{
    renderWindow.draw(sprite);
}

void Weapon::setVisible(bool visible)
{
    if (visible)
        sprite.setColor(sf::Color(255,255,255,255));
    else
        sprite.setColor(sf::Color(255,255,255,0));
}

int Weapon::getTimeElapsed()
{
    time = clock.restart();
    timeElapsed += time.asMilliseconds();
    return timeElapsed;
}

void Weapon::resetElapsedTime()
{
    timeElapsed = 0;
}

void Weapon::action()
{

}

bool Weapon::isMelee()
{
    return melee;
}

//Relative to the world
void Weapon::setTarget(int x, int y)
{
    targetX = x;
    targetY = y;
}

void Weapon::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    sprite.setPosition(x,y);
}

void Weapon::setVector(int x, int y)
{
    vecX = x;
    vecY = y;
}

int Weapon::getPositionX()
{
    return x;
}

int Weapon::getPositionY()
{
    return y;
}

int Weapon::getVecX()
{
    return vecX;
}

int Weapon::getVecY()
{
    return vecY;
}

bool Weapon::isReturnable()
{
    return returnable;
}

void Weapon::startReturning()
{
    returning = true;
}

void Weapon::stopReturning()
{
    returning = false;
}

bool Weapon::isReturning()
{
    return returning;
}

bool Weapon::isThrowable()
{
    return throwable;
}

/*
int Weapon::getFacing()
{
    return facing;
}

int Weapon::setFacing(int a)
{
    facing = a;
}
*/

std::string Weapon::getName()
{
    return name;
}

void Weapon::loadWeapon(std::string file)
{
    std::ifstream getMap;
    //TEST
    getMap.open(file.c_str());

    getMap >> name;
    //setVisible(getMap);
    getMap >> melee;
    getMap >> returnable;
    getMap >> throwable;
    getMap >> actionTime;
    getMap >> downTime;
    getMap >> spriteOffsetY;
    getMap >> speed;

    std::cout << name << std::endl;
    std::cout << melee << std::endl;
    std::cout << returnable << std::endl;
    std::cout << throwable << std::endl;
    std::cout << actionTime << std::endl;
    std::cout << downTime << std::endl;
    std::cout << spriteOffsetY << std::endl;
    std::cout << speed << std::endl;

    getMap.close();
}

int Weapon::getActionTime()
{
    return actionTime;
}

int Weapon::getDownTime()
{
    return downTime;
}

int Weapon::getCenterX()
{
    return x+8;
}

int Weapon::getCenterY()
{
    return y+8;
}

int Weapon::getSpeed()
{
    return speed;
}

//vtable
void Weapon::update(){}
