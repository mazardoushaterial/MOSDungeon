#ifndef BOOMERANG_H_INCLUDED
#define BOOMERANG_H_INCLUDED
#include "weapon.h"

class Boomerang: public Weapon
{
public:
    Boomerang();
    Boomerang(sf::Texture &rTexture);
};


#endif // BOOMERANG_H_INCLUDED
