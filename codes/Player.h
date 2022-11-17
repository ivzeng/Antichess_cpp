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
protected:
    int status;                                     // status of the player: 1: normal, 2: checked, ...
    Player * opponent;                              // reference to the opponent
    Board * board;                                  // reference to the board
    std::vector<std::unique_ptr<Piece>> pieces;     // pieces owned by the player

    /* functions */

public:
    Player();                                                       // constructor
    ~Player();                                                      // destroctor that does nothing
    void updateStatus();                                            // updates status (check if the player is checked, notify any unmovable peices)
    void updateMoves();                                             // updates valid moves 
    virtual void move(std::vector<Option> & hist); // makes a move and store it into hist
};

class Human: public Player{
public:
    void move(std::vector<Option> & hist) override;
};

class Computer: public Player{
public:
    void move(std::vector<Option> & hist) override;
};


#endif