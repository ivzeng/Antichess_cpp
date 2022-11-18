#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>
#include <vector>

class Move;
class Capture;

/* Piece class */
// A Piece can be a
//  King | Queen | Bishop | Rook | Knight | Pawn
class Piece{
    /* fields */
private:
    int colour;                             //  colour of the piece: 1 - black, 0 - white
    int value;                              //  value of the piece
    int lastMove;                           //  the most recent round when the player move this piece
    std::pair<int,int> position;            //  position of the piece on the board

    /* functions */
    virtual void scan(int iv[7]) = 0;       //  update an int array of size 7??, where
                                            //      the first element is the colour of the piece
                                            //      the second element is the moveCount (only for Pawn)
                                            //      the remaining elements form an indicating vector (which are 0 or 1)
                                            //      each indices represent the scanning Move:
                                            //          1 - king's move; 2 - horizontal/vertical; 3 - diagonal; 
                                            //          4 - knight's move; 5 - pawn's move
public:
    Piece(int colour);
    void move(std::pair<int,int> to);       //  move the piece (set position, lastMove)
    
    // get fields
    int getValue() const;
    int getColour() const;
    int getLastMove() const;
};

class King : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    King(int colour);
    void scan(int iv[6]) override;
};

class Queen : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Queen(int colour);
    void scan(int iv[6]) override;
};

class Bishop : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Bishop(int colour);
    void scan(int iv[6]) override;
};

class Rook : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Rook(int colour);
    void scan(int iv[6]) override;
};

class Knight : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Knight(int colour);
    void scan(int iv[6]) override;
};

class Pawn : public Piece{
    /* fields */
    int moveCount;          // number of Move taken

    /* functions */
public:
    Pawn(int colour);
    void scan(int iv[6]) override;
};

#endif