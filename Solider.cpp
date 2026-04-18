//
// Created by Ziv and Boozi on 20/06/2021.
//

#include "Solider.h"
#include <cmath>
namespace mtm
{

    Solider::Solider(int health,int ammo,int range,int power,Team team,CharacterType type,int ammo_reload,int max_steps,int ammo_shooting):Character(health,ammo,range,power,team,type,ammo_reload,max_steps,ammo_shooting) {}

    Solider::~Solider() =default ;

    Solider::Solider(const Solider &solider)=default;

    void Solider::specialAttack(const GridPoint& source,const GridPoint& destination, std::vector<std::vector<std::shared_ptr < Character>>>& board) {


             for(int i=0;i<board.size();i++)
              {
                 for(int j=0;j<board[i].size();j++)
                 {
                     int distance=source.distance(destination,GridPoint(i,j));
                     if(board[i][j]!=nullptr) {
                         if (distance <= ceil((double)((double)this->getRange() / (double )3)) ){
                             if (distance == 0) {
                                 board[i][j].get()->updateHealth(this->getPower() * (!this->isSameTeam(*board[i][j].get())));
                                 if(board[i][j].get()->getHealth()<=0)
                                 {
                                     board[i][j]=nullptr;//KILL! HAHAHAHA
                                 }
                             }
//                             if(board[0][0]!= nullptr)
//                                 std::cout<<board[0][0].get()->getHealth()<<"is the hp of [0][0] and he's solider?"<<(board[0][0].get()->getType()==SOLDIER)<<std::endl;
                             else{
                                 board[i][j].get()->updateHealth((ceil((double)this->getPower()/2)) * !this->isSameTeam(*board[i][j].get()));
                                 if(board[i][j].get()->getHealth()<=0)
                                 {
                                     board[i][j]=nullptr;//KILL! HAHAHAHA

                                 }
                             }
                         }
                     }
                 }
              }
        updateAmmo(-this->ammo_shooting);//:) ALOT OF DAMAGE FOR NOT ALOT OF AMMO LMAO
        if(getAmmo()<=0) {
            this->ammo=0;
        }//incase u guys want to change the definitions :-),nice try boiz
    }

    bool Solider::isValidMove(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        return true;
    }
    void Solider::isAttackValid(const GridPoint& source, const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) {
        int distance=source.distance(source,dest);
        if(distance>range)
        {
            throw OutOfRange();
        }
        if(ammo<=0) {
            throw OutOfAmmo();
        }
        if(source.col!=dest.col&&source.row!=dest.row)
        {
            throw IllegalTarget();
        }
    }



    Solider &Solider::operator=(const Solider &solider) {
        if(this==&solider)
        {
            return *this;
        }
        this->health=solider.health;
        this->ammo=solider.ammo;
        this->power=solider.power;
        this->type=solider.type;
        this->team=solider.team;
        this->range=solider.range;
        this->ammo_reload=solider.ammo_reload;
        this->max_steps=solider.max_steps;
        this->ammo_shooting=solider.ammo_shooting;
        return *this;
    }

    Solider &Solider::clone() {
        auto soldier_clone=new Solider(this->health,this->ammo,this->range,this->power,this->team,this->type,this->ammo_reload,this->max_steps,this->ammo_shooting);
        return *soldier_clone;
    }

    void Solider::updateAmmo(int ammo) {
        this->ammo+=ammo;
    }


}