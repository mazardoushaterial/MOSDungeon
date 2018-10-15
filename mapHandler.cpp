#include "mapHandler.h"
#include "game.h"
MapHandler::MapHandler(Game* pGame)
{
    game = pGame;
    std::cout << "Map handler initializing" << std::endl;
    this->x = 0;
    this->y = 0;
    mainView.setSize(sf::Vector2f(1000, 750));
    mainView.setCenter(sf::Vector2f(1000/2, 750/2));
    setUpTiles();
    loadMap();

    cursor.setTexture(game->resourceManager.cursorTextures);

}

void MapHandler::setUpTiles()
{
    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            this->tiles[y][x].setOrigin(0,0);
            this->tiles[y][x].setTexture(game->resourceManager.tileTextures);
            this->tiles[y][x].setTextureRect(sf::IntRect(50,0,50,50));
        }
    }
}

void MapHandler::loadMap()
{
    std::string temp;
    getMap.open("test1.map");
    for (int y = 0; y < 100; y++)
    {
        for (int x = 0; x < 100; x++)
        {
            getMap >> tilemap[y][x];
        }
    }
    getMap.close();
}

int MapHandler::getCursorX()
{
    return cursorX;
}

int MapHandler::getCursorY()
{
    return cursorY;
}

void MapHandler::updateTilePosition()
{
    //The start of the tilemap is p(12,-9) from the center of the screen.
    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            this->tiles[y][x].setPosition(x*50,y*50);
        }
    }
    //std::cout << "x:" << chunkX<< std::endl;
    //std::cout << "y:" << chunkY<< std::endl;
}

void MapHandler::updateTileMap()
{
    for (int y = 0; y < 15; y++)
    {
        for (int x = 0; x < 20; x++)
        {
            if (tilemap[y+this->y][x+this->x] == "gras")
            {
                tiles[y][x].setTextureRect(sf::IntRect(0,0,50,50));
            }
            else if (tilemap[y+this->y][x+this->x] == "bug")
            {
                tiles[y][x].setTextureRect(sf::IntRect(100,0,50,50));
            }
            else
            {
                tiles[y][x].setTextureRect(sf::IntRect(50,0,50,50));
            }
        }
    }

}


/*void MapHandler::updateChunkPosition()
{
    //X-Position - (the fat) / 50 = the chunk position
    chunkX = ((x)-((x)%50))/50;
    chunkY = ((y)-((y)%50))/50;
    std::cout << chunkX << std::endl;
    std::cout << chunkY << std::endl;
}
*/

int MapHandler::convertToChunk(int a)
{
    return ((a)-((a)%50))/50;
}

void MapHandler::updateCursorPosition()
{
    cursor.setPosition(getCursorX()*50,getCursorY()*50);
}

void MapHandler::moveCursor(int x, int y)
{
    cursorX+=x;
    cursorY+=y;
}

void MapHandler::move(int x, int y)
{
    this->x += x;
    this->y += y;
}
