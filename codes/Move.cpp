#include "Move.h"
#include "Piece.h"

using namespace std;

Move::Move() {}

Move::Move(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : piece{piece}, from{from}, to{to} {}

Move::~Move() {}

bool Move::operator==(const string & can){
    return getX(can[0]) == from.first && getY(can[1]) == from.second && getX(can[2]) == to.first && getX(can[3]) == to.second;
}

string Move::representation(){
    return getRepresentaion();
}

string Move::getRepresentaion(){
    string res{"    "};
    res[0] = from.first+'a';
    res[1] = from.second+'1';
    res[2] = to.first+'a';
    res[3] = to.second+'1';
    return res;
}

string Promotion::getRepresentaion(){
    return Move::getRepresentaion() + char{promotion->getRepresentation() < 'a' ? promotion->getRepresentation() + 'A' : promotion->getRepresentation()};
}


Basic::Basic(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to} {}

Capture::Capture(Piece * piece, Piece * capturedPiece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, capturedPiece{capturedPiece} {}

Promotion::Promotion(Piece * piece, Piece * promotion, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, promotion{promotion} {}

CapturePromotion::CapturePromotion(Piece * piece, Piece * promotion, Piece * captured, const pair<int,int> & from, const pair<int,int> & to) : Capture{piece, captured, from, to}, Promotion{piece, promotion, from, to} {}

Castling::Castling(Piece * piece, Piece * rook, const pair<int,int> & fromK, const pair<int,int> & toK, const std::pair<int,int> & fromR, const std::pair<int,int> & toR) : Move{piece, fromK, toK}, rook{rook} {}



int getX(const char & x){
    return (x < 'a') ? (x-'A') : (x-'a');
}
int getY(const char & y){
    return 8-(y-'0');
}

bool validX(const char & x){
    int xc = getX(x);
    return xc >= 0 && xc < 8;
}

bool validY(const char & y){
    return y >= '1' && y <= '8';
}


void search(string & move, const vector<vector<unique_ptr<Move>>> & moves){
    for (size_t i = 0; i < moves.size(); i += 1){
        for (size_t j = 0; j < moves[i].size(); j += 1){
            if ((*moves[i][j]) == move){
                move = "  1";
                move[0] = i;
                move[1] = j;
                while (i > 0) {
                    i -= 1;
                    if (moves[i].size() > 0){
                        move[2] = '0';
                        break;
                    }
                } // checks if the move is valid
                return;
            }
        }
    }
}

int getValidMove(const vector<vector<unique_ptr<Move>>> & moves) {
    int i = 0;
    while (i < 2 && moves[i].size() == 0){
        i += 1;
    }
    return i;
}
