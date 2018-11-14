#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "map.h"
#include "djikstra.h"
class Game;
class Creature
{
    public:
        Creature();
        Creature(Game* pGame);
        void draw();
        int getPositionX();
        int getPositionY();
        int getLeft();
        int getRight();
        int getTop();
        int getBottom();
        int getCenterX();
        int getCenterY();
        int getGridPositionX();
        int getGridPositionY();
        int getFacing();
        bool isAlive();
        void move(int x, int y);
        void moveBack(int x, int y);
        void setPosition(int x, int y);
        sf::Sprite sprite;
        int getSpeed();
        int UD;
        int LR;
        void makeDead();
        int steps;
        int gotoX;
        int gotoY;
        int direction; //5,1,3,7 = UDLR
        void preventOutOfScreenErrors();
        //Djikstra pathfinding;
    protected:
        int speed;
        sf::Clock clock; //Gives us the time
        sf::Time elapsed; //Time elapsed storage unit
        int elapsedAccumulated; //The elapsed time since the last animation flip
        const int DELAY; //Animation delay in milliseconds
        bool flip; //Flip between the animation cells
        int x;
        int y;
        int vecX; //Movewment factor x
        int vecY; //Movement factor y
        //bool alive;
        int facing; //URDL
        int health;
        Game* game;
        void defaultSetup();
        void updateSprite();
        int spriteOffset;
};


#endif // CREATURE_H_INCLUDED
