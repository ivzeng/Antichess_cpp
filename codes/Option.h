#ifndef MOVE_H
#define MOVE_H

#include <utility>

class Piece;

/* Option class */
// A Option can be a
//  Move (normal move without capture)
//  | Capture
//  | Promotion (when a piece reach the end of the board)
//  | Castling
class Option{
    /* fields */
protected:
    Piece * piece;              // piece to preform the option
    std::pair<int> from;
    std::pair<int> to;          // positions
    
    /* function */
public:
    Option(Piece* piece, std::pair<int> from, std::pair<int> to);  // constructor, take option on the piece
    virtual ~Option() = 0;
};

class Move : public Option{
    /* fields */

    /* function */
public:
    Move(Piece* piece, std::pair<int> from, std::pair<int> to);
};

class Capture : public Option{
    /* fields */
    Piece * capturedPiece;
    /* function */
public:
    Capture(Piece* piece, std::pair<int> from, std::pair<int> to, Piece * capturedPiece);
};

class Promotion : public Option{
    /* fields */
    Piece * promotionResult;
    /* function */
public:
    Promotion(Piece* piece, std::pair<int> from, std::pair<int> to, Piece * capturedPiece);
};

class Castling : public Option{
    /* fields */
    
    /* function */
public:
    Castling(Piece* piece, std::pair<int> from, std::pair<int> to, Piece * capturedPiece);
};


#endif