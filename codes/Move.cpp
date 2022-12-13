#include "Move.h"
#include "Piece.h"
#include "Player.h"
#include "IO.h"

using namespace std;

Move::Move(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : piece{piece}, from{from}, to{to} {}

Move::Move() {}


bool Move::operator==(const string & can){
    return getX(can[0]) == from.first && getY(can[1]) == from.second && getX(can[2]) == to.first && getY(can[3]) == to.second;
}

void Move::process(int round,Player & player) {
    act(round, player);
}

void Move::undo(Player & player) {
    reverse(player);
}

string Move::representation() const{
    return getRepresentaion();
}

string Move::getRepresentaion() const{
    string res{"    "};
    res[0] = from.first+'a';
    res[1] = from.second+'1';
    res[2] = to.first+'a';
    res[3] = to.second+'1';
    return res;
}

string Promotion::getRepresentaion() const{
    string rep = Move::getRepresentaion() + promotion->getRepresentation();
    if  (promotion->getRepresentation() < 'a') {
        rep[4] += 'a'-'A';
    }
    return rep;
}


Basic::Basic(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to} {}

Capture::Capture(Piece * piece, Piece * capturedPiece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, capturedPiece{capturedPiece} {}

Promotion::Promotion(Piece * piece, Piece * promotion, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, promotion{promotion} {}

CapturePromotion::CapturePromotion(Piece * piece, Piece * captured, Piece * promotion, const pair<int,int> & from, const pair<int,int> & to) : Promotion{piece, promotion, from, to}, capturedPiece{captured} {}

Castling::Castling(Piece * piece, Piece * rook, const pair<int,int> & fromK, const pair<int,int> & toK, const std::pair<int,int> & fromR, const std::pair<int,int> & toR) : Move{piece, fromK, toK},rookMove{new Basic{rook, fromR, toR}} {}

void Basic::act(int round, Player & player) {
    piece->move(to, round);
}

void Basic::reverse(Player & player) {
    piece->back(from);
}

void Capture::act(int round, Player & player) {
    piece->move(to, round);
    capturedPiece->setStatus(0);
}

void Capture::reverse(Player & player) {
    piece->back(from);
    capturedPiece->setStatus(1);
}

void Promotion::act(int round, Player & player) {
    piece->setStatus(0);
    player.addPiece(promotion);
}

void Promotion::reverse(Player & player) {
    piece->setStatus(1);
    player.popPiece();
}

void CapturePromotion::act(int round, Player & player) {
    piece->setStatus(0);
    capturedPiece->setStatus(0);
    player.addPiece(promotion);
}

void CapturePromotion::reverse(Player & player) {
    piece->setStatus(1);
    capturedPiece->setStatus(1);
    player.popPiece();
}

void Castling::act(int round, Player & player) {
    (*rookMove).process(round, player);
    piece->move(to, round);
}

void Castling::reverse(Player & player) {
    (*rookMove).undo(player);
    piece->back(from);
}

int getX(const char & x){
    return (x < 'a') ? (x-'A') : (x-'a');
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
    for (size_t i = 0; i < moves.size(); i += 1){
        for (size_t j = 0; j < moves[i].size(); j += 1){
            if ((*moves[i][j]) == move){
                #ifdef DEBUG
                cerr << "searchMove()" << endl;
                #endif
                move = "  1";
                move[0] = i + '0';
                move[1] = j + '0';
                while (i > 0) {
                    i -= 1;
                    if (moves[i]
                    .size() > 0){
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


