#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED
//#define _GLIBCXX_USE_CXX11_ABI 0
#include <SFML/Graphics.hpp>
#include <iostream>
#include "initialState.h"
#include "testState1.h"
#include "resourceManager.h"
//#include "mapHandler.h"
#include "player.h"

class Game
{
public:
    Game();
    void mainGameLoop();
    void changeState(State* nState);
    ResourceManager resourceManager;
    sf::RenderWindow renderWindow;
    int getWindowWidth();
    int getWindowHeight();
    //MapHandler mapHandler;
private:
    sf::View defaultView;
    State* state;
    const int WINDOW_WIDTH;
    const int WINDOW_HEIGHT;
};


#endif // GAME_H_INCLUDED
