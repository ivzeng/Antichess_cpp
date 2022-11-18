#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Option.h"
#include "IO.h"

using namespace std;

Game::Game(char * player[2]): round{0}, state{1}, board{make_unique<Board>()}, history{vector<Option>{}} {
    // set players
    setPlayer(0, player[0]);
    setPlayer(1, player[1]);
}

void Game::setPlayer(int i, char * type){
    if (type[0] == 'c') {
        players[i] = make_unique<Computer>(i); 
    }
}

void Game::processRound(){
    Player * curPlayer = players[round%2].get(), * otherPlayer = players[(round+1)%2].get();
    curPlayer->updateStatus();                      // updates the checking status
    curPlayer->updateMoves();                       // updates the vaild moves of curPlayer 
    curPlayer->move(history);                       // curPlayer makes a move
}

// starts the game
void Game::processGame(){
    while (state != 0){
        processRound();
    }
}

