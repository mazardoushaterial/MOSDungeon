//#define _GLIBCXX_USE_CXX11_ABI 0
#include "resourceManager.h"
#include <iostream>
#include <SFML/Graphics.hpp>
ResourceManager::ResourceManager()
{
    loadTextures();
}

void ResourceManager::loadTextures()
{
    if (!reubenTextures.loadFromFile("images/Reuben.png"))
    {
        std::cout << "Reuben.png did not load" << std::endl;
    }
    if (!rolfTextures.loadFromFile("images/Rolfie.png"))
    {
        std::cout << "Rolfie.png did not load" << std::endl;
    }
    if (!loadingSplash.loadFromFile("images/loading.png"))
    {
        std::cout << "loading.png did not load" << std::endl;
    }
    if (!tileTextures.loadFromFile("images/tileTextures.png"))
    {
        std::cout << "tileTextures.png did not load" << std::endl;
    }
    if (!weaponTextures.loadFromFile("images/weaponTextures.png"))
    {
        std::cout << "weaponTextures.png did not load" << std::endl;
    }
}
