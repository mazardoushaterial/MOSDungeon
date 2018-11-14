#include "testState1.h"
#include <iostream>

TestState1::TestState1(Game* pGame):
    worldMap(pGame)
{
    game = pGame;
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        creature[i].setUp(pGame);
        //creature[i].setPosition(16,16);
        //creature[i].polymorphInto("creatures/wizard.actor");
        creature[i].randomPolymorph();
    }
    //creature[0].polymorphInto("creature/robin.actor");
    //creature[0].setPosition(16,16);
    //creature[0].setWeaponToPlayer();
    //creature[0].weapon.loadWeapon("weapons/boomerang.wep");
    creature[0].setSpeed(2);
    //worldMap.loadMap("currentMap.map");
    mainView.setCenter(game->getWindowWidth()/2,game->getWindowHeight()/2);
    mainView.setSize(game->getWindowWidth(),game->getWindowHeight());
    game->renderWindow.setView(mainView);
    tAcc = 0;
    //worldMap.makeCave();
    worldMap.makeRogueLevel();
    scatterEnemies();
    for (int i = 1; i < MAX_ENEMIES;i++)
    {
        creature[i].setWeaponToPlayer();
        //creature[i].projectile.setTexture(game->resourceManager.projectileTextures);
    }
    waitToPathfind = 0;
    //Set player to the first available slot
    for (int y = 0; y < MAX_Y; y++)
    {
        for (int x = 0; x < MAX_X; x++)
        {
            if (worldMap.tile[y][x] == EMPTY)
            {
                creature[0].setPosition(16*x,16*y);
                creature[0].setWeaponToPlayer();
            }
        }
    }

    cameraX = creature[0].getCenterX();
    cameraY = creature[0].getCenterY();

}

void TestState1::input()
{
    //creature[0].input();
    creature[0].LR = 0; //Did the character move right or down or neither?
    creature[0].UD = 0; //Did the character move Up or Down, or neither?
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))//
    {
        creature[0].move(0,-1*creature[0].getSpeed());
        creature[0].UD = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        creature[0].move(0,1*creature[0].getSpeed());
        creature[0].UD = 2;
    }

    //Collisions
    //Go back if collided
    if (isColliding(creature[0]))
    {
                switch(creature[0].UD)
                {
                case 1:
                    creature[0].moveBack(0,1*creature[0].getSpeed());
                    break;
                case 2:
                    creature[0].moveBack(0,-1*creature[0].getSpeed());
                    break;
                default:
                    break;
                }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))//
    {
        creature[0].move(-1*creature[0].getSpeed(),0);
        creature[0].LR = 1;
    }
    else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        creature[0].move(1*creature[0].getSpeed(),0);
        creature[0].LR = 2;
    }
    //Collisions
    if (isColliding(creature[0]))
    {
                //Go back if collided
                switch(creature[0].LR)
                {
                case 1:
                    creature[0].moveBack(1*creature[0].getSpeed(),0);
                    break;
                case 2:
                    creature[0].moveBack(-1*creature[0].getSpeed(),0);
                    break;
                default:
                    break;
                }
    }


    if (sf::Keyboard::isKeyPressed(sf::Keyboard::X))
    {
        creature[0].weaponAction();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))
    {
        game->renderWindow.close();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Z))
    {
        knockBack(0,creature[0].getFacing());
    }

}

