#include <cmath>

#include "Piece.h"
#include "Board.h"
#include "IO.h"

using namespace std;

Piece::Piece(int colour, const pair<int,int> & pos): colour{colour}, status{1}, movesCount{0}, position{pos} {}

Piece::~Piece() {}

King::King(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Queen::Queen(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Bishop::Bishop(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Rook::Rook(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Knight::Knight(int colour, const pair<int,int> & pos) : Piece{colour, pos} {}

Pawn::Pawn(int colour, const pair<int,int> & pos) :  Piece{colour, pos}, recentMoves{} {}


void Piece::move(const pair<int,int> & to, int round){
    movePiece(to,  round);
}

void Piece::back(const pair<int,int> & from) {
    goBack(from);
}

void Piece::searchMoves(int round, Board & board, vector<vector<unique_ptr<Move>>> & moves) {
    if (status) {
        scan(round, board, moves);
    }
}

bool Piece::threats(const pair<int,int> & at) {
    return canAttack(at);
}

double Piece::getValue(int round) const {
    return (double) value(round);
}

int Piece::getColour() const {   return colour;   }

//int Piece::getLastMove() const {   return lastMove;   }

int Piece::getStatus() const {   return status;   }

int Piece::getMovesCount() const {   return movesCount; }

char Piece::getRepresentation() const { return representation();    }

const pair<int,int> & Piece::getPosition() const{   return position;    }


int Pawn::getRecentMove() const{
    return recentMoves.back();
}

void Piece::setStatus(int stat) {
    status = stat;
}

unique_ptr<Piece> Piece::copy(){
    return clone();
}

double King::value(int round) const {
    return 1000;
}

double Queen::value(int round) const {
    return 100 + (-1+round/(double)40) * (double) verticalAdj();
}

double Bishop::value(int round) const {
    return 50 + (-1+round/(double)30) * (double) verticalAdj();
}

double Rook::value(int round) const {
    return 60 + (-1+round/(double)30) * (double) verticalAdj();;
}

double Knight::value(int round) const {
    return 40;
}

double Pawn::value(int round) const {
    return 10 + (double) pow(verticalAdj(),2) /(double)3;
}

double Piece::verticalAdj() const{
    return (colour == 0 ? position.second : BOARD_SIZE-position.second-1);
}

// virtual functions
void Piece::movePiece(const pair<int,int> & to, int round){
    position = to;
    movesCount += 1;
}

void Pawn::movePiece(const pair<int,int> & to, int round) {
    Piece::movePiece(to, round);
    recentMoves.emplace_back(round);
}

void Piece::goBack(const pair<int,int> & from){
    position = from;
    movesCount -= 1;
}

void Pawn::goBack(const pair<int,int> & from){
    Piece::goBack(from);
    recentMoves.pop_back();
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
    return (position.first-at.first == 2 && (position.second - at.second == 1 || position.second - at.second == -1)) || 
    (position.first-at.first == -2 && (position.second - at.second == 1 || position.second - at.second == -1)) || 
    (position.first-at.first == 1 && (position.second - at.second == 2 || position.second - at.second == -2)) || 
    (position.first-at.first == -1 && (position.second - at.second == 2 || position.second - at.second == -2));
}

bool Pawn::canAttack(const std::pair<int, int> & at) {
    int dir = (colour == 0) ? 1 : -1;
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

Piece * makePiece(int colour, const char & p, const std::pair<int,int> & pos){
    switch (p)
    {
    case 'q':
    case 'Q':
        return new Queen(colour, pos);
        break;
    case 'r':
    case 'R':
        return new Rook(colour, pos);
        break;
    case 'b':
    case 'B':
        return new Bishop(colour, pos);
        break;
    case 'n':
    case 'N':
        return new Knight(colour, pos);
        break;
    default:
        return nullptr;
        break;
    }
}