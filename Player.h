#ifndef PLAYER_h
#define PLAYER_h

#include <vector>
#include <utility>
#include <string>
#include <memory>

class Piece;
class Board;
class Move;

/* Player Classes */
// A Player is a:
//  Computer | Human
class Player{
protected:
    /* fields */
    int status;                                     // status of the player: 1: normal, 2: checked, ...
    Player * opponent;                              // reference to the opponent
    Board * board;                                  // reference to the board
    std::vector<std::unique_ptr<Piece>> pieces;     // pieces owned by the player

    /* functions */

public:
    Player();                                       // constructor
    ~Player();                                      // destroctor that does nothing
    void update();                                  // updates status
    void updateMoves();                             // updates valid moves 
    std::unique_ptr<Move> move();                   // makes a move
};


#endif