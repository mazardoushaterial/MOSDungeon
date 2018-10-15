//#define _GLIBCXX_USE_CXX11_ABI 0
#include "game.h"
Game::Game():
    WINDOW_WIDTH(20*16),
    WINDOW_HEIGHT(16*16)//,
    //mapHandler(this)
{
    changeState(new InitialState(this));
    renderWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"MOSATRON 1977",sf::Style::Default);
    renderWindow.setFramerateLimit(60);
    //renderWindow.setPosition(sf::Vector2i(0,0));
    //renderWindow.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height));
    renderWindow.setSize(sf::Vector2u(WINDOW_WIDTH*3,WINDOW_HEIGHT*3));
    //renderWindow.setVerticalSyncEnabled(true);

    //note: the following would be ....width/2)-WINDOW_WIDTH*2/2 because of the multiple on the new
    //screen size, but 2 cancels itself out.
    //renderWindow.setFramerateLimit(60);
}

void Game::changeState(State* nState)
{
    state = nState;
}

void Game::mainGameLoop()
{
    // The main loop - ends as soon as the window is closed
    while (renderWindow.isOpen())
    {
       // Event processing
       sf::Event event;
       while (renderWindow.pollEvent(event))
       {
           // "close requested" event: we close the window
            switch (event.type)
            {
                case sf::Event::Closed:
                renderWindow.close();
                break;
            }
       }
        /*
       if(sf::Keyboard::isKeyPressed(sf::Keyboard::F5))
       {
            renderWindow.create(sf::VideoMode(WINDOW_WIDTH,WINDOW_HEIGHT),"",sf::Style::None);
            renderWindow.setPosition(sf::Vector2i(0,0));
            renderWindow.setSize(sf::Vector2u(sf::VideoMode::getDesktopMode().width,sf::VideoMode::getDesktopMode().height));
       }
       */

       //
       // Clear the whole window before rendering a new frame
       renderWindow.clear(sf::Color(58,180,109,255));


       state->logic();
       //renderWindow.draw(sFade);

       // End the current frame and display its contents on screen
       renderWindow.display();
    }
}

int Game::getWindowWidth()
{
    return WINDOW_WIDTH;
}

int Game::getWindowHeight()
{
    return WINDOW_HEIGHT;
}
