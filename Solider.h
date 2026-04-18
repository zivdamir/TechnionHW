//
// Created by Ziv on 20/06/2021.
//

#ifndef _SOLIDER_H
#define _SOLIDER_H
#include "Character.h"
#include <cmath>
namespace mtm {


    class Solider : public Character {
    public:
        Solider(int health,int ammo,int range,int power,Team team,CharacterType type,int ammo_reload=3 ,int max_steps=3  ,int ammo_shooting=1);
        ~Solider() ;
        Solider(const Solider &solider);
        Solider &operator=(const Solider &solider);
        void specialAttack(const GridPoint& source,const GridPoint& destination, std::vector<std::vector<std::shared_ptr < Character>>>& board) override;
        bool isValidMove(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;
        void isAttackValid(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;
        void updateAmmo(int ammo) override;
        Solider& clone () override;
    };
}

#endif //EX2PARTB_SOLIDER_H
