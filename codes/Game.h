#ifndef GAME_H_
#define GAME_H_

//#include <X11/Xlib.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
//#include "../Pieces/Move/move.h"

class twoPlayerBoard;   // game board
class Board;            // abstract board
//class Score;          // score
class Player;           // player
class Move;             // move


/* chess interface */
// Game is a class that owns the game board, players, and the history of move. 
class Game
{
    // fields
    int round;                                  // round count
    std::unique_ptr<Board> board;               // abstract board
    //std::unique_ptr<Score> score;               // score
    //std::string mode;                           // the modes of the game (game, setup, menu)
    std::unique_ptr<Player> players[2];         // players
    bool whitemoves;                            // true if it is white's turn
    std::vector<std::unique_ptr<Move>> history; // game move history

    // class functions
private:
    void processRound();                        // handles a round

public:
    Game(char* players[2]);                       // constructor, take an array of two integers in {1,2}:
                                                //  1: human player, 2: computer player
    virtual ~Game();                            // destructor
    void processGame();                         // starts a game
    void setup();                               // setups the game

    // friends
    friend std::ostream & operator<<(std::ostream & out, const Game & game);
};



#endif