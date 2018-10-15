#include "state.h"
#include <iostream>
#include "game.h"

#define FRAMERATE 17 //~1/60th of a second

State::State()
{
    tAcc = 0; //time accumulated
}

void State::logic()
{
    //Only when the time threshold is reached should you update
    //the game
    elapsed = clock.restart(); //The time elapsed since last update
    tAcc+=elapsed.asMilliseconds(); //Add the new time it took to update
    //std::cout << "1:" << tAcc << std::endl;


    input();
    update();
    //std::cout << "2:" << tAcc << std::endl;
    draw();
}

//V-Table
void State::update(){};
void State::input(){};
void State::draw(){};
