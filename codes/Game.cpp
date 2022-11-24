#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "IO.h"

using namespace std;

Game::Game(char * player[3]): round{0}, state{1}, players{}, history{} {
    // set players
    addPlayer(0, player[1]);
    addPlayer(1, player[2]);
}

Game::Game(const Game & game): round{game.round}, state{game.state}, players{}, history{} {
    players.push_back(game.players[0].get()->uniqueCpy());
    players.push_back(game.players[1].get()->uniqueCpy());
}

void Game::addPlayer(int i, char * type){
    if (type[0] == 'c' || type[0] == 'C') {
        players.push_back( make_unique<AlphaWind>(i));
    }
    else if (type[0] == 'h' || type[0] == 'H') {
        players.push_back(make_unique<Human>(i));
    }
}

unique_ptr<Board> Game::getBoard() const{
    unique_ptr<Board> board = make_unique<Board>();
    players[0].get()->updateBoard(board.get());
    players[1].get()->updateBoard(board.get());
    return board;
}

const std::vector<std::unique_ptr<Player>> & Game::getPlayer() const {
    return players;
}

void Game::processRound(){
    Player * curPlayer = players[round%2].get();
    Player * otherPlayer = players[(round+1)%2].get();
    curPlayer->move(history);                       // curPlayer makes a move, store the move into history
    state = otherPlayer->updateStatus();            // check if the king of the opponent is gone?!
}

void Game::processGame(){
    init();
    // cerr << "initialized game" << endl;

    printGame(*this);
    /*
    while (state != 0){
        processRound();
    }
    */
}

void Game::init(){
    // cerr << players.size() << endl;
    players[0].get()->init();
    players[1].get()->init();
}

void Game::undoRound(){
    // Todo
}

