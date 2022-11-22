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
    //int lastMove;                           //  the most recent round when the player move this piece
    int status;                             //  status of the piece: 1 - alive, 0 - rip
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
    Piece(int colour, const std::pair<int, int> & pos);     // construct the piece and move it to position pos
    Piece(const Piece & piece);                             // copy
    void move(const std::pair<int,int> & to);                       //  move the piece (set position, lastMove)
    
    // get fields
    int getValue() const;
    int getColour() const;
    //int getLastMove() const;
    int getStatus() const;
};

class King : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    King(int colour, const std::pair<int, int> & pos);
    void scan(int iv[6]) override;
};

class Queen : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Queen(int colour, const std::pair<int, int> & pos);
    void scan(int iv[6]) override;
};

class Bishop : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Bishop(int colour, const std::pair<int, int> & pos);
    void scan(int iv[6]) override;
};

class Rook : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Rook(int colour, const std::pair<int, int> & pos);
    void scan(int iv[6]) override;
};

class Knight : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Knight(int colour, const std::pair<int, int> & pos);
    void scan(int iv[6]) override;
};

class Pawn : public Piece{
    /* fields */
    int lastMove;          // number of Move taken

    /* functions */
public:
    Pawn(int colour, const std::pair<int, int> & pos);
    void scan(int iv[6]) override;
};

#endif