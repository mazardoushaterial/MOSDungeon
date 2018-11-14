#ifndef WEAPON_H_INCLUDED
#define WEAPON_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>


class Weapon
{
    public:
        Weapon();
        Weapon(sf::Texture &rTexture);
        sf::Sprite sprite;
        sf::Texture texture;
        sf::Clock clock;
        sf::Time time;
        int targetX; //Where the weapon hits
        int targetY;
        int getTimeElapsed();
        bool active; //attack cooldown
        void setTexture(sf::Texture &rTexture);
        void setVisible(bool visible);
        void draw(sf::RenderWindow &renderWindow);
        void resetElapsedTime(); //OBSOLETE EXCEPT FOR ANIMATION
        bool isMelee();
        bool isThrowable();
        bool isReturnable();
        void setTarget(int x, int y);
        void setPosition(int x, int y);
        void setVector(int x, int y);
        int getVecX();
        int getVecY();
        int getPositionX();
        int getPositionY();
        int spriteOffsetY;
        bool isReturning();
        void startReturning();
        void stopReturning();
        std::string getName();
        void loadWeapon(std::string file);
        int getActionTime();
        int getDownTime();
        int getCenterX();
        int getCenterY();
        int getSpeed();
        //int getFacing();
        //int setFacing(int a);
        virtual void update();
        virtual void action();
    protected:
        int x;
        int y;
        //direction vectors
        int vecX;//
        int vecY;
        int speed;
        bool returnable;
        bool returning;
        int actionTime; //The time is takes for an action from start to completion
        int downTime;
        //Note: The boomerang's downtime begins after the apex of it's flight
        //Not when it's in the players' possession. Fix if you want, I don't care.
        //int facing; //URDL
        int timeElapsed; //DO NOT USE EXCEPT FOR ANIMATION!! IT IS OBSOLETE
        bool melee;
        bool throwable;
        std::string name;
};

#endif // WEAPON_H_INCLUDED
