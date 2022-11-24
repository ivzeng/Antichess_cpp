#include "Player.h"
#include "Piece.h"
#include "Board.h"
#include "Move.h"

using namespace std;

Player::Player(int colour): colour{colour}, pieces{vector<unique_ptr<Piece>>{}} {}

Human::Human(int colour): Player{colour} {}

AlphaWind::AlphaWind(int colour):  Player{colour} {}

Player::Player(const Player & player): colour{player.colour} {
    pieces.reserve(player.pieces.size());
    for (const auto & piece : player.pieces){
        pieces.push_back(unique_ptr<Piece>(piece.get()->uniqueCpy()));
    }
}

Human::Human(const Human & human): Player{human} {}

AlphaWind::AlphaWind(const AlphaWind & alphaWind): Player{alphaWind} {}

void Player::init(){
    int y = 0 + 7*colour;       // 0 for white and 7 for black
    pieces.push_back(make_unique<King>(colour, pair<int,int>{3,y}));    // put king
    pieces.push_back(make_unique<Queen>(colour, pair<int,int>{4,y}));   // put queen
    pieces.push_back(make_unique<Bishop>(colour, pair<int,int>{2,y}));
    pieces.push_back(make_unique<Bishop>(colour, pair<int,int>{5,y}));  // put bishops
    pieces.push_back(make_unique<Knight>(colour, pair<int,int>{1,y}));
    pieces.push_back(make_unique<Knight>(colour, pair<int,int>{6,y}));  // put knights
    pieces.push_back(make_unique<Rook>(colour, pair<int,int>{0,y}));
    pieces.push_back(make_unique<Rook>(colour, pair<int,int>{7,y}));    // put Rooks
    
    y = 1 + 5*colour;           // 1 for white and 6 for black
    for (int x = 0; x < 8; x += 1){
        pieces.push_back(make_unique<Pawn>(colour, pair<int,int>{x,y}));
    }   // put Pawns
}

int Player::updateStatus(){
    return pieces[0].get()->getStatus();
}

void Player::updateBoard(Board * board) {
    for (auto & p : pieces){
        if ((*p).getStatus()) {
            board->set((*p).getPosition(), p.get());
        }
    }
}

vector<vector<unique_ptr<Move>>> Player::searchMoves(const Board & board) {
    vector<vector<unique_ptr<Move>>> res{};
    // Todo
    return res;
}

void Player::move(vector<unique_ptr<Move>> & hist) {
    makeMove(hist);
}

void Human::makeMove(vector<unique_ptr<Move>> & hist) {
    // Todo
}

void AlphaWind::makeMove(vector<unique_ptr<Move>> & hist) {
    // Todo
}


unique_ptr<Player> Player::uniqueCpy(){
    return clone();
}

unique_ptr<Player> Human::clone(){
    return make_unique<Human>(*this);
}

unique_ptr<Player> AlphaWind::clone(){
    return make_unique<AlphaWind>(*this);
}

int Player::getColour() const {
    return colour;
}

const vector<unique_ptr<Piece>> & Player::getPieces() const {
    return pieces;
}
