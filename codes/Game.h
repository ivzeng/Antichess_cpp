#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>

class Board;
class Player;
class Move;


/* chess interface */
// Game is a class that owns the game board, players, and the history of move. 
class Game
{
    /* fields */
    int round;                                      // round count
    int state;                                      // state
    //  std::unique_ptr<Board> board;               // board     edit: I don't think we need this field, instead, we can get it with function getBoard (since we only need it for scaning (in processRound()))
    std::vector<std::unique_ptr<Player>> players;        // players
    std::vector<std::unique_ptr<Move>> history;          // game history

    /* functions */
private:
    void addPlayer(int i, char * type);         // set player[i]
    void processRound();                        // handles a round, update the state
    void undoRound();                           // undo a round

public:
    Game(char * players[3]);                     // constructor, take an array of two char* in {"c","d"}:
                                                //  "d": human player, "c": computer player
    Game(const Game & game);                    // copy constructor (without copying history)
    //~Game();                                    // destructor
    void processGame();                         // starts a game
    void init();                                // initial setup

    std::unique_ptr<Board> getBoard() const;  // let players update the board
    const std::vector<std::unique_ptr<Player>> & getPlayer() const;

    /* friend functions */
    friend std::ostream & operator<<(std::ostream & out, const Game & game);
};



#endif