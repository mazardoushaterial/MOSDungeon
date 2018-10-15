#include "initialState.h"
InitialState::InitialState(Game* pGame)
{
    game = pGame;
    startGame = false;
    splash.setTextureRect(sf::IntRect(0,0,320,256));
    splash.setTexture(game->resourceManager.loadingSplash);
    blackRectangle.setFillColor(sf::Color(0,0,0,0));
    blackRectangle.setPosition(0,0);
    tAcc = 0;
}

void InitialState::input()
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        startGame = true;
    }
}

void InitialState::draw()
{
    game->renderWindow.draw(splash);
}

void InitialState::update()
{
    if (startGame)
    {
        for (int x = 0; x <= 256; x++)
        {
            blackRectangle.setFillColor(sf::Color(0,0,0,x));
            game->renderWindow.clear();
            //draw();
            game->renderWindow.draw(blackRectangle);
            game->renderWindow.display();
            //std::cout << x << std::endl;
        }
        startGame = false;
        game->changeState(new TestState1(game));
    }
}
