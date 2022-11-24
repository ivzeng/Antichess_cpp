#include "Move.h"
#include "Piece.h"

using namespace std;

Move::Move(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : piece{piece}, from{from}, to{to} {}

Move::~Move() {}

Basic::Basic(Piece * piece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to} {}

Capture::Capture(Piece * piece, Piece * capturedPiece, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, capturedPiece{capturedPiece} {}

Promotion::Promotion(Piece * piece, Piece * promotion, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, promotion{promotion} {}

Castling::Castling(Piece * piece, Piece * rook, const pair<int,int> & from, const pair<int,int> & to) : Move{piece, from, to}, rook{rook} {}
