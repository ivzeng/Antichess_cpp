#ifndef PIECE_H
#define PIECE_H

#include <utility>
#include <string>
#include <vector>
#include <memory>

class Move;
class Board;

const int SO_LEN = 9;

//enum PeiceTypes = {King, Queen, Bishop, Rook, Knight, Pawn};

/* Piece class */
// A Piece can be a
//  King | Queen | Bishop | Rook | Knight | Pawn
class Piece{
    /* fields */
protected:
    int colour;                             //  colour of the piece: 1 - black, 0 - white
    int status;                             //  status of the piece: 1 - alscanOpte, 0 - rip
    int movesCount;
    std::pair<int,int> position;            //  position of the piece on the board

    /* functions */
    virtual double value() const = 0;                  // value of the piece         
    virtual void movePiece(const std::pair<int,int> & to, int round); // move a piece
    virtual void  goBack(const std::pair<int, int> & from);

    virtual void scan(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const = 0;    // scans for valid moves
    virtual bool canAttack(const std::pair<int, int> & at) = 0;
    virtual char representation() const = 0;
    virtual std::unique_ptr<Piece> clone() = 0;
public:
    Piece(int colour, const std::pair<int, int> & pos);     // construct the piece and move it to position pos
    virtual ~Piece() = 0;
    void move(const std::pair<int,int> & to, int round);    // move the piece (set position, update last move, increment movesCount)
    void back(const std::pair<int,int> & to);   // undo the move
    void searchMoves(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves);       // search for the moves and update moves
    bool threats(const std::pair<int,int> & at);

    // get fields
    double getValue() const;
    int getColour() const;
    int getStatus() const;
    int getMovesCount() const;
    char getRepresentation() const;
    const std::pair<int,int> & getPosition() const;

    // set field
    void setStatus(int status);
    // return a unique pointer of a copy of the class
    std::unique_ptr<Piece> copy();
};

class King : public Piece{
    /* fields */
    // ...

    /* functions */
    double value() const override;
    void scan(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const override;
    bool canAttack(const std::pair<int, int> & at) override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    King(int colour, const std::pair<int, int> & pos);
};

class Queen : public Piece{
    /* fields */
    // ...

    /* functions */
    double value() const override;
    void scan(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const override;
    bool canAttack(const std::pair<int, int> & at) override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Queen(int colour, const std::pair<int, int> & pos);
};

class Bishop : public Piece{
    /* fields */
    // ...

    /* functions */
    double value() const override;
    void scan(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const override;
    bool canAttack(const std::pair<int, int> & at) override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Bishop(int colour, const std::pair<int, int> & pos);
};

class Rook : public Piece{
    /* fields */
    // ...

    /* functions */
    double value() const override;
    void scan(int round,  Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const override;
    bool canAttack(const std::pair<int, int> & at) override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Rook(int colour, const std::pair<int, int> & pos);
};

class Knight : public Piece{
    /* fields */
    // ...

    /* functions */
    double value() const override;
    void scan(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const override;
    bool canAttack(const std::pair<int, int> & at) override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Knight(int colour, const std::pair<int, int> & pos);
    
};

class Pawn : public Piece{
    /* fields */
    std::vector<int> recentMoves;          // all rounds which move this piece
    /* functions */
    double value() const override;
    void movePiece(const std::pair<int,int> & to, int round) override;
    void goBack(const std::pair<int,int> & from) override;
    void scan(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves) const override;
    bool canAttack(const std::pair<int, int> & at) override;
    char representation() const override;
    std::unique_ptr<Piece> clone() override;
public:
    Pawn(int colour, const std::pair<int, int> & pos);
    int getRecentMove() const;
};

Piece * makePiece(int colour, const char & p, const std::pair<int,int> & pos);

#endif