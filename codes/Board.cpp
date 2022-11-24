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

//pos = (col, row)
void Board::hvScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    //scan up
    for (int i = pos.first + 1;  i < boardSize; ++i){
        if (board[i][pos.second] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(i, pos.second>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(i, pos.second>)));
            break;
        }
    }

    //scan down
    for (int i = pos.first - 1;  i >= 0; --i){
        if (board[i][pos.second] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(i, pos.second>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(i, pos.second>)));
            break;
        }
    }

    //scan right
    for (int i = pos.second + 1;  i < boardSize; ++i){
        if (board[pos.first][i] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, i>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, i>)));
            break;
        }
    }

    //scan left
    for (int i = pos.second - 1;  i >= 0; --i){
        if (board[pos.first][i] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, i>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, i>)));
            break;
        }
    }
}

void Board::dScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    //Scan up and right
    for (int c = pos.first + 1, int r = pos.second + 1; c < boardSize && r < boardSize; ++c, ++r){
        if (board[c][r] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
            break;
        }
    }

    //Scan up and left
    for (int c = pos.first + 1, int r = pos.second - 1; c < boardSize && r >= 0; ++c, --r){
        if (board[c][r] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
            break;
        }
    }

    //Scan down and right
    for (int c = pos.first - 1, int r = pos.second + 1; c >= 0 && r < boardSize; --c, ++r){
        if (board[c][r] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
            break;
        }
    }

    //Scan down and left
    for (int c = pos.first - 1, int r = pos.second - 1; c >= 0 && r >= 0; --c, --r){
        if (board[c][r] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(c, r>)));
            break;
        }
    }
}

void Board::kScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    //up 
    if (pos.first + 1 < boardSize) {
        if (board[pos.first + 1][pos.second] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first + 1, pos.second>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first + 1, pos.second>)));
            break;
        }
    }

    //down
    if (pos.first - 1 >= 0) {
        if (board[pos.first - 1][pos.second] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first - 1, pos.second>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first - 1, pos.second>)));
            break;
        }
    }

    //left
    if (pos.second - 1 >= 0) {
        if (board[pos.first][pos.second - 1] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, pos.second - 1>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, pos.second - 1>)));
            break;
        }
    }

    //right
    if (pos.second + 1 < boardSize) {
        if (board[pos.first][pos.second + 1] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, pos.second + 1>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first, pos.second + 1>)));
            break;
        }
    }

    //up right
    if (pos.first + 1 < boardSize, pos.second + 1 < boardSize) {
        if (board[pos.first + 1][pos.second + 1] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first + 1, pos.second + 1>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first + 1, pos.second + 1>)));
            break;
        }
    }

    //up left
    if (pos.first + 1 < boardSize && pos.second - 1 >= 0) {
        if (board[pos.first + 1][pos.second - 1] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first + 1, pos.second - 1>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first + 1, pos.second - 1>)));
            break;
        }
    }

    //down right
    if (pos.first - 1 >= 0 && pos.second + 1 < boardSize){
        if (board[pos.first - 1][pos.second + 1] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first - 1, pos.second + 1>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first - 1, pos.second + 1>)));
            break;
        }
    }

    //down left
    if (pos.first - 1 >= 0 && pos.second - 1 >= 0) {
        if (board[pos.first - 1][pos.second - 1] == nullptr) {
            moves[0].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first - 1, pos.second - 1>)));
        }else {
            moves[1].emplace_back(make_unique<Basic>(get(pos), pos, std::pair<int, int>(pos.first - 1, pos.second - 1>)));
            break;
        }
    }

}

void Board::nScan(pair<int,int> pos,vector<vector<unique_ptr<Move>>> & moves){
    // Todo
}

void Board::pScan(int col, int movesCount, pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    // Todo
}

bool Board::isCheck(std::pair<int, int> pos) {
    // Todo
}

void Board::scan(int iv[9], vector<vector<unique_ptr<Move>>> & moves){
    std::pair<int,int> pos{iv[0],iv[1]};
    if (iv[4]) {
        kScan(pos, moves);
    }
    if (iv[5]) {
        hvScan(pos, moves);
    }
    if (iv[6]) {
        dScan(pos, moves);
    }
    if (iv[7]) {
        nScan(pos, moves);
    }
    if (iv[8]) {
        pScan(iv[2], iv[3],pos, moves);
    }
} 

Piece * Board::get(int x, int y) const {
    return board[y][x];
}

Piece * Board::get(std::pair<int, int> pos) const {
    return board[pos.first][pos.second];
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
