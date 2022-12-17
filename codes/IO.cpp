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
    decision = "";
    getline(in, decision);
    toLower(decision);
    if (decision == "") return true;        // select the pervious decision
    if (decision == "undo") return true;    // undo
    if (decision.length() == 1 && decision[0] >= '1' && decision[0] <= '9') return true;    // require program's help (decision[0] is the number of iterations)
    if (decision.length() == 4){
        return (validX(decision[0]) && validX(decision[2]) && validY(decision[1]) && validY(decision[3]));
    }   // move (not promotion)
    if (decision.length() == 5) {
        return validX(decision[0]) && validX(decision[2]) && validY(decision[1]) && validY(decision[3]) && (decision[4] == 'q' || decision[4] == 'r' || decision[4] == 'b' || decision[4] == 'n');
    }   // promotion
    return false;
}

void getDecision(istream & in, string & decision){
    while (!readDecision(cin, decision)) {
        err_decision(cerr);
        decisionInstruction(cerr);
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
    out << *(game.getBoard()) << endl;       // prints the board
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
        out << static_cast<char>('a'+ x) << ' ';
    }
    return out;
}

ostream & operator<<(ostream & out, const Player & player){
    out << "player" << player.getColour()+1 << ":" << endl;
    out << "pieces:" << endl;
    for (const auto & p : player.getPieces()) {
        out << *p << endl;
    }
    return out; 
}

ostream & operator<<(ostream & out, const Piece & piece){
    out << piece.getRepresentation() << ": position at (" << piece.getPosition().first << ", " <<  piece.getPosition().second << "), with status " << piece.getStatus();
    return out;
}

ostream & operator<<(std::ostream & out, const Move & move) {
    out << move.representation();
    return out;
}

/* check inputs */
int checkArgv(int argc, char * argv[]){
    if (argc == 3){
        toLower(argv[1][0]);
        toLower(argv[2][0]);
        if (!checkArgvPT(argv[1][0]) || !checkArgvPT(argv[2][0])) {
            err_argvType(cerr);
            return 0;
        }
    }
    else if (argc == 2) {
        toLower(argv[1][0]);
        if (!checkArgvC(argv[1][0])) {
            err_argvType(cerr);
            return 0;
        }
    }
    else {
        err_argc(cerr);
        return 0;
    }
    
    return 1;
}

bool checkArgvPT(const char & arg) {
    return arg == 'c' || arg == 'h';
}

bool checkArgvC(const char & arg){
    return arg == 'w' || arg == 'b';
}

void beginRoundNote(ostream & out, const Board & board, int round) {
    out << "round" << round/2 << ':' << endl;
    out << board << endl;
    out << "player(" << round%2 +1 << ")'s turn:" << endl; 
}

void endNote(ostream & out, int winner) {
    if (winner == -1) {
        out << "dawn" << endl;
    }
    else {
        out << "player(" << winner + 1 << ") win!" << endl;
    }
    out << "game ended" << endl;
}

/* error / warning messages */
void err_argc(ostream & out){
    out << "error: incorrect number of arguments" << endl;
    argvInstruction(cerr);
}
void err_argvType(ostream & out){
    out << "error: invalid type of arguments" << endl;
    argvInstruction(cerr);
}

void err_decision(ostream & out){
    out << "error: invalid move" << endl;
}

void err_emptyHist(std::ostream & out){
    out << "error: no more step to undo" << endl;
}

void warning_invalidMove(ostream & out){
    out << "warning: your move is not valid!" << endl;
}

/* instructions / messages */

void argvInstruction(ostream & out){
    out << "please make sure there are 1 arguments starts with 'w'(white) or 'b'(black) or 2 arguments that each either starts with 'h' (human) or 'c' computer" << endl;
}

void requireDecision(ostream & out) {
    out << "please make a move" << endl;
}

void decisionInstruction(ostream & out){
    out  << "please enter either:\n     a move in correct coordinate algebraic notation (e.g. e2e4), or\n     'undo' to undo a move, or \n [0-9] to get a hint, or \n enter to use the pervious decision (if there is)"  << endl;
}

void msgStartGame(ostream & out){
    out << "game started" << endl;
}

void printMoves(ostream & out, const vector<vector<unique_ptr<Move>>> & moves) {
    out << "capture moves: ";
    for (const auto & m : moves[0]) {
        out << (*m).representation() << ' ';
    }
    out << endl << "placeful moves: ";
    for (const auto & m : moves[1]) {
        out << (*m).representation() << ' ';
    }
    out << endl;
}

void printMoves(ostream & out, vector<unique_ptr<Move>> & moves) {
    out << endl << "moves: ";
    for (const auto & m : moves) {
        out << (*m).representation() << ' ';
    }
    out << endl;
}

/* helpers */

void toLower(std::string & s){
    for (char & c : s) {
        toLower(c);
    }
}

void toLower(char & c) {
    if (c >= 'A' && c <= 'Z') {
        c += 'a' - 'A';
    }
}