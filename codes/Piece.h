#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>
#include <vector>
#include <memory>

class Move;
class Capture;

const int SO_LEN = 9;

/* Piece class */
// A Piece can be a
//  King | Queen | Bishop | Rook | Knight | Pawn
class Piece{
    /* fields */
protected:
    int colour;                             //  colour of the piece: 1 - black, 0 - white
    int status;                             //  status of the piece: 1 - alscanOpte, 0 - rip
    int moveCount;
    std::pair<int,int> position;            //  position of the piece on the board

    /* functions */
    virtual int value() const = 0;                  // value of the piece         
    virtual void movePiece(const std::pair<int,int> & to, int round); // move a piece
    virtual void scan(int scanOpt[SO_LEN]) const = 0;    // add scanning options 
    virtual char representation() const = 0;
    virtual std::unique_ptr<Piece> clone() = 0;
public:
    Piece(int colour, const std::pair<int, int> & pos);     // construct the piece and move it to position pos
    // Piece(const Piece & piece);          // edit: we may not need that since there is no pointer field
    void move(const std::pair<int,int> & to, int round);    // move the piece (set position, update last move)
    void setScanningOptions(int scanOpt[SO_LEN]);                // add scanning options
    // scanOpt is an imforming vector of size 9 (?)
    //      scanOpt[0]: x
    //      scanOpt[1]: y
    //      scanOpt[2]: the colour of the piece
    //      scanOpt[3]: the movesCount (only for Pawn, -1 otherwise)
    //  the remaining elements form an indicating vector (which are 0 or 1)
    //   each indices represent the scanning options:
    //      scanOpt[4]: king's move
    //      scanOpt[5]: horizontal/vertical 
    //      scanOpt[6]: diagonal
    //      scanOpt[7]: knight's move
    //      scanOpt[8]: pawn's move

    // get fields
    int getValue() const;
    int getColour() const;
    //int getLastMove() const;
    int getStatus() const;
    char getRepresentation() const;
    const std::pair<int,int> & getPosition() const;

    // return a unique pointer of a copy of the class
    std::unique_ptr<Piece> copy();
};

class King : public Piece{
    /* fields */
    // ...

    /* functions */
    int value() const override;
    void scan(int scanOpt[SO_LEN]) const override;
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
    void scan(int scanOpt[SO_LEN]) const override;
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
    void scan(int scanOpt[SO_LEN]) const override;
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
    void scan(int scanOpt[SO_LEN]) const override;
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
    void scan(int scanOpt[SO_LEN]) const override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Knight(int colour, const std::pair<int, int> & pos);
    
};

class Pawn : public Piece{
    /* fields */
    std::vector<int> recentMove;          // all rounds which move this piece
    /* functions */
    int value() const override;
    void movePiece(const std::pair<int,int> & to, int round) override;
    void scan(int scanOpt[SO_LEN]) const override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Pawn(int colour, const std::pair<int, int> & pos);
};

#endif