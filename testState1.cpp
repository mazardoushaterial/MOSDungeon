#include "testState1.h"
#include <iostream>

TestState1::TestState1(Game* pGame):
    player(pGame),
    worldMap(pGame)
{
    game = pGame;
    for (int i = 0; i < 25; i++)
    {
        enemy[i].setUp(pGame);
        enemy[i].setPosition(16,16);
    }

    player.setPosition(16,16);
    player.setWeaponToPlayer();
    worldMap.loadMap("currentMap.map");
    mainView.setCenter(game->getWindowWidth()/2,game->getWindowHeight()/2);
    mainView.setSize(game->getWindowWidth(),game->getWindowHeight());
    game->renderWindow.setView(mainView);
    tAcc = 0;
    cameraX = game->getWindowWidth()/2;
    cameraY = game->getWindowHeight()/2;
    worldMap.makeCave();
}

void TestState1::input()
{
    //player.input();
    int LR = 0; //Did the character move right or down or neither?
    int UD = 0; //Did the character move Up or Down, or neither?
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//
    {
        player.move(0,-1*player.getSpeed());
        UD = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player.move(0,1*player.getSpeed());
        UD = 2;
    }

    //Collisions
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if ((worldMap.tile[y][x] != 0) &&
                player.getLeft() <= x*16+15 &&
                player.getRight() >= x*16 &&
                player.getTop() <= y*16+15 &&
                player.getBottom() >= y*16
                )
            {
                //Go back if collided
                switch(UD)
                {
                case 1:
                    player.moveBack(0,1*player.getSpeed());
                    break;
                case 2:
                    player.moveBack(0,-1*player.getSpeed());
                    break;
                default:
                    break;
                }

            }
        }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//
    {
        player.move(-1*player.getSpeed(),0);
        LR = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player.move(1*player.getSpeed(),0);
        LR = 2;
    }
    //Collisions
    for (int y = 0; y < 60; y++)
    {
        for (int x = 0; x < 60; x++)
        {
            if ((worldMap.tile[y][x] != 0) &&
                player.getLeft() <= x*16+15 &&
                player.getRight() >= x*16 &&
                player.getTop() <= y*16+15 &&
                player.getBottom() >= y*16
                )
            {
                //Go back if collided
                switch(LR)
                {
                case 1:
                    player.moveBack(1*player.getSpeed(),0);
                    break;
                case 2:
                    player.moveBack(-1*player.getSpeed(),0);
                    break;
                default:
                    break;
                }

            }
        }
    }

        //If the player is not on the sides of the map
        if (
            player.getPositionX()+8 < (60*16) - (game->getWindowWidth()/2)
            && player.getPositionX()+8 > (game->getWindowWidth()/2)
            )
        {
            cameraX = player.getPositionX()+8;
        }
        //If the player is not on the sides of the map
        if (
            player.getPositionY()+8 < (60*16) - (game->getWindowHeight()/2)
            && player.getPositionY()+8 > (game->getWindowHeight()/2)
            )
        {
            cameraY = player.getPositionY()+8;
        }
    mainView.setCenter(cameraX,cameraY);
    game->renderWindow.setView(mainView);

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        player.weaponAction();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        game->renderWindow.close();
    }

}

void TestState1::update()
{
    //player.weapon.update();
    player.stabbingUpdate();
    player.throwingUpdate();
    player.stab();
    player.shoot();
    throwingCollision();
    player.catchWeapon();
    checkPlayerWeaponPosition();
    worldMap.makeInvisible();
    lineOfSight();
}

void TestState1::draw()
{
    worldMap.draw();
    player.draw();
    drawEnemies();
    player.weapon.draw(game->renderWindow);
    //player.weapon.draw(game->renderWindow);
}

void TestState1::throwingCollision()
{
    //If the weapon hits a wall, then return
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
        if ((worldMap.tile[y][x] != 0) &&
                    player.weapon.getCenterX() <= x*16+15 &&
                    player.weapon.getCenterX() >= x*16 &&
                    player.weapon.getCenterY() <= y*16+15 &&
                    player.weapon.getCenterY() >= y*16
                    )
                {
                    player.weapon.active = false;
                }
        }
    }
}

//If the weapon is not active, set it to the player's position
void TestState1::checkPlayerWeaponPosition()
{
    if (!player.weapon.active)
    {
        //If it's a melee weapon
        if(!player.weapon.isReturnable())
        {
            player.setWeaponToPlayer(); //Instantly sets weapon to player
        }
        //Return the projectile
        else if(player.weapon.isReturnable())
        {
            for (int i = 0; i < player.weapon.getSpeed(); i++)
            {
                //Weapon is to the left of the player
                if (player.weapon.getPositionX() < player.getPositionX())
                {
                    player.weapon.setPosition(player.weapon.getPositionX()+1,player.weapon.getPositionY());
                }
                else if (player.weapon.getPositionX() > player.getPositionX()) //"" is to the right
                {
                    player.weapon.setPosition(player.weapon.getPositionX()-1,player.weapon.getPositionY());
                }
                if (player.weapon.getPositionY() < player.getPositionY())
                {
                    player.weapon.setPosition(player.weapon.getPositionX(),player.weapon.getPositionY()+1);
                }
                else if (player.weapon.getPositionY() > player.getPositionY())
                {
                    player.weapon.setPosition(player.weapon.getPositionX(),player.weapon.getPositionY()-1);
                }
            }
            //Has to return to sender
        }
        //If it's like a boomerang
    }

}

void TestState1::drawEnemies()
{
    for (int i = 0; i < 25; i++)
    {
        if (enemy[i].isAlive())
        {
            game->renderWindow.draw(enemy[i].sprite);
        }
    }
}

//Cast rays all round the player (to the borders of the screen)
void TestState1::lineOfSight()
{
    //The players X and Y positions in grid form
    int px = (player.getCenterX()-(player.getCenterX()%16))/16;
    int py = (player.getCenterY()-(player.getCenterY()%16))/16;

    for (int x = 0; x < 22; x++)
    {
        for (int y = 0; y < 22; y++)
        {
            worldMap.castRay(px,py,(px-11)+x,(py-11)+y);
        }
    }

}
