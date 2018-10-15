#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <math.h>

#define MAX_X 60
#define MAX_Y 60

typedef unsigned char byte;

enum Tiles {EMPTY,BROWN};
class Game;
class Map
{
    public:
        Map(Game *pGame);
        void draw();
        void loadMap(std::string file);
        int tile[60][60];
        bool visible[60][60]; //If the tile is visible
        sf::Sprite sprite;

        void makeInvisible();
        void makeCave();
        bool castRay(int x1, int y1, int x2, int y2);
        //void lineOfSight();
    private:
        Game *game;
        int grid[MAX_Y*MAX_X];
        void mazeSetup();
        void drawMap();
        bool outOfBounds(int x, int y);
        int nNeighbors(int x, int y);
        void caveGeneration();

};

#endif // MAP_H_INCLUDED
