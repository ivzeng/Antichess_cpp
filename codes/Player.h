#ifndef PLAYER_h
#define PLAYER_h

#include <vector>
#include <utility>
#include <string>
#include <memory>

class Piece;
class Board;
class Move;

/* Player Classes */
// A Player can be a:
//  Computer | Human
class Player{
    /* fields */
protected:
    int colour;                                         // 0 for white and 1 for black
    std::vector<std::unique_ptr<Piece>> pieces;         // pieces owned by the player


    /* functions */
    virtual std::string decide(const std::vector<std::vector<std::unique_ptr<Move>>> & moves) = 0;                               // decide a move 
    virtual std::unique_ptr<Player> clone() = 0; 
public:
    Player(int colour);                                             // constructor
    Player(const Player & player);                                  // copy ctor
    // ~Player();                                                   // destroctor 
    //  edit: apparently there is nothing to delete

    void init();                                                    // initialize pieces
    int updateStatus();                                             // check if the king is rip
    void updateBoard(Board & board);                // help put the pieces on the board
    void searchMoves(int round, Board & board, std::vector<std::vector<std::unique_ptr<Move>>> & moves);     // searches all possible moves and puts them into moves
    
    // decides a move
    std::string move(const std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // make a copy of the player and return the unique_ptr
    std::unique_ptr<Player> copy();

    // gets field
    int getColour() const;
    const std::vector<std::unique_ptr<Piece>> & getPieces() const;

    void addPiece(std::unique_ptr<Piece> & p);
    void popPiece();
};

class Human: public Player{
public:
    Human(int colour);
    Human(const Human & human);

    // read from stdin, return either a move 
    std::string decide(const std::vector<std::vector<std::unique_ptr<Move>>> & moves) override;

    std::unique_ptr<Player> clone() override;
};

class AlphaWind: public Player{
public:
    AlphaWind(int colour);
    AlphaWind(const AlphaWind & alphaWind);
    std::string decide(const std::vector<std::vector<std::unique_ptr<Move>>> & moves) override;
    std::unique_ptr<Player> clone() override;
};


#endif