//
// Created by Ziv on 20/06/2021.
//

#ifndef _MEDIC_H
#define _MEDIC_H
#include "Character.h"
namespace mtm {


    class Medic : public Character {
    public:
        Medic(int health,int ammo,int range,int power,Team team,CharacterType type,int ammo_reload=5,int max_steps=5,int ammo_shooting=1);

        ~Medic() =default;

        Medic(const Medic &solider) ;

        Medic &operator=(const Medic &solider);

        void specialAttack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;

        bool isValidMove(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;

        void isAttackValid(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;

        Medic& clone () override;

        void updateAmmo(int ammo) override;


    };
}

#endif //MEDIC_H
