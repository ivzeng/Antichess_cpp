#include "Board.h"
#include "Piece.h"
#include "Move.h"

using namespace std;

Board::Board() {
    for (int y = 0; y < 8; y += 1){
        for (int x = 0; x < 8; x += 1){
            board[y][x] = nullptr;
        }
    }
}

Piece * Board::get(int x, int y) const {
    return board[y][x];
}

Piece * Board::get(const pair<int, int> & pos) const {
    return board[pos.second][pos.first];
}

char Board::getRepresentation(int x, int y) const {
    return get(x,y) ? get(x,y)->getRepresentation() : '-';
}

void Board::set(int x, int y, Piece * p) {
    board[y][x] = p;
} 

void Board::set(const pair<int,int> & position, Piece * p) {
    board[position.second][position.first] = p;
}

void Board::setKP(const pair<int,int> & position) {
    kingPos = position;
}

bool Board::insertMove(const std::pair<int,int> & from, const std::pair<int,int> & to, vector<vector<unique_ptr<Move>>> & moves){
    if (!safeMove(from, to)) {
        return !get(to);
    }
    if (get(to) == nullptr) {
        moves[1].emplace_back(unique_ptr<Move>{new Basic{get(from), from, to}});
        return true;
    }
    else {
        moves[0].emplace_back(unique_ptr<Move>{new Capture{get(from), get(to), from, to}});
        return false;
    }
}

void Board::kInsertMove(const pair<int,int> & to, vector<vector<unique_ptr<Move>>> & moves) {
    if (!kSafeMove(to)) {
        return;
    }
    if (get(to) == nullptr) {
        moves[1].emplace_back(unique_ptr<Move>{new Basic{get(kingPos), kingPos, to}});
    }
    else {
        moves[0].emplace_back(unique_ptr<Move>{new Capture{get(kingPos), get(to), kingPos, to}});
    }
}


void Board::pInsertMove(int col, const pair<int,int> & from, vector<vector<unique_ptr<Move>>> & moves) {
    int dir = (col == 0) ? 1 : -1;
    bool prom = from.second+dir == BOARD_SIZE-1 || from.second + dir == 0;
    // normal move / promotion
    if (!board[from.second+dir][from.first]) {
        pair<int,int> to{from.first, from.second + dir}; 
        if (prom) {
            moves[1].emplace_back(unique_ptr<Move> {new Promotion{get(from), new Queen{col, to}, from, to}});
            moves[1].emplace_back(unique_ptr<Move> {new Promotion{get(from), new Rook{col, to}, from, to}});
            moves[1].emplace_back(unique_ptr<Move> {new Promotion{get(from), new Bishop{col, to}, from, to}});
            moves[1].emplace_back(unique_ptr<Move> {new Promotion{get(from), new Knight{col, to}, from, to}});
        }
        else {
            moves[1].emplace_back(unique_ptr<Move> {new Basic{get(from), from, to}});
        }
    }
    // capture move / promotion
    if (from.first+1 < BOARD_SIZE) {
        if (board[from.second+dir][from.first+1]){
            Piece * target = board[from.second+dir][from.first+1]; 
            pair<int,int> to{from.first + 1, from.second + dir}; 
            if (prom) {
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target,new Queen{col, to}, from, to}});
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target, new Rook{col, to}, from, to}});
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target, new Bishop{col, to}, from, to}});
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target, new Knight{col, to}, from, to}});
            }
            else {
                moves[0].emplace_back(unique_ptr<Move> {new Basic{get(from), from, pair<int,int> {from.first+1, from.second + dir}}});
            }
        }
    }

    if (from.first-1 < BOARD_SIZE) {
        if (board[from.second+dir][from.first-1]){
            Piece * target = board[from.second+dir][from.first-1]; 
            pair<int,int> to{from.first - 1, from.second + dir}; 
            if (prom) {
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target, new Queen{col, to}, from, to}});
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target, new Rook{col, to}, from, to}});
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target, new Bishop{col, to},  from, to}});
                moves[0].emplace_back(unique_ptr<Move> {new CapturePromotion{get(from), target,new Knight{col, to}, from, to}});
            }
            else {
                moves[0].emplace_back(unique_ptr<Move> {new Basic{get(from), from, pair<int,int> {from.first-1, from.second + dir}}});
            }
        }
    }
}

bool Board::safeMove(const std::pair<int,int> & from, const std::pair<int,int> & to) {
    // Todo
    return false;
}

