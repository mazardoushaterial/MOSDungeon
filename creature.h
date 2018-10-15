#ifndef CREATURE_H_INCLUDED
#define CREATURE_H_INCLUDED
#include <SFML/Graphics.hpp>
#include "map.h"
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
        bool isAlive();
        void move(int x, int y);
        void moveBack(int x, int y);
        void setPosition(int x, int y);
        sf::Sprite sprite;
        int getSpeed();
    protected:
        int speed;
        sf::Clock clock; //Gives us the time
        sf::Time elapsed; //Time elapsed storage unit
        int elapsedAccumulated; //The elapsed time since the last animation flip
        const int DELAY; //Animation delay in milliseconds
        bool flip; //Flip between the animation cells
        int x;
        int y;
        bool alive;
        int facing; //URDL
        int health;
        Game* game;
        void defaultSetup();
        void updateSprite();
};


#endif // CREATURE_H_INCLUDED
