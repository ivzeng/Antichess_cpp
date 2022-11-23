#include "Piece.h"

using namespace std;

Piece::Piece(int colour, const pair<int,int> & pos): colour{colour}, status{1}, position{pos} {}

Piece::Piece(const Piece & piece) : colour{piece.colour}, status{piece.status}, position{piece.position} {}

King::King(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Queen::Queen(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Bishop::Bishop(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Rook::Rook(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Knight::Knight(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Pawn::Pawn(int colour, const pair<int,int> & pos) : recentMove{-1}, movesCount{0}, Piece{colour, pos} {}


void Piece::movePiece(const pair<int,int> & to, int round){
    position.first = to.first;
    position.second = to.second;
}

void Pawn::movePiece(const pair<int,int> & to, int round) {
    Piece::movePiece(to, round);
    recentMove = round;
    movesCount += 1;
}

void Piece::move(const pair<int,int> & to, int round){
    movePiece(to,  round);
}

int Piece::getValue() const {   return value();   }

int Piece::getColour() const {   return colour;   }

//int Piece::getLastMove() const {   return lastMove;   }

int Piece::getStatus() const {   return status;   }

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


void King::scan(int iv[IV_LEN]) const {
    iv[2] = 1;
}

void Queen::scan(int iv[IV_LEN]) const {
    iv[3] = 1;
    iv[4] = 1;  // horizontal, vertical and diagonal scan
}

void Bishop::scan(int iv[IV_LEN]) const {
    iv[4] = 1;  // diagonal scan
}

void Rook::scan(int iv[IV_LEN]) const {
    iv[3] = 1;  // horizontal and vertical scan
}

void Knight::scan(int iv[IV_LEN]) const {
    iv[5] = 1;  // knight's moves scan
}

void Pawn::scan(int iv[IV_LEN]) const {
    iv[6] = 1;  // Pawn's move scan
}