bool Board::kSafeMove(const std::pair<int,int> & to) {
    // Todo
    return false;
}


//pos = (col, row)
void Board::hvScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    //scan right
    for (int i = pos.first + 1;  i < BOARD_SIZE && insertMove(pos, pair<int, int>{i, pos.second}, moves); ++i);

    //scan left
    for (int i = pos.first - 1;  i >= 0 && insertMove(pos, pair<int, int>{i, pos.second}, moves); --i);

    //scan up
    for (int i = pos.second + 1;  i < BOARD_SIZE && insertMove(pos, pair<int, int>{pos.first, i}, moves); ++i);

    //scan down
    for (int i = pos.second - 1;  i >= 0 && insertMove(pos, pair<int, int>{pos.first, i}, moves); ++i);
}

void Board::dScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    //Scan up and right
    for (int i = 1;  pos.first+i < BOARD_SIZE && pos.second+i < BOARD_SIZE && insertMove(pos, pair<int, int>{pos.first+i, pos.second+i}, moves); ++i);

    //Scan up and left
    for (int i = 1;  pos.first-i >= 0 && pos.second+i < BOARD_SIZE && insertMove(pos, pair<int, int>{pos.first-i, pos.second+i}, moves); ++i);

    //Scan down and right    
    for (int i = 1;  pos.first+i < BOARD_SIZE && pos.second-i >= 0 && insertMove(pos, pair<int, int>{pos.first+i, pos.second-i}, moves); ++i);

    //Scan down and left
    for (int i = 1;  pos.first-i >= 0 && pos.second-i >= 0 && insertMove(pos, pair<int, int>{pos.first-i, pos.second-i}, moves); ++i);
}

void Board::kScan(vector<vector<unique_ptr<Move>>> & moves){
    // left
    if (kingPos.first + 1 < BOARD_SIZE) {
        kInsertMove(pair<int, int>{kingPos.first+1, kingPos.second}, moves);
    }

    // right
    if (kingPos.first - 1 >= 0) {
        kInsertMove(pair<int, int>{kingPos.first-1, kingPos.second}, moves);
    }

    // up
    if (kingPos.second + 1 < BOARD_SIZE) {
        kInsertMove(pair<int, int>{kingPos.first, kingPos.second+1}, moves);
    }

    // down
    if (kingPos.second - 1 >= 0) {
        kInsertMove(pair<int, int>{kingPos.first, kingPos.second-1}, moves);
    }

    //up right
    if (kingPos.first + 1 < BOARD_SIZE && kingPos.second + 1 < BOARD_SIZE) {
        kInsertMove(pair<int, int>{kingPos.first+1, kingPos.second+1}, moves);
    }

    // down right
    if (kingPos.first + 1 < BOARD_SIZE && kingPos.second - 1 >= 0) {
        kInsertMove(pair<int, int>{kingPos.first+1, kingPos.second-1}, moves);
    }

    // up left
    if (kingPos.first - 1 >= 0 && kingPos.second + 1 < BOARD_SIZE){
        kInsertMove(pair<int, int>{kingPos.first-1, kingPos.second+1}, moves);
    }

    //down left
    if (kingPos.first - 1 >= 0 && kingPos.second - 1 >= 0) {
        kInsertMove(pair<int, int>{kingPos.first-1, kingPos.second-1}, moves);
    }

    // Todo: check castling
}

void Board::nScan(pair<int,int> pos,vector<vector<unique_ptr<Move>>> & moves){
    // Todo
    int coldiff = 2;
    int rowdiff = 1;
    
    if (pos.first + coldiff < BOARD_SIZE && pos.second + rowdiff < BOARD_SIZE) {
        insertMove(pos, pair<int, int>{pos.first+coldiff, pos.second+rowdiff}, moves);
    }

    if (pos.first + coldiff < BOARD_SIZE && pos.second - rowdiff >= 0) {
        insertMove(pos, pair<int, int>{pos.first+coldiff, pos.second-rowdiff}, moves);
    }

    if (pos.first - coldiff >= 0 && pos.second + rowdiff < BOARD_SIZE) {
        insertMove(pos, pair<int, int>{pos.first-coldiff, pos.second+rowdiff}, moves);
    }

    if (pos.first - coldiff >= 0 && pos.second - rowdiff >= 0) {
        insertMove(pos, pair<int, int>{pos.first - coldiff, pos.second-rowdiff}, moves);
    }
    
    coldiff = 1;
    rowdiff = 2;

    if (pos.first + coldiff < BOARD_SIZE && pos.second + rowdiff < BOARD_SIZE) {
        insertMove(pos, pair<int, int>{pos.first+coldiff, pos.second+rowdiff}, moves);
    }

    if (pos.first + coldiff < BOARD_SIZE && pos.second - rowdiff >= 0) {
        insertMove(pos, pair<int, int>{pos.first+coldiff, pos.second-rowdiff}, moves);
    }

    if (pos.first - coldiff >= 0 && pos.second + rowdiff < BOARD_SIZE) {
        insertMove(pos, pair<int, int>{pos.first-coldiff, pos.second+rowdiff}, moves);
    }
    
    if (pos.first - coldiff >= 0 && pos.second - rowdiff >= 0) {
        insertMove(pos, pair<int, int>{pos.first-coldiff, pos.second-rowdiff}, moves);
    }

}

