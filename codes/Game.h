#ifndef GAME_H_
#define GAME_H_


#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <memory>
#include <queue>

class Board;
class Player;
class Move;


/* chess interface */
// Game is a class that owns the game board, players, and the history of move. 
class Game
{
    /* fields */
    int round;                                      // round count
    std::vector<std::unique_ptr<Player>> players;        // players
    std::vector<std::unique_ptr<Move>> history;          // game history

    /* functions */
private:
    void addPlayer(int i, char type);         // set player[i]
    int processRound();                        // handles a round, update the state
    void undoRound(Player & other);                           // undo a round

    std::string smartMove(std::vector<std::vector<std::unique_ptr<Move>>> & moves, int it);     // find an optimized move
    
    //finds best move (minmax)
    char findBestMoveWrapper(std::vector<std::unique_ptr<Move>> & moves, int depth, int player);
    double getPositionScoreAtDepth(std::vector<std::unique_ptr<Move>> & moves, Board & board, int depth, int player);
    double positionScore(int player);
    int determineDepth(int it);
    
public:
    // constructor, take an array of two char* in {"c","d"}:
    //  "d": human player, "c": computer player
    Game(char * players[3]);   
    // copy constructor (without copying history)                  
    Game(const Game & game);

    // starts a game
    void processGame();
    // initial setup          
    void init();

    std::unique_ptr<Board> getBoard() const;  // let players update the board
    const std::vector<std::unique_ptr<Player>> & getPlayer() const;

    const Player & getPlayerM() const;

    Player * playerM();             // returns the player that is going to make a move in the current round
    Player * playerW();             // returns the player that is going to make a move in the next round

    /* friend functions */
    friend std::ostream & operator<<(std::ostream & out, const Game & game);
};

// given a sorted vector of outcomes, returns the expected outcome by the sum of products of the first 8 elements in outcomes and the geometric series 1/2, 1/4, 1/8, ..., the last scalar is designed so that the sum of all scalars is always 1.
double expectedOutcome(std::vector<double> & outcomes, int upperBound);

// determines the rate of drop based on the size
int depthDrop(int size);

#endif