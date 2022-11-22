#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>
#include <vector>

class Move;
class Capture;

const int IV_LEN = 7;

/* Piece class */
// A Piece can be a
//  King | Queen | Bishop | Rook | Knight | Pawn
class Piece{
    /* fields */
protected:
    int colour;                             //  colour of the piece: 1 - black, 0 - white
    int value;                              //  value of the piece
    //int lastMove;                           //  the most recent round when the player move this piece
    int status;                             //  status of the piece: 1 - alive, 0 - rip
    std::pair<int,int> position;            //  position of the piece on the board
    /* functions */
    virtual void movePiece(const std::pair<int,int> & to, int round); // move a piece
    virtual void scan(int iv[IV_LEN]) = 0;       //  update an int array of size 7??, where
                                            //      the first element is the colour of the piece
                                            //      the second element is the moveCount (only for Pawn)
                                            //      the remaining elements form an indicating vector (which are 0 or 1)
                                            //      each indices represent the scanning Move:
                                            //          1 - king's move; 2 - horizontal/vertical; 3 - diagonal; 
                                            //          4 - knight's move; 5 - pawn's move
public:
    Piece(int colour, const std::pair<int, int> & pos);     // construct the piece and move it to position pos
    Piece(const Piece & piece);                             // copy
    void move(const std::pair<int,int> & to, int round);    //  move the piece (set position, update last move)
    
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
    void scan(int iv[IV_LEN]) override;
};

class Queen : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Queen(int colour, const std::pair<int, int> & pos);
    void scan(int iv[IV_LEN]) override;
};

class Bishop : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Bishop(int colour, const std::pair<int, int> & pos);
    void scan(int iv[IV_LEN]) override;
};

class Rook : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Rook(int colour, const std::pair<int, int> & pos);
    void scan(int iv[IV_LEN]) override;
};

class Knight : public Piece{
    /* fields */
    // ...

    /* functions */
public:
    Knight(int colour, const std::pair<int, int> & pos);
    void scan(int iv[IV_LEN]) override;
};

class Pawn : public Piece{
    /* fields */
    int movesCount;          // number of Move taken
    int recentMove;          // recent round which move this piece
    /* functions */
public:
    Pawn(int colour, const std::pair<int, int> & pos);
    void movePiece(const pair<int,int> & to, int round) override;
    void scan(int iv[IV_LEN]) override;
};

#endif