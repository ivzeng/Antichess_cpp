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

class twoPlayerBoard;
class Board;
class Player;
class Option;


/* chess interface */
// Game is a class that owns the game board, players, and the history of move. 
class Game
{
    /* fields */
    int round;                                      // round count
    int state;                                      // state
    std::unique_ptr<Board> board;                   // board
    std::unique_ptr<Player> players[2];             // players
    std::vector<Option> history;                    // game move history

    /* functions */
private:
    void processRound();                        // handles a round, update the state
    void undoRound();                           // undo a round

public:
    Game(char* players[2]);                     // constructor, take an array of two char* in {"c","d"}:
                                                //  "d": human player, "c": computer player
    ~Game();                                    // destructor
    void processGame();                         // starts a game
    void setup();                               // setups the game

    /* friend functions */
    friend std::ostream & operator<<(std::ostream & out, const Game & game);
};



#endif