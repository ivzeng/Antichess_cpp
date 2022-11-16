#include "IO.h"
#include "Game.h"

using namespace std;

/* std in */


/* std out */
ostream & operator<<(ostream & out, const Game & game){
    out << *game.board.get();       // print the board
    // Todo: more info
    return out; 
}

ostream & operator<<(ostream & out, const Board & board){
    // Todo
}

/* std err */
void err_argc(){
    cerr << "error: incorrect number of arguments;" << endl;
    argvInstruction();
}
void err_argvType(){
    cerr << "error: invalid type of arguments;" << endl;
    argvInstruction();
}
void argvInstruction(){
    cerr << "please make sure there are exactly 2 arguments that are either character 'h' (human) or 'c' computer." << endl;
} 