void Board::pScan(int col, int movesCount, int round, pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    int dir = (col == 0) ? -1 : 1;

    // move (first time)
    if (movesCount == 0 && !board[pos.second+2*dir][pos.first]) {
        moves[1].emplace_back(unique_ptr<Move>{new Basic{get(pos), pos, pair<int,int>{pos.first, pos.second + 2*dir}}});
    }

    // other move / promotion
    pInsertMove(col, pos, moves);
    
}

/*
void Board::castleScan(int col, int movesCountKing, int movesCountRook, std::pair<int,int> posK, std::pair<int,int> posR, std::vector<std::vector<std::unique_ptr<Move>>> & moves) {
    //Neither the king nor the rook has previously moved.
    //There are no pieces between the king and the rook.
    //The king is not currently in check.
    //The king does not pass through a square that is attacked by an opposing piece.

    if (movesCountKing == 0 && movesCountRook == 0){
        bool isPossible = true;

        //Right side
        for (int i = posK.first + 1; i < posR.first; ++i) {
            if (board[i][posK.second] != nullptr) {
                isPossible = false;
            }
        }

        if (isCheck(posK)) {
            isPossible = false;
        }

        std::pair newposK = std::pair<int, int>(posK.first + 2, posK.second>);
        std::pair newposR = std::pair<int, int>(posR.first - 2, posR.second>);

        if (isCheck(newposK)) {
            isPossible = false;
        }

        if (isPossible) {
            moves[0].emplace_back(make_unique<Basic>(new Castling{get(posK), get(posR), posK, newposK, posR, newposR}));
        }

        //Left Side
        isPossible = true;

        for (int i = posK.first - 1; i > posR.first; --i) {
            if (board[i][posK.second] != nullptr) {
                isPossible = false;
            }
        }

        if (isCheck(posK)) {
            isPossible = false;
        }

        std::pair newposK = std::pair<int, int>(posK.first - 2, posK.second>);
        std::pair newposR = std::pair<int, int>(posR.first + 3, posR.second>);

        if (isCheck(newposK)) {
            isPossible = false;
        }

        if (isPossible) {
            moves[0].emplace_back(make_unique<Basic>(new Castling{get(posK), get(posR), posK, newposK, posR, newposR}));
        }
    }
}
*/

// NEED TO REDO
//Iterate over oposing players pieces
bool Board::isCheck(std::pair<int, int> pos) {

    //check down
    /*
    for (int r = pos.second + 1; r < BOARD_SIZE; ++r){
        if (board[pos.first][r]->getRepresentation() == 'Q' || board[pos.first][r]->getRepresentation() == 'R' || board[pos.first][r]->getRepresentation() == 'K')
    }
    */


    return false;
}


unique_ptr<Move> Board::makeMove(int colour,  std::string can) {
    pair<int,int>from{getX(can[0]), getY(can[1])};
    pair<int,int>to{getX(can[2]), getY(can[3])};
    if (can.length() == 4) {
        if (get(to)) {
            return unique_ptr<Move> {new Capture{get(from), get(to), from, to}};
        }
        else {
            return unique_ptr<Move> {new Basic{get(from), from, to}};
        }
    }
    else {
        if (get(to)) {
            return unique_ptr<Move> {new CapturePromotion{get(from), get(to), makePiece(colour, can[4], to) , from, to}};
        }
        else {
            return unique_ptr<Move> {new Promotion{get(from), makePiece(colour, can[4], to) , from, to}};
        }
    }
}