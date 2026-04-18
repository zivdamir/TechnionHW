#include <iostream>
#include "Character.h"
#include "Game.h"
#include "Auxiliaries.h"
#include "Sniper.h"
#include "Medic.h"
#include "Solider.h"
#include "Exceptions.h"
#include <memory>
#include <vector>

namespace mtm {

    Game::Game(int height, int width) : row_size(height), col_size(width) {

        board.resize(height, std::vector<std::shared_ptr< Character>>
        (width, std::shared_ptr<Character>(nullptr)));
        char_arr.resize(height*width,' ');
    }

    Game::~Game() {}

//copy constrctor
    Game::Game(const Game &other) : Game(other.row_size, other.col_size) {

        // check for board size (board.size should return the number of rows)
        for (int i = 0; i < other.row_size; i++) {
            for (int k = 0; k < other.col_size; k++) {
                if(other.board[i][k]!=nullptr)
                {
                std::shared_ptr<Character> temp(&other.board.at(i).at(k).get()->clone());
                board.at(i).at(k) = temp;
                char_arr[i*col_size+k]=convertToChar(temp);
                }
                else
                {
                    board[i][k]=nullptr;
                    char_arr[i*col_size+k]=' ';
                }
            }
        }

    }

    Game& Game:: operator=(const Game& other){
        this->board.resize(other.board.size());
        this->char_arr.resize(other.char_arr.size());
        this->row_size=other.row_size;
        this->col_size=other.col_size;
         for (int i = 0; i < other.row_size; i++) {
             this->board.at(i).resize(other.row_size);
            for (int k = 0; k < other.col_size; k++) {
                if(other.board[i][k]!=nullptr)
                {
                std::shared_ptr<Character> temp(&other.board[i][k].get()->clone());
                board[i][k]=nullptr;
                board.at(i).at(k) = temp;
                char_arr[i*col_size+k]=convertToChar(temp);
                }
                else{
                    board[i][k]=nullptr;
                    char_arr[i*col_size+k]=' ';
                }
            }
        }
        return *this;
    }

    void Game::addCharacter(const GridPoint &coordinates, std::shared_ptr<Character> character) {

        if (isLocationValid(coordinates) == false) {
            throw IllegalCell();
        }
        if (board.at(coordinates.row).at(coordinates.col) != NULL) {
            throw CellOccupied();
        }
        
        this->board.at(coordinates.row).at(coordinates.col) = character;
        int board_size=board.size();
        this->char_arr[coordinates.row*col_size+coordinates.col]=convertToChar(character);
        this->updateCharArray();
    }

    std::shared_ptr<Character> Game::makeCharacter
            (CharacterType type, Team team, units_t health, units_t ammo, units_t range, units_t power) {

        //checks
        if (health <= 0 || ammo < 0 || range < 0 || power < 0)
            throw IllegalArgument(); //
       switch(type)
       {
           case(SNIPER):
               return std::shared_ptr<Character>(new Sniper(health,ammo,range,power,team,type));
           case(MEDIC):
               return std::shared_ptr<Character>(new Medic(health,ammo,range,power,team,type));
           case(SOLDIER):
               return std::shared_ptr<Character>(new Solider(health,ammo,range,power,team,type));
            default:
               throw IllegalArgument();
       }
//        return std::shared_ptr<Character>(new Typed_Character(team, health, ammo, range, power));
    }

