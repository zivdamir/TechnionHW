
#ifndef _CHARACTER_H
#define _CHARACTER_H
#include <iostream>
#include "Auxiliaries.h"
#include <memory>
#include <vector>
#include "Exceptions.h"

namespace mtm {
    class Character {
    protected:
        int health;
        int ammo;
        int range;
        int power;
        Team team;
        CharacterType type;
        int ammo_reload;//ammo to give you when reload
        int max_steps;
        int ammo_shooting;//ammo when you shoot,when you shoot ,shoot dont talk.
        Character(int health, int ammo, int range, int power, Team team,CharacterType type, int ammo_reload=0,int max_steps=0,int ammo_shooting=0);
    public:
        ~Character() = default;
        Character(const Character &hero) = default;
        Character &operator=(const Character& hero) = default;
        //generic functions

        /* function specialAttack- function to set the diffrent effect of attack for each character.
        @param source- the coordinate of the attacker.
        @param dest- the coortinate to attack.
        @param board - the character who attack.
        */
         virtual void specialAttack(const GridPoint& source,const GridPoint &dest,std::vector<std::vector<std::shared_ptr < Character>>>& board);

         /* isValidMove - a virtual function that check if the charcter can move.
         @param source- the coordinate of the charcter.
         @param dest- the coortinate to move.
         @param board- the character to move.
         @return true- the move is valid.
         @return false- if the move is not valid.
         */
         virtual bool isValidMove(const GridPoint &source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board );

         /* isAttackValid- function to check if the attack is valid.
         @param source- the coordinate of the charcter who attack.
         @param dest- the coortinate to attack
         @param board- the character who attack.
         @return true- the attack is valid.
         @return false- if the attack is not valid.
         */
         virtual void isAttackValid(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board);

         /* getUniqueAmmo- a virtual function to get for each character his unique num of ammo when reload.
         */
          int getUniqueAmmo();
        //generic getters&&setters getters&setters.

        /* getHealth - function to get the health that the character has.
        */
         int getHealth();

         /* getMaxSteps- a function to get the max steps that the character can do.
         */
          int getMaxSteps();

         /* updateHealth- a function to update health.
         @param damage- the amount to down when damage made.
         -id damage is less then zero, it means healing
         */
         void updateHealth(int damage);

         /* function getAmmo - return the ammo of the character.
         */
         int getAmmo();

         /* getRange- function that return the range of the charcter.
         */
         int getRange() ;

         /* updateAmmo - virtual function to update the ammo.
         @param ammo- the amount of ammo to add.
         */
         virtual void updateAmmo(int ammo)=0;

         /*
          * getPower- return the power of the charcter.
         */
         int getPower();

         /*
         * getTeam- return the type of team.
         */
         Team getTeam();
        CharacterType getType();
         virtual Character& clone()=0;
        //general functions that will be used within GameClass;

        /* attack- a function who call the special attack and make the damage.
        *@param source- the coorinates of the attacker.
        *@param dest- the coordinate to attack.
        *@param - board - the player who attack
        */
        void attack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board);

        /* isSameTeam - a boolean function to check if the players in same team.
        @param character - the character to compare.
        @return true- if they in the same team, if not, return false.
        */
        bool isSameTeam(Character& character);//we cannot pass abstarct cas


        void move(std::vector<std::vector<std::shared_ptr < Character>>> board,GridPoint dest);

        /* reload- function to reload the ammo.
        */
        void reload();


    };
}
#endif //_CHARACTER_H
