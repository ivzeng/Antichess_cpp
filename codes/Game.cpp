#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Move.h"
#include "IO.h"

using namespace std;

Game::Game(char * player[2]): round{0}, state{1},\
    board{make_unique<Board>()}, history{vector<Move>{}} {
    // set players
    setPlayer(0, player[0]);
    setPlayer(1, player[1]);
}

void Game::setPlayer(int i, char * type){
    if (type[0] == 'c' || type[0] == 'C') {
        players[i] = make_unique<Computer>(i); 
    }
    else if (type[0] == 'h' || type[0] == 'H') {
        players[i] = make_unique<Computer>(i); 
    }
}

Board * Game::getBoard() const{
    return board.get();
}

void Game::processRound(){
    Player * curPlayer = players[round%2].get(), \
    * otherPlayer = players[(round+1)%2].get();
    curPlayer->updateMoves();                       // updates the vaild moves of curPlayer 
    curPlayer->move(history);                       // curPlayer makes a move
    state = otherPlayer->updateStatus();            // check if the king of the opponent is gone?!
}

// starts the game
void Game::processGame(){
    while (state != 0){
        processRound();
    }
}