void TestState1::update()
{

    playerHitLogic();
     //If the creature[0] is not on the sides of the map
    if (
        creature[0].getPositionX()+8 < (60*16) - (game->getWindowWidth()/2)
        && creature[0].getPositionX()+8 > (game->getWindowWidth()/2)
        )
    {
        cameraX = creature[0].getPositionX()+8;
    }
    //If the creature[0] is not on the sides of the map
    if (
        creature[0].getPositionY()+8 < (60*16) - (game->getWindowHeight()/2)
        && creature[0].getPositionY()+8 > (game->getWindowHeight()/2)
        )
    {
        cameraY = creature[0].getPositionY()+8;
    }

    mainView.setCenter(cameraX,cameraY);
    game->renderWindow.setView(mainView);

    for (int i = 0; i < MAX_ENEMIES;i++)
    {
        creature[i].increaseTimer();
    }

    //creature[0].weapon.update();
    moveEnemies();

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        creature[i].preventOutOfScreenErrors();
    }

    creature[0].stabbingUpdate();
    creature[0].throwingUpdate();
    creature[0].stab();
    creature[0].shoot();
    throwingCollision();
    creature[0].catchWeapon();
    checkCreatureWeaponPosition(&creature[0]);
    for (int i = 1; i < MAX_ENEMIES; i++)
    {
        creature[i].weaponAction();
        creature[i].stabbingUpdate();
        creature[i].throwingUpdate();
        creature[i].stab();
        creature[i].shoot();
        creature[i].catchWeapon();
        checkCreatureWeaponPosition(&creature[i]);
    }
    worldMap.makeInvisible();
    playerWeaponVsEnemies();
    lineOfSight();
    tempProjectile();
}

void TestState1::draw()
{
    worldMap.draw();
    //creature[0].draw();
    //creature[0].weapon.draw(game->renderWindow);

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        creature[i].weapon.draw(game->renderWindow);
        //draw only if alive
        if (creature[i].isAlive())
        {
            game->renderWindow.draw(creature[i].projectile.sprite);
        }
    }

    drawEnemies();

    //creature[0].weapon.draw(game->renderWindow);
}

void TestState1::throwingCollision()
{
    if (creature[0].weapon.isThrowable())
    {
        //If the weapon hits a wall, then return
        for (int y = 0; y < MAX_Y; y++)
        {
            for (int x = 0; x < MAX_X; x++)
            {
            if ((worldMap.tile[y][x] != 0) &&
                        creature[0].weapon.getCenterX() <= x*16+15 &&
                        creature[0].weapon.getCenterX() >= x*16 &&
                        creature[0].weapon.getCenterY() <= y*16+15 &&
                        creature[0].weapon.getCenterY() >= y*16
                        )
                    {
                        creature[0].weapon.active = false;
                    }
            }
        }
    }
}

//If the weapon is not active, set it to the creature[0]'s position
void TestState1::checkCreatureWeaponPosition(Player * creature)
{
    if (!creature->weapon.active)
    {
        //If it's a melee weapon
        if(!creature->weapon.isReturnable())
        {
            creature->setWeaponToPlayer(); //Instantly sets weapon to creature[0]
        }
        //Return the projectile
        else if(creature->weapon.isReturnable())
        {
            for (int i = 0; i < creature->weapon.getSpeed(); i++)
            {
                //Weapon is to the left of the creature[0]
                if (creature->weapon.getPositionX() < creature->getPositionX())
                {
                    creature->weapon.setPosition(creature->weapon.getPositionX()+1,creature->weapon.getPositionY());
                }
                else if (creature->weapon.getPositionX() > creature->getPositionX()) //"" is to the right
                {
                    creature->weapon.setPosition(creature->weapon.getPositionX()-1,creature->weapon.getPositionY());
                }
                if (creature->weapon.getPositionY() < creature->getPositionY())
                {
                    creature->weapon.setPosition(creature->weapon.getPositionX(),creature->weapon.getPositionY()+1);
                }
                else if (creature->weapon.getPositionY() > creature->getPositionY())
                {
                    creature->weapon.setPosition(creature->weapon.getPositionX(),creature->weapon.getPositionY()-1);
                }
            }
            //Has to return to sender
        }
        //If it's like a boomerang
    }

}

void TestState1::drawEnemies()
{
    //Draw the dead enemies in the background
    //and draw the live ones in the foreground

    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (!creature[i].isAlive())
        {
            game->renderWindow.draw(creature[i].sprite);
        }
    }
    for (int i = 0; i < MAX_ENEMIES; i++)
    {
        if (creature[i].isAlive())
        {
            game->renderWindow.draw(creature[i].sprite);
        }
    }
}

