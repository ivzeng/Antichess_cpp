#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "IO.h"

using namespace std;

Game::Game(char * player[2]): round{0}, state{1}, players{vector<unique_ptr<Player>>(2, nullptr)}, history{vector<unique_ptr<Move>>{}} {
    // set players
    setPlayer(0, player[0]);
    setPlayer(1, player[1]);
}

Game::Game(const Game & game): round{game.round}, state{game.state}, players{vector<unique_ptr<Player>>(2, nullptr)}, history{vector<unique_ptr<Move>>{}} {
    players[0] = make_unique<Player>(*(game.players[0]));
    players[1] = make_unique<Player>(*(game.players[1]));
}

void Game::setPlayer(int i, char * type){
    if (type[0] == 'c' || type[0] == 'C') {
        players[i] = make_unique<AlphaWind>(i); 
    }
    else if (type[0] == 'h' || type[0] == 'H') {
        players[i] = make_unique<Human>(i); 
    }
}

unique_ptr<Board> & Game::getBoard() const{
    unique_ptr<Board> board = make_unique<Board>();
    players[1].get()->updateBoard(board.get());
    players[2].get()->updateBoard(board.get());
    return board;
}

void Game::processRound(){
    Player * curPlayer = players[round%2].get();
    Player * otherPlayer = players[(round+1)%2].get();
    curPlayer->move(history);                       // curPlayer makes a move, store the move into history
    state = otherPlayer->updateStatus();            // check if the king of the opponent is gone?!
}

void Game::processGame(){
    init();
    while (state != 0){
        processRound();
    }
}

void Game::init(){
    players[0].get()->init();
    players[1].get()->init();
}

