#ifndef TESTSTATE1_H_INCLUDED
#define TESTSTATE1_H_INCLUDED
#include "state.h"
#include "player.h"
#include "game.h"
#include "map.h"
#include "djikstra.h"
#include <SFML/Graphics.hpp>
#define MAX_ENEMIES 25
class TestState1: public State
{
    public:
        TestState1(Game* pGame);
        void update();
        void draw();
        void input();
        void checkCreatureWeaponPosition(Player * creature);
        void moveEnemies();
        void moveEnemy(int i);
        void drawEnemies();
        void throwingCollision();
        void lineOfSight();
        void spawnEnemies();
        void scatterEnemies();
        void enemyGoto(int i, int x, int y);
        void enemyGotoTile(int i, int x, int y);
        bool isColliding(Player creature); //isColliding with World
        void playerWeaponVsEnemies();
        double distanceBetween(int x1, int y1, int x2, int y2);
        void enemyPathfindToPlayer(int i);
        void tempProjectile();
        void spawnProjectile(int centerX, int centerY,double vecX, double vecY);
        void knockBack(int i, int direction);
        void playerHitLogic();
        bool creatureCollision(int i, int j);
        //TEMP

    private:

        Game *game;
        Player player;
        Map worldMap;

        Player creature[MAX_ENEMIES];
        sf::View mainView;
        //Have two variables which determines if the camera should move in that axis,
        //The camera settings are linearly independent
        int cameraX;
        int cameraY;
        int waitToPathfind;
        Djikstra pathfinding;
        std::vector<Projectile> projectile;

};

#endif // TESTSTATE1_H_INCLUDED
