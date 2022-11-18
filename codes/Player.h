#ifndef PLAYER_h
#define PLAYER_h

#include <vector>
#include <utility>
#include <string>
#include <memory>

class Piece;
class Board;
class Option;

/* Player Classes */
// A Player can be a:
//  Computer | Human
class Player{
    /* fields */
    int colour;
protected:
    Board * board;                                  // reference to the board
    std::vector<Piece> pieces;                      // pieces owned by the player
    std::vector<Option> options[3];                 // option avaliable to the player
                                                    //  index 0: valid capture moves
                                                    //  index 1: valid peaceful moves
                                                    //  index 2: moves that sell your king!

    /* functions */

public:
    Player(int colour);                                                       // constructor
    ~Player();                                                      // destroctor that does nothing
    void updateStatus();                                            // updates status (check if the player is checked and maybe more)
    void updateMoves();                                             // updates valid moves 
    virtual void move(std::vector<Option> & hist);                  // makes a move and store it into hist
};

class Human: public Player{
public:
    Human(int colour);
    void move(std::vector<Option> & hist) override;
};

class Computer: public Player{
public:
    Computer(int colour);
    void move(std::vector<Option> & hist) override;
};


#endif