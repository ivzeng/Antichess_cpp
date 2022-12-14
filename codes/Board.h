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
    std::pair<int,int> kingPos{};

    /* function */
    

    //checks if the piece at pos can be attacked
    bool unsafe(std::pair<int, int> pos, int col);

    // checks if the king is in checked
    bool isCheck();

    // inserts the move (from, to) (either basic or capture) (true iff the move is not capture)
    bool insertMove(const std::pair<int,int> & from, const std::pair<int,int> & to, std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // inserts the move for king
    void kInsertMove(const std::pair<int,int> & to, std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    void pInsertMove(int diff, const std::pair<int,int> & from, std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // determine if a (not king's) move is safe/valid
    bool safeMove(const std::pair<int,int> & from, const std::pair<int,int> & to);

    // determine if a king's move is safe/valid
    bool kSafeMove(const std::pair<int,int> & to);

    void castleScan(std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    bool validPos(const std::pair<int,int> & pos);

public:
    Board();

    // get the piece at (x,y) position
    Piece * get(int x, int y) const;

    Piece * get(const std::pair<int, int> & pos) const;
    // return the (x,y) position of the board
    char getRepresentation(int x, int y) const;

    // set (x, y)
    void set(int x, int y, Piece * p);
    void set(const std::pair<int,int> & position, Piece * p);

    // set kingPos
    void setKP(const std::pair<int,int> & position);

    // scanning

    // given a position, assume there is a rook,
    // inserts the positions the rook can go before encountering a piece into moves[0];
    // inserts the positions of the pieces (if any) that block the route into moves[1]. 
    void hvScan(const std::pair<int,int> & pos,std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a bishop 
    //  (i.e. scan diagnal directions)
    void dScan(const std::pair<int,int> & pos,std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a King 
    //  (i.e. scan positions at (x+i, y+j) where |i| = 1, |j| = 1)
    void kScan(std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a knight 
    //  (i.e. scan positions at (x+i, y+j) where |i| = 1, |j| = 2 or |i| = 2, |j| = 1)
    void nScan(const std::pair<int,int> & pos, std::vector<std::vector<std::unique_ptr<Move>>> & moves);

    // do hvScan except that rook becomes a pawn 
    //  (i.e. scan positions at (x,y+d), (x, y+2d) (if pawn have not moved) - moves
    //          (x+1, y+d), (x-1, y-d)                                      - capture / en passant
    //      d is the direction, in {-1,1})
    void pScan(int col, int movesCount, int round, const std::pair<int,int> & pos, std::vector<std::vector<std::unique_ptr<Move>>> & moves);


    // makes a move based on the coordinate representation
    std::unique_ptr<Move> makeMove(int colour, std::string can);

};

const int BOARD_SIZE = 8;

#endif
