#ifndef RESOURCEMANAGER_H_INCLUDED
#define RESOURCEMANAGER_H_INCLUDED
#include <SFML/Graphics.hpp>
class ResourceManager//
{
    public:
        ResourceManager();
        sf::Texture reubenTextures;
        sf::Texture rolfTextures;
        sf::Texture loadingSplash;
        sf::Texture tileTextures;
        sf::Texture weaponTextures;
    private:
        void loadTextures();
};

#endif // RESOURCEMANAGER_H_INCLUDED
