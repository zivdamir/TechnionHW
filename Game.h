//
// Created by Ziv on 21/06/2021.
//
#include <iostream>
#include "Character.h"
#include "Auxiliaries.h"
#include "Sniper.h"
#include "Medic.h"
#include "Solider.h"
#include <iostream> 
#include <memory> 
#include <vector>
#ifndef GAME_H
#define GAME_H
namespace mtm {
    class Game {
    private:
        int row_size;
        int col_size;
        std::vector<std::vector<std::shared_ptr < Character>>> board;
        std::vector<char> char_arr;
        bool isLocationValid(const GridPoint& point);
        int calculateDistance(const GridPoint& p1,const GridPoint& p2);
        char convertToChar(std::shared_ptr <Character> character);
        void updateCharArray();

    public:
        /* A constrctor of Game
        *Creating a new board of game
        @param height- the size of rows of our board
        @param width- the size of column
        @throw "illegalArgument" if one of the parameter is negative.
        */
        Game(int height, int width);

        /*
            Disrtuctor of game
        */
        ~Game();

        /*CopyConstructor of Game
        @param Game - the game that we copied.
        */
        Game(const Game &other); //copy constructor

        /*operator= : Comparing Game to Game and check if equal.
        @param other- the game to compare with.
        */
        Game &operator=(const Game &other);

        /*addCharacter - A function to add a Character to the board.
        @param - coorinates - the coorinate to add the character on the board.
        @param character- the character to add.
        @throw IllegalCell - if the coorindate out of board.
        @throw CellOccupied - if the cell already exist a character.
        */
        void addCharacter(const GridPoint &coordinates, std::shared_ptr <Character> character);

        

        /*makeCharacter- a function to create a new character.
        @param type- the type of the character : sildier/sniper/medic
        @param team- the team : Crosslifters or PowerLifters.
        @param health - the health points that the character start with.
        @param ammo- the cmount of ammo that the character start with.
        @param range- the range of attacks for tha character.
        @param power- the amount of damage the character can do.
        @throw IllegalArgument - if one of the parameters are ngative.
        @return - shared_ptr to the character.
        */
        static std::shared_ptr <Character> makeCharacter(CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power);

        /* move- a function to the move the character in our board.
        @param src_coordinates - from where to move the character.
        @param dst_coordinates - to where to move.
        @throw IllegalCell- if one of the coordinate cross the boards.
        @throw CelEmpty- if src_coordinates is empty.
        @throw MoveTooFar - if the distance to move bigger then the range move of the character.
        @throw CellOccupies - if dst_coordinate already include other character
        @return void.
        */
        void move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);


        /*attack - function that make the attack .
        @param src_coordinates - from where to attack the character.
        @param dst_coordinates - to where attack.
        @throw IllegalCell- if one of the coordinate cross the boards.
        @throw CelEmpty- if src_coordinates is empty.
        @throw OutOfRamge- if dst_coorindate out of the range that the character can attack.
        @throw OutOfAmmo - if the character has no enogh ammo.
        @throw IllegalTarget - if the attack cannot make from other reson.
        @return void.
        */
        void attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates);


        /* reload- a function to realod the character ammo's.
        @param coordinate- the coordinate of the character to update ammo.
        @throw IllegalCell- if one of the coordinate cross the boards.
        @throw CelEmpty- if src_coordinates is empty.
        */
        void reload(const GridPoint &coordinates);

        /*opertator << - a operator to print the board.
        @param os- the os stream to print the board.
        @param &other - the game to print.
        */
        friend std::ostream& operator<<(std::ostream& os ,const Game &other);

        /* isOver- check if there is a winning.
        @param *winningTeam - a type of Team to save there the name of the winning team.
        @return true- if only one tram stay in the game.
        @return false- if there so players from the 2 teams or there is still a players from the two teams.
        */
        bool isOver(Team *winningTeam) const;


    };

}
#endif //GAME_CPP_GAME_H
