//
// Created by Ziv on 21/06/2021.
//

#include "Character.h"
#include <string>
namespace mtm {
    Character::Character(
    const int& health,
    const int& ammo,
    const int& range,
    const int& power,
    const Team& team,
    const CharacterType& type,
    const int& ammo_reload,
    const int& max_steps,
    const int& ammo_shooting) : health(health), ammo(ammo), range(range),
                                power(power), team(team), type(type),
                                ammo_reload(ammo_reload), max_steps(max_steps),
                                ammo_shooting(ammo_shooting) {
        //here check for illegal stuff
        if (health <= 0 || ammo < 0 || range < 0 || power < 0 ||
            (team !=POWERLIFTERS && team != CROSSFITTERS || (type != MEDIC && type != SOLDIER && type != SNIPER))) {
            throw IllegalArgument();
        }
    }
    
    int Character::getHealth() const {
        return health;
    }
    
    void Character::updateHealth(const int& damage) {
        health -= damage;
    }
    
    int Character::getAmmo() const {
        return ammo;
    }
    int Character::getPower() const {
        return power;
    }

     Team Character::getTeam() const {
        return team;
    }

    void Character::move(std::vector<std::vector<std::shared_ptr < Character>>> board,GridPoint dest) {

    }

    void Character::reload() {
        this->updateAmmo(this->getUniqueAmmo());
    }


    int Character::getUniqueAmmo() const{
        return ammo_reload;
    }

    int Character::getMaxSteps() const {
        return max_steps;
    }
    
    bool Character::isSameTeam(const Character& character) const{
        return (getTeam()==character.getTeam());
    }
    
    int Character::getRange() const{
        return range;
    }

    CharacterType Character::getType() const{
        return type;
    }
    
    bool Character::isValidMove(const GridPoint &source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board ) const
    {
        return true;
    }
    void Character::updateAmmo(const int& ammo) {
        this->ammo += ammo;
    }


}