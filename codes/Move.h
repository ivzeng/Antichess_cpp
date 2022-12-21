#ifndef MOVE_H
#define MOVE_H

#include <utility>
#include <string>
#include <vector>
#include <memory>

class Piece;
class Player;

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
    virtual std::string getRepresentaion() const;
    /* function */
    Move(Piece* piece, const std::pair<int,int> & from, const std::pair<int,int> & to);  // constructor, take Move on the piece
    virtual void act(int round, Player & player) = 0;
    virtual void reverse(Player & player) = 0;
    
public:
    virtual ~Move() = 0;
    bool operator==(const std::string & can) const;
    std::string representation() const;       // return the coordinate algebraic notation of the move (e2e4, e7e8q (promotion))
    void process(int round,Player & player);
    void undo(Player & player);
};

class Basic : public Move{
    /* fields */

    /* function */
    void act(int round, Player & player) override;
    void reverse(Player & player) override;

public:
    Basic(Piece* piece, const std::pair<int,int> & from, const std::pair<int,int> & to);
};

class Capture : virtual public Move{
    /* fields */
    Piece * capturedPiece;

    /* function */
    virtual void act(int round, Player & player) override;
    virtual void reverse(Player & player) override;

public:
    Capture(Piece* piece,Piece * capturedPiece, const std::pair<int,int> & from, const std::pair<int,int> & to);
};

class Promotion : virtual public Move{
    /* fields */
protected:
    std::unique_ptr<Piece> promotion;
    std::string getRepresentaion() const override;

    /* function */
    void act(int round,Player & player) override;
    void reverse(Player & player) override;

public:
    Promotion(Piece* piece,  Piece * promotion, const std::pair<int,int> & from, const std::pair<int,int> & to);

};

class CapturePromotion : public Promotion {
    /* field */
    Piece * capturedPiece;

    /* function */
    void act(int round, Player & player) override;
    void reverse(Player & player) override;

public:
    CapturePromotion(Piece* piece, Piece * captured, Piece * promotion, const std::pair<int,int> & from, const std::pair<int,int> & to);
};

class Castling : public Move{
    /* fields */
    std::unique_ptr<Basic> rookMove;

    /* function */
    void act(int round, Player & player) override;
    void reverse(Player & player) override;

public:
    Castling(Piece* piece,  Piece * rook, const std::pair<int,int> & fromK, const std::pair<int,int> & toK, const std::pair<int,int> & fromR, const std::pair<int,int> & toR);
};

// converts the coordinate algebraic notation into the coordinate system used by the program
int getX(const char & x);
int getY(const char & y);

// checks the coordinate algebraic notation
bool validX(const char & x);    // also to lower case
bool validY(const char & y);


// searches the move in coordinate algebraic notation from moves, puts the indices of the move in moves and the validity into move (for example, moves becomes "011": the move is at moves[0][1], and it is valid). If the move is not in moves, move will be unchanged 
void search(std::string & move, const std::vector<std::vector<std::unique_ptr<Move>>> & moves);

// get the index of the row of moves that is not empty, returns -1 if all rows are empty
int getValidMove(const std::vector<std::vector<std::unique_ptr<Move>>> & moves);

#endif