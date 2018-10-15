#include "boomerang.h"
#include <iostream>
Boomerang::Boomerang()
{

}

Boomerang::Boomerang(sf::Texture &rTexture)
{
    int x = 0;
    int y = 0;
    setTexture(rTexture);
    setVisible(false);
    active = false;
    melee = false;
    throwable = true;
    returnable = true;
    spriteOffsetY = 1;
    name = "boomerang";
}



