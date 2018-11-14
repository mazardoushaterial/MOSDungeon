#include "creature.h"
#include "game.h"
#include <iostream>

Creature::Creature():
    DELAY(200) // half a second delay
{
}

Creature::Creature(Game* pGame):
    DELAY(200) // half a second delay
{
    defaultSetup();
}

void Creature::draw()
{
    game->renderWindow.draw(sprite);
}


int Creature::getPositionX()
{
    return x;
}

int Creature::getPositionY()
{
    return y;
}


int Creature::getLeft()
{
    return x+2;
}
int Creature::getRight()
{
    return x+15-2;
}
int Creature::getTop()
{
    return y+4;
}
int Creature::getBottom()
{
    return y+15;
}

/*
int Creature::getLeft()
{
    return x;
}
int Creature::getRight()
{
    return x+15;
}
int Creature::getTop()
{
    return y;
}
int Creature::getBottom()
{
    return y+15;
}
*/

int Creature::getCenterX()
{
    return getPositionX() + 8;
}
int Creature::getCenterY()
{
    return getPositionY() + 8;
}

int Creature::getFacing()
{
    return facing;
}

void Creature::moveBack(int x, int y)
{
    this->x += x;
    this->y += y;
    updateSprite();
}
void Creature::setPosition(int x, int y)
{
    this->x = x;
    this->y = y;
    updateSprite();
}
void Creature::move(int x, int y)
{
    if (x == -1*getSpeed())
    {
        facing = 3;
    }
    else if (x == 1*getSpeed())
    {
        facing = 1;
    }
    else if (y == -1*getSpeed())
    {
        facing = 0;
    }
    else if (y == 1*getSpeed())
    {
        facing = 2;
    }
    //Incremement the X and Y, but not in the cheap way
    for (int i = x; i != 0; i--)
    {
        this->x++;
    }
    for (int i = y; i != 0; i--)
    {
        this->y++;
    }
    elapsed = clock.restart();
    elapsedAccumulated+=elapsed.asMilliseconds(); //accumulated time
    if (elapsedAccumulated > DELAY) //Stops the animated from going to fast
    {
        elapsedAccumulated = 0; //Reset timer
        if (flip == 1) //flipper
        {
            flip = 0;
        }
        else
        {
            flip = 1;
        }
    }
    updateSprite();
}

void Creature::updateSprite()
{
    sprite.setTextureRect(sf::IntRect(16*facing,16*flip+spriteOffset*16,16,16));
    sprite.setPosition(this->x,this->y);
}

void Creature::defaultSetup()
{
    flip = 1;
    health = 1;
    //alive = true;
    x = 16;
    y = 16;
    facing = 2; //facing down
}

bool Creature::isAlive()
{
    if (health >= 0)
    {
        return true;
    }
    return false;
}

int Creature::getSpeed()
{
    return speed;
}

int Creature::getGridPositionX()
{
    return (getCenterX()-(getCenterX()%16))/16;
}
int Creature::getGridPositionY()
{
    return (getCenterY()-(getCenterY()%16))/16;
}

void Creature::makeDead()
{
    health = -1;
    sprite.setTextureRect(sf::IntRect(16*4,spriteOffset*16,16,16));
}

//Make the player stay on screen by teleporting them into the visible space
void Creature::preventOutOfScreenErrors()
{
    if (getLeft() < 0)
    {
        setPosition(getLeft(),y);
    }
    if (getRight() > MAX_X*16)
    {
        setPosition(MAX_X*16-16,y);
    }
    if (getTop() < 0)
    {
        setPosition(x,getTop());
    }
    if (getBottom() > MAX_Y*16)
    {
        setPosition(x,MAX_Y*16-16);
    }

}