//Cast rays all round the creature[0] (to the borders of the screen)
void TestState1::lineOfSight()
{
    //The creature[0]s X and Y positions in grid form
    int px = (creature[0].getCenterX()-(creature[0].getCenterX()%16))/16;
    int py = (creature[0].getCenterY()-(creature[0].getCenterY()%16))/16;
    int cx = ((int)mainView.getCenter().x-((int)mainView.getCenter().x%16))/16;
    int cy = ((int)mainView.getCenter().y-((int)mainView.getCenter().y%16))/16;

    for (int x = 0; x < 22; x++)
    {
        for (int y = 0; y < 22; y++)
        {
            worldMap.castRay(px,py,(cx-11)+x,(cy-11)+y);
        }
    }

}

void TestState1::spawnEnemies()
{

}

//Spawn enemies randomly around the map
void TestState1::scatterEnemies()
{
    int randX = 0;
    int randY = 0;
    for (int i = 1; i < MAX_ENEMIES; i++)
    {
        do
        {
            randX = game->randInt(60);
            randY = game->randInt(60);
            std::cout << "====" << std::endl;
            std::cout << randX << std::endl;
            std::cout << randY << std::endl;
            creature[i].setPosition(randX*16,randY*16);
        } while (worldMap.tile[randY][randX] != EMPTY);
    }
}

void TestState1::moveEnemies()
{
    for (int i = 1; i < MAX_ENEMIES;i++)
    {
        //If the enemy is dead, don't move
        if (!creature[i].isAlive())
        {
            //do nothing because dead people dont do anything
        }
        else if (distanceBetween(creature[i].getPositionX(),creature[i].getPositionY(),creature[0].getPositionX(),creature[i].getPositionY()) > 320)
        {
            //do nothing because the path is too big
        }
        //If the tile is not visible to the creature[0], then do pathfinding
        else if (!worldMap.visible[creature[i].getGridPositionY()][creature[i].getGridPositionX()])
        {
            enemyPathfindToPlayer(i);
        }
        else //otherwise charge at the creature[0] if he's visible
        {
            bool charge = true;

            //If any tile around the enemy is visible, then still pathfind
            //to prevent getting stuck on walls (Rushing the creature[0] can make
            //enemies get stuck on walls
            for (int x = -1; x <= 1 && charge == true; x++)
            {
                for (int y = -1; y <= 1 && charge == true; y++)
                {
                    //Don't check out of bound tiles
                    if (worldMap.outOfBounds(creature[i].getGridPositionX()+x,creature[i].getGridPositionY()+y))
                    {
                        //out of bounds
                    }
                    //If any tile around the enemy is visible, then still pathfind
                    else if (worldMap.visible[creature[i].getGridPositionY()+y][creature[i].getGridPositionX()+x] == false)
                    {
                        enemyPathfindToPlayer(i);
                        charge = false; //turn off rushing the creature[0]
                    }
                }
            }
            //If the above conditions are not met,
            //then it is safe to rush the creature[0]!
            if (charge == true)
            {
                creature[i].steps = 0; //Stop pathfinding and give the pathfinding a full reset
                enemyGoto(i,creature[0].getCenterX(), creature[0].getCenterY()); //Go to the creature[0]s' grid location
            }
        }


    }
}

