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
                sprite.setTextureRect(sf::IntRect(16,0,16,16));
            }
            else //tile is seen
            {
                switch(tile[y][x])
                {
                case BROWN:
                    sprite.setTextureRect(sf::IntRect(16,0,16,16));
                    break;
                case DL:
                    sprite.setTextureRect(sf::IntRect(0,16*2,16,16));
                    break;
                case DR:
                    sprite.setTextureRect(sf::IntRect(16*2,16*2,16,16));
                    break;
                case DU:
                    sprite.setTextureRect(sf::IntRect(16,16,16,16));
                    break;
                case DD:
                    sprite.setTextureRect(sf::IntRect(16,16*3,16,16));
                    break;
                case DUL:
                    sprite.setTextureRect(sf::IntRect(0,16,16,16));
                    break;
                case DUR:
                    sprite.setTextureRect(sf::IntRect(16*2,16,16,16));
                    break;
                case DDL:
                    sprite.setTextureRect(sf::IntRect(0,16*3,16,16));
                    break;
                case DDR:
                    sprite.setTextureRect(sf::IntRect(16*2,16*3,16,16));
                    break;
                case DC:
                    sprite.setTextureRect(sf::IntRect(16,16*2,16,16));
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

    makeDungeonTheme();
}



bool Map::castRay(int x1, int y1, int x2, int y2)
{
    //Just a little cheatsy doodle because
    //The player's square needs to be lit
    //Only do processes while inside processable grid
        if(round(x1) >= 0 && round(x1) < MAX_X && round(y1) >= 0 && round(y1) < MAX_Y)
        {
            visible[y1][x1] = true;
        }
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
        if(round(x) >= 0 && round(x) < MAX_X && round(y) >= 0 && round(y) < MAX_Y)
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

int Map::convertVoxelToGrid(int i)
{
    return (i-(i%16))/16;
}

//change the map to make it dungeon themed
void Map::makeDungeonTheme()
{
    for (int x = 0; x < MAX_X; x++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            if (!(outOfBounds(x,y)) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DC; //CENTER DARK TILE
            }
            if ((!outOfBounds(x+1,y)) && (tile[y][x+1] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DR;//dungeon tile right facing
            }
            if ((!outOfBounds(x-1,y)) && (tile[y][x-1] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DL;//
            }
            if ((!outOfBounds(x,y-1)) && (tile[y-1][x] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DU;//
            }
            if ((!outOfBounds(x,y+1)) && (tile[y+1][x] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DD;//
            }
            //The corners
            if ((!outOfBounds(x-1,y)) && (!outOfBounds(x,y-1)) && (tile[y][x-1] == EMPTY) && (tile[y-1][x] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DUL;//dungeon tile right facing
            }
            if ((!outOfBounds(x+1,y)) && (!outOfBounds(x,y-1)) && (tile[y][x+1] == EMPTY) && (tile[y-1][x] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DUR;//dungeon tile right facing
            }
            if ((!outOfBounds(x-1,y)) && (!outOfBounds(x,y+1)) && (tile[y][x-1] == EMPTY) && (tile[y+1][x] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DDL;//dungeon tile right facing
            }
            if ((!outOfBounds(x+1,y)) && (!outOfBounds(x,y+1)) && (tile[y][x+1] == EMPTY) && (tile[y+1][x] == EMPTY) && (tile[y][x] != EMPTY))
            {
                tile[y][x] = DDR;//dungeon tile right facing
            }


        }
    }
}

bool Map::isConnectable(int rx, int ry)
{
    //Find the adjactent rooms
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            //TODO: BUG with out of bounds
            if ((ry+y < 0) || (ry+y >= MAX_Y/PARTITION_SIZE) || (rx+x < 0) || (rx+x >= MAX_X/PARTITION_SIZE))
            {
                //do nothing if out of bounds of partition
            }
            else if (((x==0) && (y==0)))
            {
                //do nothing if in center
            }
            //If it's not a diagonal and also not the center
            else if (((x == 0) || (y == 0)))
            {
                //If one of the partitions is connectable
                if (partition[ry+y][rx+x] == 1)
                {
                    connectedTo[ry][rx] = (((ry+y)*(MAX_X/PARTITION_SIZE))+rx+x);
                    connectedX[ry][rx] = rx+x;
                    connectedY[ry][rx] = ry+y;
                    return true;
                }
            }
        }
    }
    return false;
}


void Map::connectRooms(int x1, int y1, int x2, int y2)
{
    int x = x1;
    int y = y1;
    //while it's not the end
    while  (!((x == x2) && (y == y2)))
    {
        //If it's true and needs to go up
        if (game->randInt(2))
        {
            if (x < x2)
            {
                //then go up
                x++;
            }
            if (x > x2)
            {
                x--;
            }
        }
        else
        {
            if (y < y2)
            {
                y++;
            }
            if (y > y2)
            {
                y--;
            }
        }
        tile[y][x] = 1;
    }
}

void Map::createRectangularRoom(int rx, int ry)
{
    //Flag the room as connected
    partition[ry][rx] = 1;
    int positionX, positionY;
    int width, height; //A range of 1-10

    //Don't go out of partition (which is of size 10)
    do
    {
        //The point to start at (relative to partition)
        positionX = game->randInt(PARTITION_SIZE-3)+1; //a range of 1-18
        positionY = game->randInt(PARTITION_SIZE-3)+1; //a range of 1-18
        width = game->randInt(10)+8; //a range of 6-18 (partition size - 2 = 18)
        height= game->randInt(10)+8; //a range of 6-18
        roomCenterX[ry][rx] = (rx*PARTITION_SIZE)+positionX+(width/2);
        roomCenterY[ry][rx] = (ry*PARTITION_SIZE)+positionY+(height/2);
    } while (positionX+width > PARTITION_SIZE || positionY+height > PARTITION_SIZE);
    //Fill the room with walls where we want
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            //Where the partition starts + where we want to fill
            /*
            if (x == 0 || x==width-1 || y == 0 || y == height-1)
            {
                //Where we can place a corridor
                map[ry*PARTITION_SIZE+(positionY+y)][rx*PARTITION_SIZE+(positionX+x)] = 2;
            }
            else
            */
            {
                //where we can place a room
                tile[ry*PARTITION_SIZE+(positionY+y)][rx*PARTITION_SIZE+(positionX+x)] = 1;
            }
        }
    }
}

bool Map::partitionsNotFull()
{
    for (int y = 0; y < MAX_Y/PARTITION_SIZE; y++)
    {
        for (int x = 0; x < MAX_X/PARTITION_SIZE; x++)
        {
            //A partition is not connected to the rest of the map
            if (partition[y][x] == 0)
            {
                return true;
            }
        }
    }
    return false; //All partitions are full
}

void Map::makeRogueLevel()
{
    //Create a room in a random partition as the start
    int startX = game->randInt(MAX_X/PARTITION_SIZE), startY = game->randInt(MAX_Y/PARTITION_SIZE);
    std::cout << "START (x) " << startX << " (y) " << startY << std::endl;
    partition[startY][startX] = 1; //Flag the partition
    connectedTo[startY][startX] = 9; //The partition is connected to no node, because it is the first
    //Start the node connected to itself
    connectedX[startY][startX] = startX;
    connectedY[startY][startX] = startY;
    createRectangularRoom(startX,startY);
    //Set all the rooms
    while (partitionsNotFull())
    {
        int px = game->randInt(MAX_X/PARTITION_SIZE);
        int py = game->randInt(MAX_Y/PARTITION_SIZE);
        //If there is no room there yet and it can be connected to the map
        if (partition[py][px] == 0 && isConnectable(px,py))
        {
            createRectangularRoom(px,py);
        }
    }
    //Lets connect all the rooms
    for (int y = 0; y < MAX_Y/PARTITION_SIZE;y++)
    {
        for (int x = 0; x < MAX_X/PARTITION_SIZE;x++)
        {
            connectRooms(roomCenterX[y][x],roomCenterY[y][x],roomCenterX[connectedY[y][x]][connectedX[y][x]],roomCenterY[connectedY[y][x]][connectedX[y][x]]);
        }
    }
    invertWallsAndFloors();
    makeDungeonTheme();
}

//The rogue levels are inverted for some reason, I don't remember why
void Map::invertWallsAndFloors()
{
    for (int x = 0; x < MAX_X; x++)
    {
        for (int y = 0; y < MAX_Y; y++)
        {
            if (tile[y][x] == EMPTY)
            {
                tile[y][x] = 1;
            }
            else
            {
                tile[y][x] = EMPTY;
            }
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

