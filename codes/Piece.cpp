#include "Piece.h"

using namespace std;

Piece::Piece(int colour, const pair<int,int> & pos): colour{colour}, value{-1}, status{1}, position{pos} {}

Piece::Piece(const Piece & piece) : colour{piece.colour}, value{piece.value}, status{piece.status}, position{piece.position} {}

King::King(int colour, const pair<int,int> & pos) : Piece{colour, pos} {
    value = 100;
}

Queen::Queen(int colour, const pair<int,int> & pos) : Piece{colour, pos} {
    value = 20;
}

Bishop::Bishop(int colour, const pair<int,int> & pos) : Piece{colour, pos} {
    value = 10;
}

Rook::Rook(int colour, const pair<int,int> & pos) : Piece{colour, pos} {
    value = 12;
}

Knight::Knight(int colour, const pair<int,int> & pos) : Piece{colour, pos} {
    value = 8;
}

Pawn::Pawn(int colour, const pair<int,int> & pos) : recentMove{-1}, movesCount{0}, Piece{colour, pos} {
    value = 3;
}


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

int Piece::getValue() const {   return value;   }

int Piece::getColour() const {   return colour;   }

//int Piece::getLastMove() const {   return lastMove;   }

int Piece::getStatus() const {   return status;   }
