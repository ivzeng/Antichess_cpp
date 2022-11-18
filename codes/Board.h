#ifndef BOARD_H
#define BOARD_H
#include <vector>
#include <utility>



class Piece;
class Move;

class Board{
    /* fields */
    Piece * board[8][8];

    /* function */
    // given a position, assume there is a rook,
    // inserts the positions the rook can go before encountering a piece into basicOptions[0];
    // inserts the positions of the pieces (if any) that block the route into basicOptions[1]. 
    void hvScan(std::pair<int,int> pos, std::vector<std::vector<std::pair<int,int>>> & basicOptions);

    // do hvScan except that rook becomes a bishop 
    //  (i.e. scan diagnal directions)
    void dScan(std::pair<int,int> pos, std::vector<std::vector<std::pair<int,int>>> & basicOptions);

    // do hvScan except that rook becomes a knight 
    //  (i.e. scan positions at (x+i, y+j) where |i| = 1, |j| = 2 or |i| = 2, |j| = 1)
    void kScan(std::pair<int,int> pos, std::vector<std::vector<std::pair<int,int>>> & basicOptions);

    // do hvScan except that rook becomes a pawn 
    //  (i.e. scan positions at (x,y+d), (x, y+2d) (if pawn have not moved) - moves
    //          (x+1, y+d), (x-1, y-d)                                      - capture / en passant
    //      d is the direction, in {-1,1})
    void pScan(std::pair<int,int> pos, std::vector<std::vector<std::pair<int,int>>> & basicOptions, int d);

    // get the direction bases on the colour.
    int getD(int colour);
public:
    Board();
    void process(Move & move);                  // do an Move
    void undo(Move & move);                     // undo an Move

    // scan based on the instructions on iv, return all possible position a piece can go (regardless validity)
    std::vector<std::vector<std::pair<int,int>>> scan(int iv[7]); 
    
};
#endif
