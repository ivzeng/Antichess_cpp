#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "IO.h"

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
        moves[1].emplace_back(make_unique<Basic>(get(from), from, to));
        return true;
    }
    else if (get(from)->getColour() != get(to)->getColour()) {
        moves[0].emplace_back(make_unique<Capture>(get(from), get(to), from, to));
        return false;
    }
    return false;
}

void Board::kInsertMove(const pair<int,int> & to, vector<vector<unique_ptr<Move>>> & moves) {
    if (!kSafeMove(to)) {
        return;
    }
    if (get(to) == nullptr) {
        moves[1].emplace_back(make_unique<Basic>(get(kingPos), kingPos, to));
    }
    else if (get(to)->getColour() != get(kingPos)->getColour()) {
        moves[0].emplace_back(make_unique<Capture>(get(kingPos), get(to), kingPos, to));
    }
}


void Board::pInsertMove(int col, const pair<int,int> & from, vector<vector<unique_ptr<Move>>> & moves) {
    int dir = (col == 0) ? 1 : -1;
    bool prom = from.second+dir == BOARD_SIZE-1 || from.second + dir == 0;
    // normal move / promotion
    if (!board[from.second+dir][from.first] && safeMove(from, pair<int,int>{from.first, from.second+dir})) {
        pair<int,int> to{from.first, from.second + dir}; 
        if (prom) {
            moves[1].emplace_back(make_unique<Promotion>(get(from), new Queen{col, to}, from, to));
            moves[1].emplace_back(make_unique<Promotion>(get(from), new Rook{col, to}, from, to));
            moves[1].emplace_back(make_unique<Promotion>(get(from), new Bishop{col, to}, from, to));
            moves[1].emplace_back(make_unique<Promotion>(get(from), new Knight{col, to}, from, to));
        }
        else {
            moves[1].emplace_back(make_unique<Basic>(get(from), from, to));
        }
    }
    // capture move / promotion
    if (from.first+1 < BOARD_SIZE && board[from.second+dir][from.first+1] && board[from.second+dir][from.first+1]->getColour() != col && safeMove(from, pair<int,int>{from.first+1, from.second+dir})){
        Piece * target = board[from.second+dir][from.first+1]; 
            pair<int,int> to{from.first+1, from.second + dir}; 
        if (prom) {
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Queen{col, to}, from, to));
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Rook{col, to}, from, to));
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Bishop{col, to}, from, to));
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Knight{col, to}, from, to));
        }
        else {
            moves[0].emplace_back(make_unique<Capture>(get(from), get(to), from, pair<int,int> {from.first+1, from.second + dir}));
        }
    }

    if (from.first-1 >= 0  && board[from.second+dir][from.first-1] && board[from.second+dir][from.first-1]->getColour() != col && safeMove(from, pair<int,int>{from.first-1, from.second+dir})){
        Piece * target = board[from.second+dir][from.first-1]; 
        pair<int,int> to{from.first - 1, from.second + dir}; 
        if (prom) {
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Queen{col, to}, from, to));
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Rook{col, to}, from, to));
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target, new Bishop{col, to},  from, to));
            moves[0].emplace_back(make_unique<CapturePromotion>(get(from), target,new Knight{col, to}, from, to));
        }
        else {
            moves[0].emplace_back(make_unique<Capture>(get(from), get(to), from, pair<int,int> {from.first-1, from.second + dir}));
        }
    }
}

bool Board::validPos(const pair<int,int> & pos) {
    return pos.first >= 0 && pos.second >=0 && pos.first < BOARD_SIZE && pos.second < BOARD_SIZE; 
}

bool Board::safeMove(const std::pair<int,int> & from, const std::pair<int,int> & to) {
    Piece * pf = get(from);
    Piece * pt = get(to);
    set(from, nullptr);
    set(to, pf);
    bool res = !isCheck();
    set(to, pt);
    set(from, pf);
    return res;
}

bool Board::kSafeMove(const std::pair<int,int> & to) {
    Piece * k = get(kingPos);
    set(kingPos, nullptr);
    bool res = !unsafe(to, k->getColour());
    set(kingPos, k);
    return res;
}


//pos = (col, row)
void Board::hvScan(const pair<int,int> & pos, vector<vector<unique_ptr<Move>>> & moves){
    //scan right
    for (int i = pos.first + 1;  i < BOARD_SIZE && insertMove(pos, pair<int, int>{i, pos.second}, moves); ++i);

    //scan left
    for (int i = pos.first - 1;  i >= 0 && insertMove(pos, pair<int, int>{i, pos.second}, moves); --i);

    //scan up
    for (int i = pos.second + 1;  i < BOARD_SIZE && insertMove(pos, pair<int, int>{pos.first, i}, moves); ++i);

    //scan down
    for (int i = pos.second - 1;  i >= 0 && insertMove(pos, pair<int, int>{pos.first, i}, moves); --i);
}

void Board::dScan(const pair<int,int> & pos, vector<vector<unique_ptr<Move>>> & moves){
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
    // right
    if (kingPos.first + 1 < BOARD_SIZE) {
        kInsertMove(pair<int, int>{kingPos.first+1, kingPos.second}, moves);
    }

    // left
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

    castleScan(moves);
}

