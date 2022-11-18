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
    int lastMove;                           //  the most recent round when the player move this piece
    std::pair<int,int> position;            //  position of the piece on the board

    /* functions */
    virtual int* scan() = 0;                //  return an int array of size ??, where
                                            //      the first element is the colour of the piece
                                            //      the remaining elements form an indicating vector (which are 0 or 1)
                                            //      each indices represent the scanning option:
                                            //          1 - king's move; 2 - horizontal/vertical; 3 - diagonal; 
                                            //          3 - knight's move; 4 - pawn's move
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
    int * scan() override;
};

class Queen : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Queen(int colour);
    int * scan() override;
};

class Bishop : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Bishop(int colour);
    int * scan() override;
};

class Rook : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Rook(int colour);
    int * scan() override;
};

class Knight : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Knight(int colour);
    int * scan() override;
};

class Pawn : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Pawn(int colour);
    int * scan() override;
};

#endif