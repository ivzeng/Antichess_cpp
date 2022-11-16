#include "Game.h"
#include "Player.h"
#include "IO.h"

void Game::processRound(){
    Player * curPlayer = players[round%2].get(), * otherPlayer = players[(round+1)%2].get();
    otherPlayer->update();                  // updates the checking status
    curPlayer->updateMoves();               // updates the vaild moves of curPlayer 
    history.push_back(curPlayer->move());   // curPlayer makes a move
}

// starts the game
void Game::processGame(){
    while (state != 0){
        processRound();
    }
}