void Board::nScan(const pair<int,int> & pos,vector<vector<unique_ptr<Move>>> & moves){
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

void Board::pScan(int col, int movesCount, int round, const pair<int,int> & pos, vector<vector<unique_ptr<Move>>> & moves){
    int dir = (col == 0) ? 1 : -1;
    // move (first time)
    pair<int,int> to{pos.first, pos.second+2*dir};
    if (movesCount == 0 && !board[pos.second+dir][pos.first] && !get(to) && safeMove(pos, to)) {
        moves[1].emplace_back(make_unique<Basic>(get(pos), pos, pair<int,int>{pos.first, pos.second + 2*dir}));
    }

    // other move / promotion
    pInsertMove(col, pos, moves);

    // en passant
    if (pos.second == 4-col /*white: 4, black: 3*/) {
        if (pos.first-1 >= 0) {
            pair<int,int> to{pos.first-1, pos.second};
            Pawn * target = dynamic_cast<Pawn *>(get(to));
            Piece * tmp = get(to);
            set(to, nullptr);    // ready for safeMove
            to.second += dir;
            if (target && target->getColour() != col && target->getRecentMove() == round-1 && target->getMovesCount() == 1 && safeMove(pos, to)) {
                moves[0].emplace_back(make_unique<Capture>(get(pos), target, pos, to));
            }
            to.second += dir;
            set(to, tmp);
        }
        if (pos.first+1 < BOARD_SIZE){
            pair<int,int> to{pos.first+1, pos.second};
            Pawn * target = dynamic_cast<Pawn *>(get(to));
            Piece * tmp = get(to);
            set(to, nullptr);    // ready for safeMove
            to.second += dir;
            if (target && target->getColour() != col && target->getRecentMove() == round-1 && target->getMovesCount() == 1 && safeMove(pos, to)) {
                moves[0].emplace_back(make_unique<Capture>(get(pos), target, pos, to));
            }
            to.second -= dir;
            set(to, tmp);
        }
    }
    
}


void Board::castleScan(std::vector<std::vector<std::unique_ptr<Move>>> & moves) {
    //Neither the king nor the rook has previously moved.
    //There are no pieces between the king and the rook.
    //The king is not currently in check.
    //The king does not pass through a square that is attacked by an opposing piece

    if (get(kingPos)->getMovesCount() == 0 && !isCheck()){

        //Right side
        // goes to the first piece encouted by scaning right, or stop if passes a position that is unsafe.
        pair<int,int> otherPos{kingPos.first + 1, kingPos.second};
        while (otherPos.first < BOARD_SIZE-1 && !get(otherPos) && !unsafe(otherPos, get(kingPos)->getColour())) {
            ++otherPos.first;
        }
        // check if the peice at the right edge has zero moveCount (i.e. can castle)
        if (otherPos.first == BOARD_SIZE-1 && get(otherPos) && get(otherPos)->getMovesCount() == 0){
            moves[1].emplace_back(make_unique<Castling>(get(kingPos), get(otherPos), kingPos, pair<int,int>{kingPos.first+2, otherPos.second}, otherPos, pair<int,int>{otherPos.first-2, otherPos.second}));
        }

        // Left Side
        //Right side
        // goes to the first piece encouted by scaning right, or stop if passes a position that is unsafe.
        otherPos.first = kingPos.first-1;
        while (otherPos.first >= 2  && !get(otherPos)  && !unsafe(otherPos, get(kingPos)->getColour())) {
            --otherPos.first;
        }
        // check if the peice at the left edge has zero moveCount (i.e. can castle)
        if (otherPos.first == 1 && !get(otherPos)) {
            otherPos.first -= 1;
        }
        if (otherPos.first == 0 && get(otherPos) && get(otherPos)->getMovesCount() == 0){
            moves[1].emplace_back(make_unique<Castling>(get(kingPos), get(otherPos), kingPos, pair<int,int>{kingPos.first-2, otherPos.second}, otherPos, pair<int,int>{otherPos.first+3, otherPos.second}));
        }
    }
}

/*
bool Board::checkIfThreat(std::pair<int, int> pos, int col, std::vector<PeiceTypes> typeList) {
    if (get(pos) != nullptr){
        for (PeiceTypes type : typeList) {
            if (std::dynamic_cast<type>(get(pos)) != nullptr) {
                if (get(pos)->getColour() != col) {
                    return true;
                }
            }
        }
    }

    return false;
}
*/

bool Board::isCheck() {
    return unsafe(kingPos, get(kingPos)->getColour());
}

bool Board::unsafe(pair<int, int> pos, int col) {

    // h, v, d scan
    for (const pair<int,int> & p : vector<pair<int,int>>{{1,0},{-1,0},{0,1},{0,-1},{1,1},{1,-1},{-1,1},{-1,-1}}) {
        pair<int, int> itPos{pos.first+p.first, pos.second+p.second};
        while (validPos(itPos)){
            if (get(itPos)){
                if (get(itPos)->getColour() != col && get(itPos)->threats(pos)) {
                    return true;
                }
                break;
            }
            itPos.first += p.first;
            itPos.second += p.second;
        }
    }
    
    // n scan
    for (const pair<int,int> & p : vector<pair<int,int>>{{1,2},{1,-2},{-1,2},{-1,-2},{2,1},{2,-1},{-2,1},{-2,-1}}) {
        pair<int, int> itPos{pos.first+p.first, pos.second+p.second};
        if (validPos(itPos) && get(itPos) && get(itPos)->getColour() != col && get(itPos)->threats(pos)) {
            return true;
        }
    }
    
    return false;
}


unique_ptr<Move> Board::makeMove(int colour,  std::string can) {
    pair<int,int>from{getX(can[0]), getY(can[1])};
    pair<int,int>to{getX(can[2]), getY(can[3])};
    if (can.length() == 4) {
        if (get(to)) {
            return make_unique<Capture>(get(from), get(to), from, to);
        }
        else {
            return make_unique<Basic>(get(from), from, to);
        }
    }
    else {
        if (get(to)) {
            return make_unique<CapturePromotion>(get(from), get(to), makePiece(colour, can[4], to) , from, to);
        }
        else {
            return make_unique<Promotion>(get(from), makePiece(colour, can[4], to) , from, to);
        }
    }
}