void TestState1::enemyGoto(int i,int x, int y)
{
    for (int j = 0; j < creature[i].getSpeed();j++)
    {
        creature[i].UD = 0;
        creature[i].LR = 0;
        if (x < creature[i].getCenterX())
        {
            creature[i].move(-1,0);
            creature[i].LR = 1;
        }
        else if (x > creature[i].getCenterX())
        {
            creature[i].move(1,0);
            creature[i].LR = 2;
        }

        if (isColliding(creature[i]))
        {
                    //Go back if collided
                    switch(creature[i].LR)
                    {
                    case 1:
                        creature[i].moveBack(1,0);
                        break;
                    case 2:
                        creature[i].moveBack(-1,0);
                        break;
                    default:
                        break;
                    }
        }

        if (y < creature[i].getCenterY())
        {
            creature[i].move(0,-1);
            creature[i].UD = 1;
        }
        else if (y > creature[i].getCenterY())
        {
            creature[i].move(0,1);
            creature[i].UD = 2;
        }

        if (isColliding(creature[i]))
        {
                    //Go back if collided
                    switch(creature[i].UD)
                    {
                    case 1:
                        creature[i].moveBack(0,1);
                        break;
                    case 2:
                        creature[i].moveBack(0,-1);
                        break;
                    default:
                        break;
                    }
        }
    }
}

//Colliding with world
bool TestState1::isColliding(Player creature)
{
    //If the creature is dead, don't collide
    for (int y = -1; y <= 1; y++)
    {
        for (int x = -1; x <= 1; x++)
        {
            if ((worldMap.tile[creature.getGridPositionY()+y][creature.getGridPositionX()+x] != 0) &&
                creature.getLeft() <= ((creature.getGridPositionX()+x)*16)+15 &&
                creature.getRight() >= (creature.getGridPositionX()+x)*16 &&
                creature.getTop() <= ((creature.getGridPositionY()+y)*16)+15 &&
                creature.getBottom() >= (creature.getGridPositionY()+y)*16
                )
            {
                return true;
            }
        }
    }
    return false;
}

void TestState1::playerWeaponVsEnemies()
{
    for (int i = 1; i < MAX_ENEMIES; i++)
    {
        if (!creature[i].isAlive())
        {
            //Do nothing
        }
        else if (!creature[0].weapon.active)
        {
            //do nothing
        }
        //If creature collides with weapon's center
        else if (
                creature[i].getLeft() <= creature[0].weapon.getCenterX() &&
                creature[i].getRight() >= creature[0].weapon.getCenterX()  &&
                creature[i].getTop() <= creature[0].weapon.getCenterY()  &&
                creature[i].getBottom() >= creature[0].weapon.getCenterY()
            )
            {
                creature[i].makeDead();
                //creature[i].polymorphInto("wizard.actor");
            }
    }
}

double TestState1::distanceBetween(int x1, int y1, int x2, int y2)
{
    return sqrt(pow(abs(y2-y1),2)+pow(abs(x2-x1),2));
}

