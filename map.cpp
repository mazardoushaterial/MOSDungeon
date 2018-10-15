#include "map.h"
#include "game.h"
Map::Map(Game *pGame)
{
    game = pGame;
    sprite.setTexture(game->resourceManager.tileTextures);
}

void Map::draw()
{
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if (!visible[y][x]) //Tile is not seen
            {
                sprite.setTextureRect(sf::IntRect(16*4,0,16,16));
            }
            else //tile is seen
            {
                switch(tile[y][x])
                {
                case BROWN:
                    sprite.setTextureRect(sf::IntRect(16,0,16,16));
                    break;
                default:
                    sprite.setTextureRect(sf::IntRect(0,0,16,16));
                    break;
                }
            }
            sprite.setPosition(x*16,y*16);
            game->renderWindow.draw(sprite);
        }
    }
}

void Map::loadMap(std::string file)
{
    std::ifstream getMap;
    getMap.open(file.c_str());
    //put the rest of the code here
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            getMap >> tile[y][x];
        }
    }
    getMap.close();
}

void Map::mazeSetup()
{

    srand(time(NULL));
    for(int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            grid[(y*MAX_X)+x] = rand() % 2;
        }
    }
    return;
}

void Map::drawMap()
{
    for(int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if (grid[(y*MAX_X)+x] == 1)
            {
            std::cout << "@";
            }
            if (grid[(y*MAX_X)+x] == 0)
            {
            std::cout << ".";
            }
        }
        std::cout << "\n";
    }
    std::cout << "\n";
}

bool Map::outOfBounds(int x, int y)
{
    //If any of these conditions are met, then we fail
    return (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y); //current element compared to map size
}

int Map::nNeighbors(int x, int y)
{
    int n = 0;//# of neighbors
    for (int a = -1; a < 2; a++)
    {
        for (int b = -1; b < 2; b++)
        {
            if ((a==0 && b == 0) || outOfBounds(x+b,y+a))
            {
                //No nothing
            }
            else
            {
                if (grid[(((y+a)*MAX_X)+x+b)] == 1) //If neighbor is a wall.
                {
                    n++;
                }
            }
        }
    }
    return n;
}

void Map::caveGeneration()
{
    int tempGrid[(MAX_X*MAX_Y)];
    //Set grid to zero
    for (int i = 0; i < (MAX_X*MAX_Y); i++)
    {
        tempGrid[i] = 0;
    }

    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            //If it is a wall and four or more of it's neighbors is a wall
            //...or it is not a wall, but 5 or more neighbors are a wall
            if ((grid[(y*MAX_X)+x] == 1 && nNeighbors(x,y) >= 4) || (grid[(y*MAX_X)+x] == 0 && (nNeighbors(x,y) >= 5)))
            {
                //Preservation and Birth and Death
                tempGrid[(y*MAX_X)+x] = 1;
            }
        }
    }

    for (int j = 0; j < (MAX_X*MAX_Y); j++)
    {
        grid[j] = tempGrid[j];
    }
    //std::cout << nNeighbors(1,1) << std::endl;//test


}

void Map::makeCave()
{
    mazeSetup();
    for (int i = 0; i < 7; i++)
    {
        caveGeneration();
    }
    for (int x = 0; x < MAX_X; x++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            if (grid[(y*MAX_X)+x] == 0)
            {
                tile[y][x] = EMPTY;
            }
            else
            {
                tile[y][x] = BROWN;
            }
        }
    }
}



bool Map::castRay(int x1, int y1, int x2, int y2)
{
    //Just a little cheatsy doodle because
    //The player's square needs to be lit
    visible[y1][x1] = true;
    //setBoard(pBoard);
    int steps;
    float dx, dy, incX, incY, x = x1, y = y1;
    dx = x2-x1;
    dy = y2-y1;
    if (abs(dx) > abs(dy))
    {
        steps = abs(dx);
    }
    else
    {
        steps = abs(dy);
    }
    incX = dx / (float)steps;
    incY = dy / (float)steps;
    for (int i = 0; i < steps; i++)
    {
        x = x + incX;
        y = y + incY;

        //Only do processes while inside processable grid
        if(round(x) > 0 && round(x) < MAX_X && round(y) > 0 && round(y) < MAX_Y)
        {
            visible[(int)round(y)][(int)round(x)] = true;
        }

        //The ray stops
        if(round(x) == x2 && round(y) == y2)
        {
            //keep going
            return true;
        }
        else if(tile[(int)round(y)][(int)round(x)] != EMPTY) //&& (round(x) != x2 && round(y) != y2 && round(z) != z2)) //If the ray was blocked, by anything but the target (hitting the target is ideal)
        {
            return false;
        }
        //putTile(round(x),round(y),round(z));
    }
}

void Map::makeInvisible()
{
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            visible[y][x] = false;
        }
    }

}



/*
int main()
{
    mazeSetup();
    drawMap();
    caveGeneration();
    //drawMap();
    caveGeneration();
    //drawMap();
    caveGeneration();
    //drawMap();
    caveGeneration();
    //drawMap();
    caveGeneration();
    //drawMap();
    caveGeneration();
    //drawMap();
    caveGeneration();
    drawMap();
    return 0;
}
*/

