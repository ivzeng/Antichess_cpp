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
// A Player can be a:
//  Computer | Human
class Player{
    /* fields */
    int colour;
protected:
    Board * board;                                  // reference to the board
    std::vector<Piece> pieces;                      // pieces owned by the player
    std::vector<Move> moves[3];                     // Moves avaliable to the player
                                                    //  moves[0]: valid capture moves
                                                    //  moves[1]: valid peaceful moves
                                                    //  moves[2]: moves that sell your king!

    /* functions */

public:
    Player(int colour);                                             // constructor
    ~Player();                                                      // destroctor that does nothing
    int updateStatus();                                             // check if the king is rip
    void updateMoves();                                             // updates moves 


    virtual void move(std::vector<Move> & hist);                    // makes a move and store it into hist
};

class Human: public Player{
public:
    Human(int colour);
    void move(std::vector<Move> & hist) override;
};

class Computer: public Player{
public:
    Computer(int colour);
    void move(std::vector<Move> & hist) override;
};


#endif