void TestState1::enemyPathfindToPlayer(int i)
{
    if (!creature[i].isAlive())
    {
        return;
    }
    if ((creature[i].getCenterX() == (creature[i].getGridPositionX()*16)+8 && creature[i].getCenterY() == (creature[i].getGridPositionY()*16)+8) && creature[i].steps == 0)
            {
                pathfinding.setUpMap(worldMap.tile);
                creature[i].direction = pathfinding.djikstra(creature[i].getGridPositionX(),creature[i].getGridPositionY(),creature[0].getGridPositionX(),creature[0].getGridPositionY());
                creature[i].steps = 16;

                //std::cout << "I AM GETTING A DIRECTION" << std::endl;

            }
            else if (!(creature[i].getCenterX() == (creature[i].getGridPositionX()*16)+8 && creature[i].getCenterY() == (creature[i].getGridPositionY()*16)+8) && creature[i].steps == 0)
            {
                enemyGoto(i,creature[i].getGridPositionX()*16+8,creature[i].getGridPositionY()*16+8);
                //std::cout << "I WANT TO GO TO THE CENTER" << std::endl;
            }
            if (creature[i].steps > 0)
            {

                if (creature[i].direction == 1)
                {
                    //std::cout << (creature[i].getGridPositionX()) << std::endl;
                    //std::cout << (creature[i].getGridPositionY()) << std::endl;
                    //std::cout << "DOWN" << std::endl;
                }
                if (creature[i].direction == 3)
                {
                    //std::cout << (creature[i].getGridPositionX()) << std::endl;
                    //std::cout << (creature[i].getGridPositionY()) << std::endl;
                    // std::cout << "LEFT" << std::endl;
                }
                if (creature[i].direction == 5)
                {
                    //std::cout << (creature[i].getGridPositionX()) << std::endl;
                    //std::cout << (creature[i].getGridPositionY()) << std::endl;
                    // std::cout << "UP" << std::endl;
                }
                if (creature[i].direction == 7)
                {
                    //std::cout << (creature[i].getGridPositionX()) << std::endl;
                    //std::cout << (creature[i].getGridPositionY()) << std::endl;
                    // std::cout << "RIGHT" << std::endl;
                }

                creature[i].steps--;
                if (creature[i].direction == 1)
                {
                    creature[i].move(0,1);
                    //enemyGoto(i,0,creature[i].getCenterY()+1);
                }
                else if (creature[i].direction == 3)
                {
                    creature[i].move(-1,0);
                    //enemyGoto(i,creature[i].getCenterX()-1,0);
                }
                else if (creature[i].direction == 5)
                {
                    creature[i].move(0,-1);
                    //enemyGoto(i,0,creature[i].getCenterY()-1);
                }
                else if (creature[i].direction == 7)
                {
                    creature[i].move(1,0);
                    //enemyGoto(i,creature[i].getCenterX()+1,0);
                }

            }
            //TODO: add pathfinding
            /*
            pathfinding.setUpMap(worldMap.tile);
            int p = pathfinding.djikstra((creature[i].getPositionX()-(creature[i].getPositionX()/16))/16,(creature[i].getPositionY()-(creature[i].getPositionY()/16))/16,creature[0].getGridPositionX(),creature[0].getGridPositionY());

            std::cout << p << std::endl;

            if (p == 1)
            {
                enemyGoto(i,0,creature[i].getCenterY()+1);
            }
            if (p == 3)
            {
                enemyGoto(i,creature[i].getCenterX()-1,0);
            }
            if (p == 5)
            {
                enemyGoto(i,0,creature[i].getCenterY()-1);
            }
            if (p == 7)
            {
                enemyGoto(i,creature[i].getCenterX()+1,0);
            }
            */

            /*switch(p)
            {
                case 0:
                    exit(EXIT_FAILURE);
                break;
                case 1:
                    enemyGoto(i,0,creature[i].getCenterY()+1);
                break;
                case 2:
                    exit(EXIT_FAILURE);
                break;
                case 3:
                    enemyGoto(i,creature[i].getCenterX()-1,0);
                break;
                case 4:
                    exit(EXIT_FAILURE);
                break;
                case 5:
                    enemyGoto(i,0,creature[i].getCenterY()-1);
                break;
                case 6:
                    exit(EXIT_FAILURE);
                break;
                case 7:
                    enemyGoto(i,creature[i].getCenterX()+1,0);
                break;
                case 8:
                    exit(EXIT_FAILURE);
                break;
            }
            */



}

