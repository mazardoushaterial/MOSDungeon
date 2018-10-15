#ifndef STATE_H_INCLUDED
#define STATE_H_INCLUDED
#include <SFML/Graphics.hpp>
class Game; //Forward declaration
class State
{
    public:
        State();
        void logic();
        virtual void draw();
        virtual void input();
        virtual void update();
    protected:
        int tAcc;
        sf::Clock clock;
        sf::Time elapsed;
        Game* game;
};


#endif // STATE_H_INCLUDED
