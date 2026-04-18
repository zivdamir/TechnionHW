//
// Created by Ziv on 21/06/2021.
//

#include "Character.h"
#include <string>
namespace mtm {
    Character::Character(int health, int ammo, int range, int power, Team team,CharacterType type, int ammo_reload,int max_steps,int ammo_shooting) : health(health), ammo(ammo),
                                                                                          range(range),
                                                                                          power(power), team(team),type(type),ammo_reload(ammo_reload),max_steps(max_steps),ammo_shooting(ammo_shooting) {
        //here check for illegal stuff
        if (health <= 0 || ammo < 0 || range < 0 || power < 0 ||
            (team !=POWERLIFTERS && team != CROSSFITTERS||(type!=MEDIC && type!=SOLDIER &&type != SNIPER))) {
            throw IllegalArgument();
        }
    }

    bool Character::isValidMove(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) { //
        return true;
    }

    int Character::getHealth() {
        return health;//it really doesn't matter
    }
    //the way it works-if i update char with minus damage,its heal(it adds back).
    void Character::updateHealth(int damage) {
        health -= damage;;//it really doesn't do anything
    }

    void Character::specialAttack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        return;
    }

    void Character::isAttackValid(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        return ;
    }

    int Character::getAmmo() {
        return ammo;
    }

    void Character::updateAmmo(int ammo) {
        this->ammo += ammo;
    }

    int Character::getPower() {
        return power;
    }

     Team Character::getTeam() {
        return team;
    }

    void Character::move(std::vector<std::vector<std::shared_ptr < Character>>> board,GridPoint dest) {

    }

    void Character::attack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        specialAttack(source,dest,board);
        //in special attack we will implement ammo change.
        //else throw exception nonlegal
    }

    void Character::reload() {
        this->updateAmmo(this->getUniqueAmmo());
    }


    int Character::getUniqueAmmo() {
        return ammo_reload;
    }

    int Character::getMaxSteps() {
        return max_steps;
    }
   //returns 1 if sameteam,returns 0 if not.
    bool Character::isSameTeam(Character& character) {
        {
            return (getTeam()==character.getTeam());
        }
    }
    int Character::getRange() {
        return range;
    }

    CharacterType Character::getType() {
        return type;
    }


}