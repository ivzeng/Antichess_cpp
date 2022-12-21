#ifndef IO_H
#define IO_H

//#define DEBUG
//#define PLAY


#include <iostream>
#include <vector>
#include <memory>
class Game;
class Board;
class Piece;
class Player;
class Move;

/*std in*/
bool readDecision(std::istream & in, std::string & decision);
void getDecision(std::istream & in, std::string & decision);


/* print objects */

// print the game
void printGame(const Game & game);

// overloads output operator, print the board (and other details?)
std::ostream & operator<<(std::ostream & out, const Game & game);

// prints the board
std::ostream & operator<<(std::ostream & out, const Board & board);

// print player's info
std::ostream & operator<<(std::ostream & out, const Player & player);

// print piece
std::ostream & operator<<(std::ostream & out, const Piece & Piece);

std::ostream & operator<<(std::ostream & out, const Move & move);


// print the moves set
void printMoves(std::ostream & out, const std::vector<std::vector<std::unique_ptr<Move>>> & moves);
void printMoves(std::ostream & out, std::vector<std::unique_ptr<Move>> & moves);

void beginRoundNote(std::ostream & out, const Board & board, int round);            // prints the board, player to move and round number

void endNote(std::ostream & out, int winner = -1);


/* check inputs */
int checkArgv(int argc, char * argv[]);
bool checkArgvPT(const char & arg); // convert argv[0] to lower case and checks if argv start with 'p' or 'c'

bool checkArgvC(const char & arg); // checks if the argv is a valid colour (starts with either 'w' or 'b' (to lower case))

/*std err*/
// prints error code about the argument
void err_argc(std::ostream & out);                        // incorrect number of argv
void err_argvType(std::ostream & out);                    // incorrect type of argv

void err_decision(std::ostream & out);                    // incorrect decision input

void err_emptyHist(std::ostream & out); // attempt to undo while the history is empty

void warning_invalidMove(std::ostream & out);

/* Instructions / Messages */
void argvInstruction(std::ostream & out);                 // hints for valid arguments
void requireDecision(std::ostream & out);               // asks for a decision
void decisionInstruction(std::ostream & out);           // describes the way to enter a decision

void msgStartGame(std::ostream & out);  


/* other helpers */
void toLower(std::string & s);

void toLower(char & c);


#endif