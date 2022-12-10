#include "IO.h"
#include "Game.h"
#include "Board.h"
#include "Player.h"
#include "Piece.h"
#include "Move.h"

using namespace std;

/* in */

// reads decision and checks
bool readDecision(istream & in, string & decision) {
    getline(in, decision);
    if (decision == "") return true;        // select the pervious decision
    if (decision == "undo") return true;    // undo
    if (decision.length() == 1 && decision[0] >= '1' && decision[0] <= '9') return true;    // require program's help (decision[0] is the number of iterations)
    if (decision.length() == 4){
        return (validX(decision[0]) && validX(decision[1]) && validY(decision[1]) && validY(decision[3]));
    }   // move (not promotion)
    if (decision.length() == 5) {
        return validX(decision[0]) && validX(decision[1]) && validY(decision[1]) && validY(decision[3]) && (decision[4] == 'p'||decision[4] == 'P');
    }   // promotion
    return false;
}

void getDecision(istream & in, string & decision){
    while (!readDecision(cin, decision)) {
        err_decision();
        decisionInstruction();
    }
}

/* print objects */
void printGame(const Game & game){
    cerr << game << endl;
}

ostream & operator<<(ostream & out, const Game & game){
    // out << "getting the board" << endl;
    out << *game.getPlayer()[0] << endl;
    out << *game.getPlayer()[1] << endl;
    out << *(game.getBoard());       // prints the board
    // Todo: more info
    return out; 
}

ostream & operator<<(ostream & out, const Board & board){
    for (int y = 7; y >=0; y -= 1){
        out << y+1 << ' ';
        for (int x = 0; x < 8; x += 1){
            out << board.getRepresentation(x,y) << ' ';
        }
        out << endl;
    }
    out << "  ";
    for (int x = 0; x < 8; x += 1){
        out << static_cast<char>('A'+ x) << ' ';
    }
    out << endl;
    return out;
}

ostream & operator<<(ostream & out, const Player & player){
    out << "player" << player.getColour() << ":" << endl;
    out << "pieces:" << endl;
    for (const auto & p : player.getPieces()) {
        out << *p << endl;
    }
    return out; 
}

ostream & operator<<(ostream & out, const Piece & piece){
    out << piece.getRepresentation() << ": position at (" << piece.getPosition().first << ", " <<  piece.getPosition().second << "), with status " << piece.getStatus() << endl;
    return out;
}

/* check inputs */
int checkArgv(int argc, char * argv[]){
    if (argc != 3){
        err_argc();
        return 0;
    }
    if ((argv[1][0] != 'h' && argv[1][0] != 'H' && argv[1][0] != 'c' && argv[1][0] != 'C') 
        || (argv[2][0] != 'h' && argv[2][0] != 'H' && argv[2][0] != 'c' && argv[2][0] != 'C') ){
        err_argvType();
        return 0;
    }
    return 1;
}


/* error / warning messages */
void err_argc(){
    cerr << "error: incorrect number of arguments;" << endl;
    argvInstruction();
}
void err_argvType(){
    cerr << "error: invalid type of arguments;" << endl;
    argvInstruction();
}

void err_decision(){
    cerr << "error: invalid move" << endl;
}

void warning_invalidMove(){
    cerr << "warning: your move is not valid!" << endl;
}

/* instructions / messages */

void argvInstruction(){
    cerr << "please make sure there are exactly 2 arguments that each either starts with 'h' (human) or 'c' computer." << endl;
}

void requireDecision() {
    cerr << "please make a move" << endl;
}

void decisionInstruction(){
    cerr << "please enter either:\n     a move in correct coordinate algebraic notation (e.g. e2e4), or\n     'undo' to undo a move, or \n [0-9] to get a hint, or \n enter to use the pervious decision (if there is)"  << endl;
}

void msgStartGame(){
    cerr << 'game started' << endl;
}