#ifndef PLAYER_H_INCLUDED
#define PLAYER_H_INCLUDED
#include "creature.h"//
#include "knife.h"
#include "boomerang.h"
#include "weapon.h"
enum Items {KNIFE,RIFLE,MG};
class Player: public Creature
{
    public:
        Player();
        Player(Game *pGame);
        void setUp(Game *pGame);
        void input();
        void setWeaponToPlayer();
        void stab();
        void shoot();
        void throwingUpdate();
        void stabbingUpdate();
        void throwingAction();
        void stabbingAction();
        void weaponAction();
        //void returnProjectile();
        int collide(int top, int bottom, int left, int right);
        void catchWeapon();
        Weapon weapon;
    protected:
        //ITEM SLOTS x2
        //1-Knife
        //2-rifle
        //3-machinegun

        int item[2] = {1,0};
        //Data = amount of item
        //1-Bomb
        int inventory[1] = {0};
};

#endif // PLAYER_H_INCLUDED
