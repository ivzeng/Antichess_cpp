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

void Board::hvScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    // Todo
}

void Board::dScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    // Todo
}

void Board::kScan(pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
    // Todo
}

void Board::nScan(pair<int,int> pos,vector<vector<unique_ptr<Move>>> & moves){
    // Todo
}

void Board::pScan(int col, int movesCount, pair<int,int> pos, vector<vector<unique_ptr<Move>>> & moves){
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

char Board::getRepresentation(int x, int y) const {
    return get(x,y) ? get(x,y)->getRepresentation() : '-';
}

void Board::set(int x, int y, Piece * p) {
    board[y][x] = p;
} 

void Board::set(const pair<int,int> & position, Piece * p) {
    board[position.second][position.first] = p;
}

