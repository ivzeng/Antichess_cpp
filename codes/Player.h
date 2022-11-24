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
    // std::vector<std::vector<unique_ptr<Move>>> moves;                  
    // Moves avaliable to the player
    //  moves[0]: valid capture moves
    //  moves[1]: valid peaceful moves
    //  moves[2], move[3]: moves that sell your king! caputure or not
    // edit: created a function that produce it instead


    /* functions */
    virtual void makeMove(std::vector<std::unique_ptr<Move>> & hist) = 0;   // makes a move and store it into hist
    virtual std::unique_ptr<Player> clone() = 0; 
public:
    Player(int colour);                                             // constructor
    Player(const Player & player);                                  // copy ctor
    // ~Player();                                                   // destroctor 
    //  edit: apparently there is nothing to delete

    void init();                                                    // initialize pieces
    int updateStatus();                                             // check if the king is rip
    void updateBoard(Board * board);                // help put the pieces on the board
    std::vector<std::vector<std::unique_ptr<Move>>>  searchMoves(const Board & board);     // search all possible moves
    // make a move
    void move(std::vector<std::unique_ptr<Move>> & hist);

    // make a copy of the player and return the unique_ptr
    std::unique_ptr<Player> uniqueCpy();

    int getColour() const;
    const std::vector<std::unique_ptr<Piece>> & getPieces() const;
};

class Human: public Player{
public:
    Human(int colour);
    Human(const Human & human);
    void makeMove(std::vector<std::unique_ptr<Move>> & hist) override;
    std::unique_ptr<Player> clone() override;
};

class AlphaWind: public Player{
public:
    AlphaWind(int colour);
    AlphaWind(const AlphaWind & alphaWind);
    void makeMove(std::vector<std::unique_ptr<Move>> & hist) override;
    std::unique_ptr<Player> clone() override;
};


#endif