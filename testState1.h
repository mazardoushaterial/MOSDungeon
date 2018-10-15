#ifndef TESTSTATE1_H_INCLUDED
#define TESTSTATE1_H_INCLUDED
#include "state.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include <SFML/Graphics.hpp>
class TestState1: public State
{
    public:
        TestState1(Game* pGame);
        void update();
        void draw();
        void input();
        void checkPlayerWeaponPosition();
        void moveEnemies();
        void drawEnemies();
        void throwingCollision();
        void lineOfSight();
    private:
        Game *game;
        Player player;
        Map worldMap;

        Player enemy[25];
        sf::View mainView;
        //Have two variables which determines if the camera should move in that axis,
        //The camera settings are linearly independent
        int cameraX;
        int cameraY;
};

#endif // TESTSTATE1_H_INCLUDED
