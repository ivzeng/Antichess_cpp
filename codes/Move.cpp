#include "Move.h"
#include "Piece.h"

using namespace std;

Move::Move(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : piece{piece}, from{from}, to{to} {}

Move::~Move() {}

bool Move::operator==(const string & can){
    return getX(can[0]) == from.first && getY(can[1]) == from.second && getX(can[2]) == to.first && getX(can[3]) == to.second;
}

Basic::Basic(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to} {}

Capture::Capture(Piece * piece, Piece * capturedPiece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, capturedPiece{capturedPiece} {}

Promotion::Promotion(Piece * piece, Piece * promotion, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, promotion{promotion} {}

Castling::Castling(Piece * piece, Piece * rook, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, rook{rook} {}



int getX(const char & x){
    if (x < 'a') return (x-'A');
    return x-'a';
}
int getY(const char & y){
    return y-'1';
}

bool validX(const char & x){
    int xc = getX(x);
    return xc >= 0 && xc < 8;
}

bool validY(const char & y){
    return y >= '1' && y <= '8';
}


void search(string & move, const vector<vector<unique_ptr<Move>>> & moves){
    for (int i = 0; i < 4; i += 1){
        for (size_t j = 0; j < moves[i].size(); j += 1){
            if ((*moves[i][j]) == move){
                move = "  ";
                move[0] = i;
                move[1] = j;
                return;
            }
        }
    }
}