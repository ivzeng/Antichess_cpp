#include "IO.h"
#include "Game.h"
#include "Board.h"

using namespace std;

/* in */


/* print objects */
ostream & operator<<(ostream & out, const Game & game){
    out << *(game.getBoard()) << endl;       // prints the board
    // Todo: more info
    return out; 
}

ostream & operator<<(ostream & out, const Board & board){
    for (int y = 7; y >=0; y += 1){
        out << y+1 << ' ';
        for (int x = 0; x < 8; x += 1){
            out << board.getRepresentation(x,y) << ' ';
        }
        out << endl;
    }
    out << "  ";
    for (int x = 0; x < 8; x += 1){
        out << 'A'+ x << ' ';
    }
    out << endl;
    return out;
}

/* check input */
int checkArgv(int argc, char * argv[]){
    if (argc != 2){
        err_argc();
        return 0;
    }
    if ((argv[0][0] != 'h' && argv[0][0] != 'H' && argv[0][0] != 'c' && argv[0][0] != 'C') 
        || (argv[1][0] != 'h' && argv[1][0] != 'H' && argv[1][0] != 'c' && argv[1][0] != 'C') ){
        err_argvType();
        return 0;
    }
    return 1;
}
 

/* error messages */
void err_argc(){
    cerr << "error: incorrect number of arguments;" << endl;
    argvInstruction();
}
void err_argvType(){
    cerr << "error: invalid type of arguments;" << endl;
    argvInstruction();
}

/* instructions */

void argvInstruction(){
    cerr << "please make sure there are exactly 2 arguments that each either starts with 'h' (human) or 'c' computer." << endl;
}
