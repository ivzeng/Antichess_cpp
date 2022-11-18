#ifndef MOVE_H
#define MOVE_H

#include <utility>

class Piece;

/* Move class */
// A Move can be a
//  Move (normal move without capture)
//  | Capture
//  | Promotion (when a piece reach the end of the board)
//  | Castling
class Move{
    /* fields */
protected:
    Piece * piece;                  // piece to preform the Move
    std::pair<int,int> from;
    std::pair<int,int> to;          // positions
    
    /* function */
public:
    Move(Piece* piece, std::pair<int,int> from, std::pair<int,int> to);  // constructor, take Move on the piece
    virtual ~Move() = 0;
};

class Basic : public Move{
    /* fields */

    /* function */
public:
    Basic(Piece* piece, std::pair<int,int> from, std::pair<int,int> to);
};

class Capture : public Move{
    /* fields */
    Piece * capturedPiece;
    /* function */
public:
    Capture(Piece* piece, std::pair<int,int> from, std::pair<int,int> to, Piece * capturedPiece);
};

class Promotion : public Move{
    /* fields */
    Piece * promotionResult;
    /* function */
public:
    Promotion(Piece* piece, std::pair<int,int> from, std::pair<int,int> to, Piece * capturedPiece);
};

class Castling : public Move{
    /* fields */
    
    /* function */
public:
    Castling(Piece* piece, std::pair<int,int> from, std::pair<int,int> to, Piece * capturedPiece);
};


#endif