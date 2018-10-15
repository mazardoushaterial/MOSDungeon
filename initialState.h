#ifndef INITIALSTATE_H_INCLUDED
#define INITIALSTATE_H_INCLUDED
#include "state.h"
#include "testState1.h"
#include "game.h"
#include <SFML/Graphics.hpp>
//
//This class is created because of a bug
//->The window freezes for the first few seconds
//->This is a HACK
//


class InitialState: public State
{
    public:
        InitialState(Game* pGame);
        void update();
        void draw();
        void input();
    private:
        bool startGame;
        Game *game;
        sf::Sprite splash;
        sf::RectangleShape blackRectangle;
};


#endif // INITIALSTATE_H_INCLUDED
