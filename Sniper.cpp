//
// Created by Ziv on 20/06/2021.
//

#include "Sniper.h"
#include <cmath>
namespace mtm
{
    Sniper:: Sniper(int health,int ammo,int range,int power,Team team,CharacterType type,int shooting_counter,int ammo_reload,int max_steps,int ammo_shooting): Character(health,ammo,range,power,team,type,ammo_reload,max_steps,ammo_shooting),shooting_counter(shooting_counter) {}
    void Sniper::specialAttack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
     //we're assuming the shot is 100% taken
       board[dest.row][dest.col].get()->updateHealth(power+this->isThirdShot()*power);
       if( board[dest.row][dest.col].get()->getHealth()<=0)
       {
           board[dest.row][dest.col]=nullptr;//haha!! DEATH!
       }
       this->shooting_counter++;
       this->updateAmmo(-ammo_shooting);
       if(ammo<=0){
           ammo=0;
       }
       //nice try;

    }

    bool Sniper::isValidMove(const GridPoint& source,const  GridPoint& dest, std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        return Character::isValidMove(source, dest, board);
    }

    void Sniper::isAttackValid(const GridPoint& source,const  GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {

          int distance=source.distance(source,dest);
           if(!((ceil(distance)<=range)&&(ceil(distance)>=ceil(range/2.0))))
           {
               throw OutOfRange();
           }

           if(ammo==0)
           {
               throw OutOfAmmo();
           }
        if(board[dest.row][dest.col]== nullptr)
        {
            throw IllegalTarget();
        }
        if(this->isSameTeam(*board[dest.row][dest.col].get()))
        {
            throw IllegalTarget();
        }
}



    void Sniper::updateAmmo(int ammo) {
        this->ammo+=ammo;
    }



    Sniper &Sniper::clone() {
        auto sniper_clone=new Sniper(this->health, this->ammo, this->range, this->power, this->team, this->type,this->shooting_counter,this->ammo_reload,this->max_steps,this->ammo_shooting);
        return *sniper_clone;
    }

    bool Sniper::isThirdShot() {

        return ((this->shooting_counter+1)%3==0);
    }
}