void TestState1::tempProjectile()
{
    /*
    for (int i = 1; i < MAX_ENEMIES;i++)
    {
        if (!creature[i].isAlive())
        {
            //do nothing if dead
        }
        else if (!worldMap.visible[worldMap.convertVoxelToGrid(creature[i].getCenterY())][worldMap.convertVoxelToGrid(creature[i].getCenterX())])
        {
            //do nothing if unseen
            creature[i].projectile.setCenter(creature[i].getCenterX(),creature[i].getCenterY());
            creature[i].resetMagicDowntime();
            creature[i].projectile.sprite.setPosition(creature[i].projectile.getPositionX(),creature[i].projectile.getPositionY());
        }
        else
        {
            if (creature[i].getMagicDowntime() > 60)
            {
                creature[i].projectile.setCenter(creature[i].getCenterX(),creature[i].getCenterY());
                creature[i].projectile.setTrajectory(creature[i].getCenterX(),creature[i].getCenterY(),creature[0].getCenterX(),creature[0].getCenterY());
                creature[i].resetMagicDowntime();
            }
            //not moving
            else if (creature[i].projectile.notMoving())
            {
                //do nothing if unseen
                creature[i].projectile.setCenter(creature[i].getCenterX(),creature[i].getCenterY());
                //creature[i].resetMagicDowntime();
                creature[i].projectile.sprite.setPosition(creature[i].projectile.getPositionX(),creature[i].projectile.getPositionY());
            }
            creature[i].projectile.update();
            creature[i].increaseMagicDowntime();

            //pSprite.setPosition(creature[i].projectile.getPositionX(),creature[i].projectile.getPositionY());
            creature[i].projectile.sprite.setPosition(creature[i].projectile.getPositionX(),creature[i].projectile.getPositionY());
                //std::cout << "X: " << creature[i].projectile.getPositionX() << std::endl;

                //std::cout << "Y: " << creature[i].projectile.getPositionY() << std::endl;

            //mAGIC vs creature[0]
            for (int i = 1; i < MAX_ENEMIES; i++)
            {
                if (!creature[0].isAlive())
                {
                    //Do nothing
                }
                //If creature collides with weapon's center
                else if (
                        creature[0].getLeft() <= creature[i].projectile.getCenterX() &&
                        creature[0].getRight() >= creature[i].projectile.getCenterX()  &&
                        creature[0].getTop() <= creature[i].projectile.getCenterY()  &&
                        creature[0].getBottom() >= creature[i].projectile.getCenterY() &&
                        creature[i].isAlive()
                    )
                    {
                        //creature[0].makeDead();
                        //creature[0].polymorphInto("creatures/starman.actor");
                        creature[0].randomPolymorph();
                    }
            }
        }
    }
    */
}

void TestState1::spawnProjectile(int centerX, int centerY, double vecX, double vecY)
{
    projectile.push_back(Projectile(centerX,centerY,vecX,vecY));
}

//Knockback from something
void TestState1::knockBack(int i, int direction) //URDL
{
    for (int j = 0; j < 16; j++)
    {

        if (direction == 0)
        {
            creature[i].move(0,-1);
        }

        if (direction == 2)
        {
            creature[i].move(0,1);
        }

        //Collisions
        //Go back if collided
        if (isColliding(creature[i]))
        {

                    switch(direction)
                    {
                    case 0:
                        creature[i].moveBack(0,1);
                        break;
                    case 2:
                        creature[i].moveBack(0,-1);
                        break;
                    default:
                        break;
                    }
        }

        if (direction == 1)
        {
            creature[i].move(1,0);
        }
        if (direction == 3)
        {
            creature[i].move(-1,0);
        }

        //Collisions
        if (isColliding(creature[i]))
        {
                    //Go back if collided
                    switch(direction)
                    {
                    case 3:
                        creature[i].moveBack(1,0);
                        break;
                    case 1:
                        creature[i].moveBack(-1,0);
                        break;
                    default:
                        break;
                    }
        }


    }
}
//
void TestState1::playerHitLogic()
{
    for (int i = 1; i < MAX_ENEMIES; i++)
    {
        if (!creature[i].isAlive())
        {
            //do nothing if the creature is dead
        }
        else if (creatureCollision(0,i))
        {
            knockBack(0,creature[i].getFacing());
        }
    }
}

bool TestState1::creatureCollision(int i, int j)
{
    if (
        creature[i].getLeft() <= creature[j].getRight() &&
        creature[i].getRight() >= creature[j].getLeft() &&
        creature[i].getTop() <= creature[j].getBottom() &&
        creature[i].getBottom() >= creature[j].getTop()
        )
    {
        //std::cout << "WE GOTTEM" << std::endl;
        return true;
    }
    return false;
}
