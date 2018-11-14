#include "djikstra.h"
#include <iostream>
#define SEARCH_LIMIT 300
Djikstra::Djikstra()
{
    moveCheck[0][0] = 0;
    moveCheck[0][1] = 1;
    moveCheck[0][2] = 2;
    moveCheck[1][0] = 7;
    moveCheck[1][1] = 9;
    moveCheck[1][2] = 3;
    moveCheck[2][0] = 6;
    moveCheck[2][1] = 5;
    moveCheck[2][2] = 4;
}

bool Djikstra::outOfBounds(int x, int y)
{
    //If any of these conditions are met, then we fail
    return (x < 0 || x >= MAX_X || y < 0 || y >= MAX_Y); //current element compared to map size
}


void Djikstra::drawStates(Node node[MAX_Y][MAX_X])
{
    //std::cout << '\n';
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            std::cout << node[y][x].state;
        }
        std::cout << '\n';
    }
}

void Djikstra::evaluteAdjacent(Node (*node)[MAX_X],Coord currentNode) //Graph,currentNode
{
    node[currentNode.y][currentNode.x].state = 1; //close the current node
    int gValue = 1;
    for (int x = -1; x <= 1; x++)
    {
        for (int y = -1; y <= 1; y++)
        {
            //Don't check the current node
            if (
                (y == 0) && (x == 0)
                //Don't check corners
                || (x == 1 && y == 1)
                || (x == -1 && y == -1)
                || (x == 1 && y == -1)
                || (x == -1 && y == 1)
                )
            {
                //do nothing
            }
            else if (!outOfBounds(currentNode.x+x,currentNode.y+y))  //If the element is not out of bounds
            {
                if ((node[currentNode.y+y][currentNode.x+x].state == 0))    //setundefined node
                {
                    //...then evalute it, or re-evaluate it
                    node[currentNode.y+y][currentNode.x+x].state = 2;    //Make it available as an open node first
                    node[currentNode.y+y][currentNode.x+x].gCost = node[currentNode.y][currentNode.x].gCost + gValue; //Adjacent node gCost = oldGCost + distance to old current
                    //Link to old node
                    //node[currentNode.y+y][currentNode.x+x].prev = &node[currentNode.y][currentNode.x];
                }
                else if ((node[currentNode.y+y][currentNode.x+x].state == 2))    //reevalute...
                {
                    if (node[currentNode.y+y][currentNode.x+x].gCost > node[currentNode.y][currentNode.x].gCost + gValue)   //...if changing it would give a better value...
                    {
                        node[currentNode.y+y][currentNode.x+x].gCost = node[currentNode.y][currentNode.x].gCost + gValue;
                        //Pointer to old node
                        //node[currentNode.y+y][currentNode.x+x].prev = &node[currentNode.y][currentNode.x];

                    }
                    //...Otherwise just exit.
                }
            }
            //std::cout << "bean" << std::endl;
        }
    }
    //drawStates(node);
}

void Djikstra::selectBestNode(Node node[MAX_Y][MAX_X], Coord * currentNode)
{
    Coord bestNode;
    bestNode.x = MAX_X; //Non-reachable value
    bestNode.y = MAX_Y; //Non-reachable value
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if(bestNode.x == MAX_X && bestNode.y == MAX_Y && node[y][x].state == 2) //If there is no best value yet
            {
                bestNode.x = x;
                bestNode.y = y;
            }
            //If open and less gCost than current best
            else if ((node[y][x].state == 2)  && (node[y][x].gCost) < (node[bestNode.y][bestNode.x].gCost))
            {
                bestNode.x = x;
                bestNode.y = y;
            }
        }
    }
    //The best node will be the next currentNode
    currentNode->x = bestNode.x;
    currentNode->y = bestNode.y;
    return;
}

void Djikstra::setUp(Node * node)
{
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if (map[(((y*MAX_X)+x))] == 0)
            {
                (node+((y*MAX_X)+x))->state = 0;  //Ready
            }
            else
            {
                (node+((y*MAX_X)+x))->state = 1;  //Blocked
            }
        }
    }
    return;
}

int Djikstra::djikstra(int x2, int y2, int x1, int y1)
{
    Node node[MAX_Y][MAX_X];    //All the nodes
    setUp(&node[0][0]);
    node[y1][x1].gCost = 0; //Start point starts with no cost
    Coord currentNode;
    currentNode.x = x1;
    currentNode.y = y1;
    //drawStates(node);
    for(int i = 0; i < SEARCH_LIMIT; i++) //Only do pathfinding for SEARCH_LIMIT
    {
        evaluteAdjacent(node,currentNode);
        //drawStates(node);
        selectBestNode(node,&currentNode);
        if(currentNode.x == MAX_X && currentNode.y == MAX_Y) //Didn't work out: No path.
        {
            //std::cout << "No path" << std::endl;
            return 9; //No path magic number
        }
        //std::cout << currentNode.x << std::endl;
        //std::cout << currentNode.y << std::endl;
        //std::cout << node[currentNode.y][currentNode.x].gCost << std::endl;
        //If we find the end node.
        //if (currentNode.y == y2 && currentNode.x == x2)
        //{
            for (int y = -1; y <= 1; y++)
            {
                for (int x = -1; x <= 1; x++)
                {
                    if (x == 0 && y == 0
                        //Don't check corners
                        || (x == 1 && y == 1)
                        || (x == -1 && y == -1)
                        || (x == 1 && y == -1)
                        || (x == -1 && y == 1))
                    {
                        //nothing
                    }
                    else if (currentNode.y+y == y2 && currentNode.x+x == x2)
                    {
                        //Return the movement value
                        return moveCheck[y+1][x+1];
                    }
                }
            }
            //return Coord(0,0);
        //}
    }
    return 9;
}

//Set a map from outside to the Djistra map class
void Djikstra::setUpMap(int nMap[MAX_Y][MAX_X])
{
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            map[(y*MAX_X)+x] = nMap[y][x];
        }
    }
}
