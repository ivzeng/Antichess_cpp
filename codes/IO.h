#ifndef IO_H
#define IO_H

#include <iostream>
class Game;
class Board;
class Piece;
class Player;

/*std in*/

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
void err_argc();                        // incorrect number of argv
void err_argvType();                    // incorrect type of argv

/* Instructions / Messages */
void argvInstruction();                 // hints for valid arguments
void msgStartGame();



#endif