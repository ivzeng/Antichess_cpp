#ifndef IO_H
#define IO_H

#include <iostream>
class Game;
class Board;

/*std in*/

/*std out*/
// overloads output operator, print the board (and other details?)
std::ostream & operator<<(std::ostream & out, const Game & game);

// prints the board
std::ostream & operator<<(std::ostream & out, const Board & board);

/*std err*/
// prints error code about the argument
void err_argc();                        // incorrect number of argv
void err_argvType();                    // incorrect type of argv

/* Instructions / Messages */
void argvInstruction();                 // hints for valid arguments
void msgStartGame();



#endif