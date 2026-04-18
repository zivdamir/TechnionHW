//
// Created by Ziv on 20/06/2021.
//

#ifndef _SNIPER_H
#define _SNIPER_H

#include "Character.h"

namespace mtm {
        class Sniper : public Character {
        private:
            int shooting_counter;
        public:
            Sniper(int health, int ammo, int range, int power, Team team,CharacterType type, int shooting_counter = 0,int ammo_reload=2,int max_steps=4,int ammo_shooting=1);

            ~Sniper()  = default;

            Sniper(const Sniper &solider) = default;

            Sniper &operator=(const Sniper &solider) = default;

            void specialAttack(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;

        bool isValidMove(const  GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;

        void isAttackValid(const GridPoint& source,const GridPoint& dest,std::vector<std::vector<std::shared_ptr < Character>>>& board) override;

        void updateAmmo(int ammo) override;
        Sniper& clone () override;

        bool isThirdShot();
    };
}
#endif //SNIPER_H