    void Game::move(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {

        if (isLocationValid(dst_coordinates) == false||isLocationValid(src_coordinates) == false) {
            throw IllegalCell();
        }
        if(this->board[src_coordinates.row][src_coordinates.col]== nullptr)
        {
            throw CellEmpty();
        }
        int steps_range = board[src_coordinates.row][src_coordinates.col]->getMaxSteps();
        int distance = src_coordinates.distance(src_coordinates, dst_coordinates);
        if (distance > steps_range)
        {
            throw MoveTooFar();
        }

        if (this->board[dst_coordinates.row][dst_coordinates.col] != nullptr)
        {
            throw CellOccupied();
        }

        //make the move.
        //call the copy constructor for charcater :
        std::shared_ptr <Character> temp = board[src_coordinates.row][src_coordinates.col];
        board[dst_coordinates.row][dst_coordinates.col] = temp;
        board[src_coordinates.row][src_coordinates.col] = nullptr; //std::nullptr.
        int board_size=board.size();
        char current_char=char_arr[src_coordinates.row*col_size+src_coordinates.col];
        char_arr[src_coordinates.row*col_size+src_coordinates.col]=' ';
        char_arr[dst_coordinates.row*col_size+dst_coordinates.col]=current_char;
        this->updateCharArray();
    }

    void Game::attack(const GridPoint &src_coordinates, const GridPoint &dst_coordinates) {

        if(isLocationValid(src_coordinates) == false || isLocationValid(dst_coordinates)==false)
            throw IllegalCell();

        if(this->board[src_coordinates.row][src_coordinates.col]==nullptr)
            throw CellEmpty();

               board[src_coordinates.row][src_coordinates.col].get()->isAttackValid(src_coordinates,dst_coordinates,this->board);

        //need to add one more check here.

        //ATTACK !    
            board[src_coordinates.row][src_coordinates.col].get()->attack(src_coordinates,dst_coordinates,this->board);
            this->updateCharArray();
    }

    void Game::reload(const GridPoint &coordinates) {

        if (isLocationValid(coordinates)==false)
            throw IllegalCell();
        if(this->board[coordinates.row][coordinates.col]==nullptr)
            throw CellEmpty();
        this->board[coordinates.row][coordinates.col].get()->reload();
    }

    std::ostream& operator<<(std::ostream& os ,const Game &other){

        

        //char* end= &char_arr[char_arr.size()-1];
        return printGameBoard(os,&other.char_arr[0],&other.char_arr[other.char_arr.size()],other.col_size);

    }
    bool Game::isOver(Team *winningTeam = NULL) const {

        int powerlifters_cnt=0;
        int Crossfitters_cnt=0;

         for (int i = 0; i < this->row_size; i++) {
            for (int k = 0; k < this->col_size; k++) {
                {
                    if(board[i][k]!=nullptr) {
                        if (board[i][k].get()->getTeam() == CROSSFITTERS) {
                            Crossfitters_cnt++;
                        }
                        if (board[i][k].get()->getTeam() == POWERLIFTERS) {
                            powerlifters_cnt++;
                        }
                    }
                }
            }
         }// end of for
        if(Crossfitters_cnt==0 && powerlifters_cnt ==0)
        {
            return false;
        }
        if(Crossfitters_cnt==0)
         {
             if(winningTeam!= NULL)
             {
                 *winningTeam=POWERLIFTERS;
             }
            return true;
         }
         if(powerlifters_cnt==0)
         {
             if(winningTeam != NULL)
             {
                 *winningTeam=CROSSFITTERS;
             }
            return true;
         }
        
        return false;

    }

    bool Game::isLocationValid(const GridPoint& point) {
        return (point.row >= 0 && point.row < this->row_size && point.col >= 0 && point.col <  this->col_size);
    }

    char Game::convertToChar(std::shared_ptr <Character> character)
    {
        if(character.get()->getType()==SOLDIER)
        {
            if(character.get()->getTeam()==POWERLIFTERS)
                return 'S';
            return 's';
        }

        if(character.get()->getType()==MEDIC)
        {
            if(character.get()->getTeam()==POWERLIFTERS)
                return 'M';
            return 'm';
        }

        if(character.get()->getType()==SNIPER)
        {
            if(character.get()->getTeam()==POWERLIFTERS)
                return 'N';
            return 'n';
        }
        return ' ';
    }

    int Game::calculateDistance(const GridPoint& p1, const GridPoint& p2) {
        int x = p1.row - p2.row;
        if (x < 0)
            x = x * -1;
        int y = p1.col - p2.col;
        if (y < 0)
            y = y * -1;

        return x + y;
    }

    void Game::updateCharArray() {
        for (int i = 0; i < this->row_size; i++) {
            for (int k = 0; k < this->col_size; k++) {
                if(this->board[i][k]!=nullptr)
                {
                    std::shared_ptr<Character> temp(&this->board.at(i).at(k).get()->clone());
                    char_arr[i*col_size+k]=convertToChar(temp);

                }
                else
                {
                    char_arr[i*col_size+k]=' ';
                }
            }
        }

    }

}






