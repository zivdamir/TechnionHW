//
// Created by Ziv on 20/06/2021.
//

#include "Medic.h"

namespace mtm
{
    Medic::Medic(int health,int ammo,int range,int power,Team team,CharacterType type,int ammo_reload,int max_steps,int ammo_shooting) : Character(health,ammo,range,power,team,type,ammo_reload,max_steps,ammo_shooting) {}

    void Medic::specialAttack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        this->updateAmmo(-ammo_shooting* !isSameTeam(*board[dest.row][dest.col].get()));
        board[dest.row][dest.col].get()->updateHealth(power+(-2*power*this->isSameTeam(*board[dest.row][dest.col].get())));
        if(board[dest.row][dest.col].get()->getHealth()<=0)
        {
            //kill!
            board[dest.row][dest.col]=nullptr;
        }

    }

    bool Medic::isValidMove(const GridPoint& source, const GridPoint& dest, std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        return true;
    } //this shouldn't be virtual! this is totaly generic and can be with everyone.

    void Medic::isAttackValid(const GridPoint& source, const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        //if we're here,meaning we are in valid location
          int distance=source.distance(source,dest);
          if(distance>range) //if we're out of range.
          {
              throw OutOfRange();
          }
          if(this->isSameTeam(*board[dest.row][dest.col].get())==false) //if not the same team,ammo should be used.
          {
              if(ammo<=0)
              {
                  throw OutOfAmmo();
              }
          }
          if(distance==0||board[dest.row][dest.col]==nullptr) //if we try to "attack ourself" or we attack empty cell-its illegal.
          {
              throw IllegalTarget();
          }
//
    }

    Medic::Medic(const Medic &medic): Medic(medic.health,medic.ammo,medic.range,medic.power,medic.team,medic.type) {}

    Medic &Medic::operator=(const Medic &medic) {
        this->health=medic.health;
        this->ammo=medic.ammo;
        this->range=medic.range;
        this->power=medic.power;
        this->team=medic.team;
        this->type=medic.type;
        this->max_steps=medic.max_steps;
        this->ammo_reload=medic.ammo_reload;
        this->ammo_shooting=medic.ammo_shooting;
        return *this;
    }



    Medic &Medic::clone() {
        auto medic_clone=new Medic(this->health, this->ammo, this->range, this->power, this->team, this->type);
        return *medic_clone;
    }

    void Medic::updateAmmo(int ammo) {
        this->ammo+=ammo;
    }


}