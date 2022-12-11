#ifndef IO_H
#define IO_H

#include <iostream>
class Game;
class Board;
class Piece;
class Player;

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

/* check inputs */
int checkArgv(int argc, char * argv[]);



/*std err*/
// prints error code about the argument
void err_argc(std::ostream & out);                        // incorrect number of argv
void err_argvType(std::ostream & out);                    // incorrect type of argv

void err_decision(std::ostream & out);                    // incorrect decision input

void warning_invalidMove(std::ostream & out);

/* Instructions / Messages */
void argvInstruction(std::ostream & out);                 // hints for valid arguments
void requireDecision(std::ostream & out);
void decisionInstruction(std::ostream & out);
void msgStartGame(std::ostream & out);



#endif