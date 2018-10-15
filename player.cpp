#include "player.h"
#include "game.h"

Player::Player()
{

}

Player::Player(Game *pGame)
{
    setUp(pGame);
}

void Player::setUp(Game *pGame)
{
    game = pGame; //Set the pointer to the current game
    //weapon = new Boomerang(game->resourceManager.weaponTextures);
    weapon.loadWeapon("weapons/boomerang.wep");
    weapon.setTexture(game->resourceManager.weaponTextures);
    //weapon = new Knife(game->resourceManager.weaponTextures);
    //weapon = new Knife(pGame);
    sprite.setTexture(game->resourceManager.rolfTextures);
    sprite.setPosition(this->x,this->y);
    sprite.setTextureRect(sf::IntRect(0,0,16,16));
    setWeaponToPlayer();
    health = 1;
    speed = 1;
}

void Player::input()
{}

void Player::setWeaponToPlayer() //fairly obvious
{
    weapon.setPosition(this->x,this->y);
    weapon.sprite.setPosition(weapon.getPositionX(),weapon.getPositionY());
}

void Player::weaponAction()
{
    //URDL
    //For the weapons direction vector
    if (!weapon.active)
    {
        switch(facing)
        {
        case 0:
            weapon.setVector(0,-1);break;
        case 1:
            weapon.setVector(1,0);break;
        case 2:
            weapon.setVector(0,1);break;
        case 3:
            weapon.setVector(-1,0);break;
        }
    }
    //What the weapon does TODO: DELETE THIS AFTER DATA-CENTRIC PARADIGM
    //weapon.action();
    if (weapon.isMelee())
    {
        stabbingAction();
    }
    if (weapon.isThrowable())
    {
        throwingAction();
    }
}

void Player::stabbingAction()
{
    //Knife is not active...
    if (!weapon.active)
    {
        if (weapon.getTimeElapsed() > weapon.getDownTime()) //and we've waited for a second...
        {
            //THEN STAB!
            weapon.setVisible(true);
            weapon.active = true;
            weapon.resetElapsedTime();
            std::cout << "stab" << std::endl;
        }
    }
}

void Player::stabbingUpdate()
{
    //Stabbing takes only one second, then it shuts off.
    if (weapon.active)
    {
        if (weapon.getTimeElapsed() > weapon.getActionTime())
        {
            weapon.setVisible(false);
            weapon.active = false;
            weapon.resetElapsedTime();

            std::cout << "stop" << std::endl;
        }
    }
}

void Player::throwingAction()
{
    //Knife is not active...
    if (!weapon.active && weapon.getTimeElapsed() > weapon.getDownTime())
    {
        //TODO: ADD A FUNCTION TO ONLY LET THE PLAYER THROW WHEN THE BOOMERANG IS IN HIS HAND [fixed]
        if (collide(weapon.getPositionY()+8,weapon.getPositionY()+8,weapon.getPositionX()+8,weapon.getPositionX()+8)) //and we've waited for a 'x' time...
        {
            //THEN throw!
            weapon.setVisible(true);
            weapon.active = true;
            weapon.resetElapsedTime();
            //stopReturning();
            std::cout << "throw" << std::endl;
        }
    }
}

void Player::throwingUpdate()
{
    //throwing takes only 'x' time, then it shuts off.
    if (weapon.active)
    {
        //It's maximum limit in the forward direction is 800ms
        if (weapon.getTimeElapsed() > weapon.getActionTime())
        {
            //setVisible(false);
            weapon.active = false;
            weapon.resetElapsedTime();
            //goBack();
            //startReturning();
            std::cout << "go back" << std::endl;
        }
        else
        {
            std::cout << "flying" << std::endl;
            //keep it moving forward
        }
    }

    //Put animation here:
    if (weapon.getTimeElapsed()%400 > 300)
    {
        weapon.sprite.setTextureRect(sf::IntRect(16,weapon.spriteOffsetY*16,16,16));
    }
    else if (weapon.getTimeElapsed()%400 > 200)
    {
        weapon.sprite.setTextureRect(sf::IntRect(16*1,weapon.spriteOffsetY*16,16,16));
    }
    else if (weapon.getTimeElapsed()%400 > 100)
    {
        weapon.sprite.setTextureRect(sf::IntRect(16*2,weapon.spriteOffsetY*16,16,16));
    }
    else if (weapon.getTimeElapsed()%400 > 0)
    {
        weapon.sprite.setTextureRect(sf::IntRect(16*3,weapon.spriteOffsetY*16,16,16));
    }
}



void Player::stab()
{
    //std::cout << facing << std::endl;
    if (weapon.isMelee() && weapon.active)
    {
        weapon.sprite.setTextureRect(sf::IntRect(facing*16,weapon.spriteOffsetY*16,16,16));
        //0123-URDL
        if (facing == 0)
        {
            //weapon.setTarget(getCenterX(),getCenterY()-16);
            weapon.setPosition(getPositionX(),getPositionY()-8);
        }
        else if (facing == 1)
        {
            //weapon.setTarget(getCenterX()+16,getCenterY());
            weapon.setPosition(getPositionX()+8,getPositionY());
        }
        else if (facing == 2)
        {
            //weapon.setTarget(getCenterX(),getCenterY()+16);
            weapon.setPosition(getPositionX(),getPositionY()+8);
        }
        else
        {
            //weapon.setTarget(getCenterX()-16,getCenterY());
            weapon.setPosition(getPositionX()-8,getPositionY());
        }
    }
}

void Player::shoot()
{
    //Thrown Projectile
    if (weapon.isThrowable() && weapon.active)
    {
        //Move weapon 'i' times per frame
        for (int i = 0; i < weapon.getSpeed(); i++)
        {
            weapon.setPosition(weapon.getPositionX()+weapon.getVecX(),weapon.getPositionY()+weapon.getVecY());
        }
    }
}

void Player::catchWeapon()
{
    //This weapon is throwable
    if (weapon.isThrowable())
    {
        //UDLR
        if (!weapon.active && collide(weapon.getCenterY(),weapon.getCenterY(),weapon.getCenterX(),weapon.getCenterX()))
            {
                weapon.setVisible(false);
                setWeaponToPlayer();
            }
        else
        {
            weapon.setVisible(true);
        }
    }
}

int Player::collide(int top, int bottom, int left, int right)
{
    if (
            getTop() <= top  &&
            getBottom() >= bottom &&
            getLeft() <= left &&
            getRight() >= right
        )
        return true;
    else
        return false;
}
