#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <memory>
#include <utility>



class Piece;
class Move;

class Board{
    /* fields */
    Piece * board[8][8];

    /* function */
    // given a position, assume there is a rook,
    // inserts the positions the rook can go before encountering a piece into moves[0];
    // inserts the positions of the pieces (if any) that block the route into moves[1]. 
    void hvScan(std::pair<int,int> pos,std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a bishop 
    //  (i.e. scan diagnal directions)
    void dScan(std::pair<int,int> pos,std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a King 
    //  (i.e. scan positions at (x+i, y+j) where |i| = 1, |j| = 2 or |i| = 2, |j| = 1)
    void kScan(std::pair<int,int> pos,  std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a knight 
    //  (i.e. scan positions at (x+i, y+j) where |i| = 1, |j| = 2 or |i| = 2, |j| = 1)
    void nScan(std::pair<int,int> pos, std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a pawn 
    //  (i.e. scan positions at (x,y+d), (x, y+2d) (if pawn have not moved) - moves
    //          (x+1, y+d), (x-1, y-d)                                      - capture / en passant
    //      d is the direction, in {-1,1})
    void pScan(int col, int movesCount, std::pair<int,int> pos, std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // get the direction bases on the colour.
    int getD(int colour);
public:
    Board();

    // scan based on the instructions on iv, return all possible position a piece can go (regardless validity)
    void scan(int iv[9], std::vector<std::vector<std::unique_ptr<Move>>> & moves); 

    // get the piece at (x,y) position
    Piece * get(int x, int y) const;

    // return the (x,y) position of the board
    char getRepresentation(int x, int y) const;

    // set (x, y)
    void set(int x, int y, Piece * p);
    void set(const std::pair<int,int> & position, Piece * p);
};
#endif
