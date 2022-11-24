#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>
#include <vector>
#include <memory>

class Move;
class Capture;

const int IV_LEN = 9;

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
    virtual char representation() const = 0;
    virtual std::unique_ptr<Piece> clone() = 0;
public:
    Piece(int colour, const std::pair<int, int> & pos);     // construct the piece and move it to position pos
    // Piece(const Piece & piece);          // edit: we may not need that since there is no pointer field
    void move(const std::pair<int,int> & to, int round);    // move the piece (set position, update last move)
    void setScanningOptions(int iv[IV_LEN]);                // add scanning options
    // iv is an imforming vector of size 9 (?)
    //      iv[0]: x
    //      iv[1]: y
    //      iv[2]: the colour of the piece
    //      iv[3]: the movesCount (only for Pawn, -1 otherwise)
    //  the remaining elements form an indicating vector (which are 0 or 1)
    //   each indices represent the scanning options:
    //      iv[4]: king's move
    //      iv[5]: horizontal/vertical 
    //      iv[6]: diagonal
    //      iv[7]: knight's move
    //      iv[8]: pawn's move

    // get fields
    int getValue() const;
    int getColour() const;
    //int getLastMove() const;
    int getStatus() const;
    char getRepresentation() const;
    const std::pair<int,int> & getPosition() const;

    // return a unique pointer of a copy of the class
    std::unique_ptr<Piece> uniqueCpy();
};

class King : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
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
    std::unique_ptr<Piece> clone() override;
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
    std::unique_ptr<Piece> clone() override;
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
    std::unique_ptr<Piece> clone() override;
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
    std::unique_ptr<Piece> clone() override;
public:
    Knight(int colour, const std::pair<int, int> & pos);
    
};

class Pawn : public Piece{
    /* fields */
    int movesCount;          // number of Moves taken
    int recentMove;          // recent round which move this piece
    /* functions */
    int value() const override;
    void movePiece(const std::pair<int,int> & to, int round) override;
    void scan(int iv[IV_LEN]) const override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Pawn(int colour, const std::pair<int, int> & pos);
};

#endif