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
    int status;                             //  status of the piece: 1 - alive, 0 - rip
    std::pair<int,int> position;            //  position of the piece on the board
    /* functions */
    virtual int value() const = 0;                  // value of the piece         
    virtual void movePiece(const std::pair<int,int> & to, int round); // move a piece
    virtual void scan(int iv[IV_LEN]) const = 0;    // add scanning options 
    virtual char representation() const;
public:
    Piece(int colour, const std::pair<int, int> & pos);     // construct the piece and move it to position pos
    // Piece(const Piece & piece);          // edit: we may not need that since there is no pointer field
    void move(const std::pair<int,int> & to, int round);    // move the piece (set position, update last move)
    void setScanningOptions(int iv[IV_LEN]);                // add scanning options
    // iv is an imforming vector of size 7 (?)
    //      iv[0]: the colour of the piece
    //      iv[1]: the moveCount (only for Pawn, -1 otherwise)
    //  the remaining elements form an indicating vector (which are 0 or 1)
    //   each indices represent the scanning options:
    //      iv[2]: king's move
    //      iv[3]: horizontal/vertical 
    //      iv[4]: diagonal
    //      iv[5]: knight's move
    //      iv[6]: pawn's move

    // get fields
    int getValue() const;
    int getColour() const;
    //int getLastMove() const;
    int getStatus() const;
    char getRepresentation() const;
};

class King : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
public:
    King(int colour, const std::pair<int, int> & pos);
};

class Queen : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
public:
    Queen(int colour, const std::pair<int, int> & pos);
};

class Bishop : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
public:
    Bishop(int colour, const std::pair<int, int> & pos);
};

class Rook : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
public:
    Rook(int colour, const std::pair<int, int> & pos);
};

class Knight : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
public:
    Knight(int colour, const std::pair<int, int> & pos);
    
};

class Pawn : public Piece{
    /* fields */
    int movesCount;          // number of Move taken
    int recentMove;          // recent round which move this piece
    /* functions */
    int value() const override;
    void movePiece(const pair<int,int> & to, int round) override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
public:
    Pawn(int colour, const std::pair<int, int> & pos);
};

#endif