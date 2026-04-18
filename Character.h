
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
        int health; // A threshold to the amount of hit points a unit may take before it no longer is able to participate in the game.
        int ammo;  // An upper bound to the amount of special attacks a unit may perform before being forced to "reload"(=refilling is ammo points)
        int range; // An upper bound to the distance in a board this unit may attack if he spots an enemy unit.
        int power; // the amount of hit points(or damage) the said unit will inflict to each of the enemy units in the map(in it's range), given its attack. 
        Team team; // Specifies the team this unit belongs to.
        CharacterType type; // Specifies what is the type of the character.
        int ammo_reload;//ammo to give you when reload
        int max_steps; // represent an upper bound to the amount of steps a unit can walk in a single direction.
        int ammo_shooting; // specifies the number of ammo points that will be reduced from calling "special attack" function.
        // this number also specifies the minimal number of ammo points that allows a unit to perform its "special attack".
        Character(const int& health, const int& ammo, const int& range,
                  const int& power, const Team& team, const CharacterType& type,
                  const int& ammo_reload=0, const int& max_steps=0, const int& ammo_shooting=0);
    public:

        ~Character() = default; // as there are no memory allocation, no need for explicit deletion.
        Character(const Character &hero) = default; // no explicit memory allocation in consturction implies no need for explicit copy constructor.
        Character &operator=(const Character& hero) = default; // default operator= produced by compiler provides the same functionality.
        //generic functions

        /* function specialAttack- function to set the diffrent effect of attack for each character.
        @param source- the coordinate of the attacker.
        @param dest- the coordinate to attack.
        @param board - the board in which the attack performs it's special attack.
        */
         virtual void specialAttack(const GridPoint& source, const GridPoint &dest ,std::vector<std::vector<std::shared_ptr < Character>>>& board) = 0;

         /* isValidMove - a virtual function that check if the charcter can perform a given move.
         @param source- the coordinate of the charcter.
         @param dest- the coortinate to move.
         @param board- the character to move.
         @return true- the move is valid.
         @return false- if the move is not valid.
         */
         bool isValidMove(const GridPoint &source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board ) const;

         /* isAttackValid- function to check if the attack is valid.
         @param source- the coordinate of the charcter who attack.
         @param dest- the coortinate to attack
         @param board- the character who attack.
         @return true- the attack is valid.
         @return false- if the attack is not valid.
         */
         virtual void isAttackValid(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) const=0;

         /* getUniqueAmmo- a virtual function to get for each character his unique num of ammo when reload.
         */
          int getUniqueAmmo() const;
        //generic getters&&setters getters&setters.

        /* getHealth - function to get the health that the character has.
        */
         int getHealth() const;

         /* getMaxSteps- a function to get the max steps that the character can do.
         */
          int getMaxSteps() const;

         /* updateHealth- a function to update health.
         @param damage- the amount to down when damage made.

         -if damage is less then zero, it means healing
         */
         void updateHealth(const int& damage);

         /* function getAmmo - return the ammo of the character.
         */
         int getAmmo() const;

         /* getRange- function that return the range of the charcter.
         */
         int getRange() const;

         /* updateAmmo - virtual function to update the ammo.
         @param ammo- the amount of ammo to add.
         */
         void updateAmmo(const int& ammo);

         /*
          * getPower- return the power of the charcter.
         */
         int getPower() const;

         /*
         * getTeam- return the type of team.
         */
         Team getTeam() const;
         CharacterType getType() const;
         virtual Character& clone()=0;
        //general functions that will be used within GameClass;

        /* isSameTeam - a boolean function to check if the players in same team.
        @param character - the character to compare.
        @return true- if they in the same team, if not, return false.
        */
        bool isSameTeam(const Character& character) const;


        void move(std::vector<std::vector<std::shared_ptr < Character>>> board,GridPoint dest);

        /* reload- function to reload the ammo.
        */
        void reload();


    };
}
#endif //_CHARACTER_H
