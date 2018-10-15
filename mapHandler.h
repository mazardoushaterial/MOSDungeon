#ifndef MAPHANDLER_H_INCLUDED
#define MAPHANDLER_H_INCLUDED
#include <SFML/Graphics.hpp>
#include <fstream>
#include <iostream>
class Game;
class MapHandler
{
  public:
        MapHandler(Game* pGame);
        //currentmap (map file)
        sf::View mainView;
        std::string tilemap[100][100];
        std::ifstream getMap;
        //void updateChunkPosition();
        void updateTilePosition();
        void updateTileMap();
        int convertToChunk(int a);
        int getCursorX();
        int getCursorY();
        void updateCursorPosition();
        void moveCursor(int x, int y);
        void move(int x, int y);
        sf::Sprite cursor;
  private:
        Game* game;
        void loadMap();
        //The camera's chunk position (grid unit)
        //The camera's 2D view of the world.
        int x;
        int y;
        //int chunkX;
        //int chunkY;
        int cursorX;
        int cursorY;
        void setUpTiles();
  public:
        //The visible tiles
        sf::Sprite tiles[15][20];
        //Select the position of the tiles
        //draw the tiles' in their position

        //Draw the chunks
        //The 9 chunk tiles
        //Detect the chunks changing
        //Changing the chunks when you move into a new square
};

#endif // MAPHANDLER_H_INCLUDED
