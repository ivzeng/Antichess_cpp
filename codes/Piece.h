#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>
#include <vector>

class Option;
class Capture;

/* Piece class */
// A Piece can be a
//  King | Queen | Bishop | Rook | Knight | Pawn
class Piece{
    /* fields */
private:
    int colour;                             //  colour of the piece: 1 - black, 0 - white
    int value;                              //  value of the piece
    int status;                             //  status of the piece: 2 - activate, 1 - forced (cannot move normally), 0 - inactivate (captured) 
    int lastMove;                           //  the most recent round when the player move this piece
    std::pair<int,int> position;            //  position of the piece on the board
    std::vector<Option> peacefulMoves;     //  all valid Options other than Captures
    std::vector<Capture> captureMoves;     //  all valid capture moves  

    /* functions */
    virtual char* scan() = 0;               //  return a char array that tells the borad where to scan
                                            //      "abc"   a: vertical and horizontal, b: ...
    
public:
    void move(std::pair<int,int> to);       //  move the piece
    void addMove();                         //  
};

#endif