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
    virtual std::string getRepresentaion();
    /* function */
public:
    Move(Piece* piece, const std::pair<int,int> & from, const std::pair<int,int> & to);  // constructor, take Move on the piece
    virtual ~Move() = 0;
    bool operator==(const std::string & can);
    std::string representation();       // return the coordinate algebraic notation of the move (e2e4, e7e8q (promotion))
};

class Basic : public Move{
    /* fields */

    /* function */
public:
    Basic(Piece* piece, const std::pair<int,int> & from, const std::pair<int,int> & to);
};

class Capture : public Move{
    /* fields */
    Piece * capturedPiece;
    /* function */
public:
    Capture(Piece* piece,Piece * capturedPiece, const std::pair<int,int> & from, const std::pair<int,int> & to);
};

class Promotion : public Move{
    /* fields */
    Piece * promotion;
    std::string getRepresentaion() override;
    /* function */
public:
    Promotion(Piece* piece,  Piece * promotion, const std::pair<int,int> & from, const std::pair<int,int> & to);
};

class Castling : public Move{
    /* fields */
    Piece * rook;
    /* function */
public:
    Castling(Piece* piece,  Piece * rook, const std::pair<int,int> & fromK, const std::pair<int,int> & toK, const std::pair<int,int> & fromR, const std::pair<int,int> & toR);
};

// converts the coordinate algebraic notation into the coordinate system used by the program
int getX(const char & x);
int getY(const char & y);

// checks the coordinate algebraic notation
bool validX(const char & x);
bool validY(const char & y);

// searches the move in coordinate algebraic notation from moves, puts the indices of the move in moves and the validity into move (for example, moves becomes "011": the move is at moves[0][1], and it is valid). If the move is not in moves, move will be unchanged 
void search(std::string & move, const std::vector<std::vector<std::unique_ptr<Move>>> & moves);

bool hasValidMove(const std::vector<std::vector<std::unique_ptr<Move>>> & moves);

#endif