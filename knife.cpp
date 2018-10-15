#include "knife.h"
#include <iostream>
Knife::Knife()
{

}

Knife::Knife(sf::Texture &rTexture)
{
    int x = 0;
    int y = 0;
    setTexture(rTexture);
    setVisible(false);
    active = false;
    melee = true;
    throwable = false;
    returnable = false;
    spriteOffsetY = 0;
    name = "knife";
}

