#include "Piece.h"
#include "Board.h"

using namespace std;

Piece::Piece(int colour, const pair<int,int> & pos): colour{colour}, status{1}, movesCount{0}, position{pos} {}

King::King(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Queen::Queen(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Bishop::Bishop(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Rook::Rook(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Knight::Knight(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Pawn::Pawn(int colour, const pair<int,int> & pos) :  Piece{colour, pos}, recentMove{-1} {}


void Piece::move(const pair<int,int> & to, int round){
    movePiece(to,  round);
}

void Piece::back(const pair<int,int> & from) {
    goBack(from);
}

void Piece::searchMoves(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) {
    scan(round, board, moves);
}

bool Piece::threats(const pair<int,int> & at) {
    return canAttack(at);
}

int Piece::getValue() const {   return value();   }

int Piece::getColour() const {   return colour;   }

//int Piece::getLastMove() const {   return lastMove;   }

int Piece::getStatus() const {   return status;   }

int Piece::getMovesCount() const {   return movesCount; }

char Piece::getRepresentation() const { return representation();    }

const pair<int,int> & Piece::getPosition() const{   return position;    }


void Piece::setStatus(int stat) {
    status = stat;
}

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


// virtual functions
void Piece::movePiece(const pair<int,int> & to, int round){
    position = to;
    movesCount += 1;
}

void Pawn::movePiece(const pair<int,int> & to, int round) {
    Piece::movePiece(to, round);
    recentMove.emplace_back(round);
}

void Piece::goBack(const pair<int,int> & from){
    position = from;
    movesCount -= 1;
}

void Pawn::goBack(const pair<int,int> & from){
    Piece::goBack(from);
    recentMove.pop_back();
}

void King::scan(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) const {
    board.kScan(moves);
}

void Queen::scan(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) const {
    board.hvScan(position, moves);
    board.dScan(position, moves);
}

void Bishop::scan(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) const {
    board.dScan(position, moves);
}

void Rook::scan(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) const {
    board.hvScan(position, moves);
}

void Knight::scan(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) const {
    board.nScan(position, moves);
}

void Pawn::scan(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) const {
    board.pScan(colour, movesCount, round, position, moves);
}

bool King::canAttack(const std::pair<int, int> & at){
    return position.first - at.first >= -1 && position.first - at.first <= 1 && position.second - at.second >= -1 && position.second - at.second <= 1;
}

bool Queen::canAttack(const std::pair<int, int> & at) {
    return position.first == at.first || position.second == at.second ||  position.first - at.first == position.second - at.second || position.first - at.first == - position.second + at.second;
}

bool Bishop::canAttack(const std::pair<int, int> & at) {
    return position.first - at.first == position.second - at.second || position.first - at.first == - position.second + at.second;
}

bool Rook::canAttack(const std::pair<int, int> & at) {
    return position.first == at.first || position.second == at.second;
}

bool Knight::canAttack(const std::pair<int, int> & at) {
    return (position.first-at.first == 2 && (position.second - at.second == 1 || position.second - at.second == -1)) || (position.first-at.first == -2 && (position.second - at.second == 1 || position.second - at.second == -1)) || (position.first-at.first == 1 && (position.second - at.second == 2 || position.second - at.second == -2)) || (position.first-at.first == -1 && (position.second - at.second == 1 || position.second - at.second == -2));
}

bool Pawn::canAttack(const std::pair<int, int> & at) {
    int dir = (colour == 0) ? -1 : 1;
    return at.second == position.second+dir && (at.first == position.first-1 || at.first == position.first+1);
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