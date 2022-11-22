#include "Player.h"
#include "Piece.h"

using namespace std;

Player::Player(int colour): colour{colour}, pieces{vector<unique_ptr<Piece>>{}} {}

Player::Player(const Player & player): colour{player.colour}, pieces(vector<unique_ptr<Piece>> (player.pieces)) {}

void Player::init(){
    int y = 0 + 7*colour;       // 0 for white and 7 for black
    pieces.push_back(make_unique<King>(colour, pair<int,int>{3,y}));   // put king
    pieces.push_back(make_unique<Queen>(colour, pair<int,int>{4,y}));   // put queen
    pieces.push_back(make_unique<Bishop>(colour, pair<int,int>{2,y}));
    pieces.push_back(make_unique<Bishop>(colour, pair<int,int>{5,y}));  // put bishops
    pieces.push_back(make_unique<Knight>(colour, pair<int,int>{1,y}));
    pieces.push_back(make_unique<Knight>(colour, pair<int,int>{6,y}));  // put knights
    pieces.push_back(make_unique<Rook>(colour, pair<int,int>{0,y}));
    pieces.push_back(make_unique<Rook>(colour, pair<int,int>{7,y}));  // put Rooks
    
    y = 1 + 5*colour;           // 1 for white and 6 for black
    for (int x = 0; x < 8; x += 1){
        pieces.push_back(make_unique<Pawn>(colour, pair<int,int>{x,y}));
    }   // put Pawns
}

int Player::updateStatus(){
    return pieces[0].get()->getStatus();
}
