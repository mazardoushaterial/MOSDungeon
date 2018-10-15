#ifndef KNIFE_H_INCLUDED
#define KNIFE_H_INCLUDED
#include "weapon.h"
class Knife: public Weapon
{
  public:
      Knife();
      Knife(sf::Texture &rTexture);
};

#endif // KNIFE_H_INCLUDED
