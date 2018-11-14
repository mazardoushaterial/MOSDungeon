#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <string>
#include <fstream>

#include <iostream>
#include <cstdlib>
#include <ctime>

#include <math.h>

#define PARTITION_SIZE 20
#include <stdlib.h>
#include <time.h>
#define MAX_X 60
#define MAX_Y 60

typedef unsigned char byte;

enum Tiles {EMPTY,BROWN,DL,DR,DU,DD,DUL,DUR,DDL,DDR,DC};
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
        bool outOfBounds(int x, int y);
        int convertVoxelToGrid(int i);
        void makeDungeonTheme();
        //For the rogue-level gen
        bool isConnectable(int rx, int ry);
        void connectRooms(int x1, int y1, int x2, int y2);
        void createRectangularRoom(int rx, int ry);
        bool partitionsNotFull();
        void makeRogueLevel();
        void invertWallsAndFloors();
        //void lineOfSight();
    private:
        Game *game;
        int grid[MAX_Y*MAX_X];
        void mazeSetup();
        void drawMap();
        int nNeighbors(int x, int y);
        void caveGeneration();

        //For the rogue-level generation
        int partition[MAX_Y/PARTITION_SIZE][MAX_X/PARTITION_SIZE];
        int connectedTo[MAX_Y/PARTITION_SIZE][MAX_X/PARTITION_SIZE];

        //What the partition at (a,b) is connected to
        int connectedX[MAX_Y/PARTITION_SIZE][MAX_X/PARTITION_SIZE];
        int connectedY[MAX_Y/PARTITION_SIZE][MAX_X/PARTITION_SIZE];
        //The center of the respective rooms
        int roomCenterX[MAX_Y/PARTITION_SIZE][MAX_X/PARTITION_SIZE];
        int roomCenterY[MAX_Y/PARTITION_SIZE][MAX_X/PARTITION_SIZE];

};

#endif // MAP_H_INCLUDED
