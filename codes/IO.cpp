#include "IO.h"
#include "Game.h"

using namespace std;

/* std in */


/* std out */
ostream & operator<<(ostream & out, const Game & game){
    out << *(game.getBoard()) << endl;       // prints the board
    // Todo: more info
    return out; 
}

ostream & operator<<(ostream & out, const Board & board){
    for (int y = 7; y >=0; y += 1){
        out << y+1 << ' ';
        for (int x = 0; x < 8; x += 1){
            out << board[y][x] ? board[y][x]->getRepresentation : '-' << ' ';
        }
    }
    return out;
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
    cerr << "please make sure there are exactly 2 arguments \
    that either start with 'h' (human) or 'c' computer." << endl;
} 