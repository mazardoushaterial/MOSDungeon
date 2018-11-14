#ifndef DJIKSTRA_H_INCLUDED
#define DJIKSTRA_H_INCLUDED
//#include "map.h"
#include <stdlib.h>
#define MAX_X 60
#define MAX_Y 60
class Node
{
  public:
      int gCost;    //Cost of the current node
      int hCost;
      int totalCost;
      int getTotalCost()
      {
          return gCost + hCost;
      }
      int getHCost(int x1, int y1, int x2, int y2)
      {
          return abs(x2-x1) + abs(y2-y1);
      }

      int state;    //0 = undefined(unevaluated,visitable), 1 = closed(visited)/blocked,2 = open(available,visitable)
      //Node * prev;  //The node that this one is pointing to
};

class Coord
{
    public:
        Coord()
        {
        }
        Coord(int x, int y)
        {
            this->x = x;
            this->y = y;
        }
        int x;
        int y;
};


class Djikstra
{
public:
    Djikstra();

    int map[MAX_Y*MAX_X];
    int moveCheck[3][3];
    bool outOfBounds(int x, int y);
    void drawStates(Node node[MAX_Y][MAX_X]);
    void evaluteAdjacent(Node (*node)[MAX_X],Coord currentNode);
    void selectBestNode(Node node[MAX_Y][MAX_X], Coord * currentNode);
    void setUpMap(int nMap[MAX_Y][MAX_X]);
    void setUp(Node * node);
    int djikstra(int x2, int y2, int x1, int y1);
};

#endif // DJIKSTRA_H_INCLUDED
