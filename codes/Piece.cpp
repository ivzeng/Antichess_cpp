#include "Piece.h"

using namespace std;

Piece::Piece(int colour, const pair<int,int> & pos): colour{colour}, status{1}, moveCount{0}, position{pos} {}

King::King(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Queen::Queen(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Bishop::Bishop(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Rook::Rook(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Knight::Knight(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Pawn::Pawn(int colour, const pair<int,int> & pos) :  Piece{colour, pos}, recentMove{-1} {}


void Piece::movePiece(const pair<int,int> & to, int round){
    position.first = to.first;
    position.second = to.second;
    moveCount += 1;
}

void Pawn::movePiece(const pair<int,int> & to, int round) {
    Piece::movePiece(to, round);
    recentMove.emplace_back(round);
}

void Piece::move(const pair<int,int> & to, int round){
    movePiece(to,  round);
}

int Piece::getValue() const {   return value();   }

int Piece::getColour() const {   return colour;   }

//int Piece::getLastMove() const {   return lastMove;   }

int Piece::getStatus() const {   return status;   }

char Piece::getRepresentation() const { return representation();    }

const pair<int,int> & Piece::getPosition() const{   return position;    }

unique_ptr<Piece> Piece::copy(){
    return clone();
}

int King::value() const {
    return 100;
}

int Queen::value() const {
    return 20;
}

int Bishop::value() const {
    return 10;
}

int Rook::value() const {
    return 11;  // I prefer Rook than Bishop
}

int Knight::value() const {
    return 8;
}

int Pawn::value() const {
    return 3;
}


void King::scan(int iv[SO_LEN]) const {
    iv[2] = 1;
}

void Queen::scan(int iv[SO_LEN]) const {
    iv[3] = 1;
    iv[4] = 1;  // horizontal, vertical and diagonal scan
}

void Bishop::scan(int iv[SO_LEN]) const {
    iv[4] = 1;  // diagonal scan
}

void Rook::scan(int iv[SO_LEN]) const {
    iv[3] = 1;  // horizontal and vertical scan
}

void Knight::scan(int iv[SO_LEN]) const {
    iv[5] = 1;  // knight's moves scan
}

void Pawn::scan(int iv[SO_LEN]) const {
    iv[6] = 1;  // Pawn's move scan
}

char King::representation() const {
    return (colour == 0) ? 'k' : 'K';
}

char Queen::representation() const {
    return (colour == 0) ? 'q' : 'Q';
}

char Bishop::representation() const {
    return (colour == 0) ? 'b' : 'B';
}

char Knight::representation() const {
    return (colour == 0) ? 'n' : 'N';
}

char Rook::representation() const {
    return (colour == 0) ? 'r' : 'R';
}

char Pawn::representation() const {
    return (colour == 0) ? 'p' : 'P';
}

unique_ptr<Piece> King::clone() {
    return make_unique<King>(*this);
}

unique_ptr<Piece> Queen::clone() {
    return make_unique<Queen>(*this);
} 

unique_ptr<Piece> Bishop::clone() {
    return make_unique<Bishop>(*this);
}

unique_ptr<Piece> Rook::clone() {
    return make_unique<Rook>(*this);
}

unique_ptr<Piece> Knight::clone() {
    return make_unique<Knight>(*this);
}

unique_ptr<Piece> Pawn::clone() {
    return make_unique<Pawn>(*this);
}