#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "IO.h"


using namespace std;

Game::Game(char * player[3]): round{0}, players{}, history{} {
    // set players
    addPlayer(0, player[1]);
    addPlayer(1, player[2]);
}

Game::Game(const Game & game): round{game.round}, players{}, history{} {
    players.push_back(game.players[0].get()->copy());
    players.push_back(game.players[1].get()->copy());
}

void Game::addPlayer(int i, char * type){
    if (type[0] == 'c' || type[0] == 'C') {
        players.push_back( make_unique<AlphaWind>(i));
    }
    else if (type[0] == 'h' || type[0] == 'H') {
        players.push_back(make_unique<Human>(i));
    }
}

unique_ptr<Board> Game::getBoard() const{
    unique_ptr<Board> board = make_unique<Board>();
    players[0].get()->updateBoard(*board);
    players[1].get()->updateBoard(*board);
    board->setKP(players[round%2]->getPieces()[0]->getPosition());
    return board;
}

const std::vector<std::unique_ptr<Player>> & Game::getPlayer() const {
    return players;
}

int Game::processRound(){
    #ifdef DEBUG
    cerr << "processRound()" << endl;
    #endif

    Player * pMove = players[round%2].get();
    Player * pWait = players[(round+1)%2].get();
    unique_ptr<Board> board{getBoard()};
    vector<vector<unique_ptr<Move>>> possibleMoves(2);
    #ifdef DEBUG
    beginRoundNote(cout, *board, round);
    #else
    beginRoundNote(cerr, *board, round);
    #endif

    round += 1;

    // search for move
    pMove->searchMoves(round, *board, possibleMoves);

    // check game status 
    if (getValidMove(possibleMoves) == -1) {
        return 0;
    }

    // select the move
    string decision{pMove->move(possibleMoves)};
    
    #ifdef DEBUG
    cerr << "get decision: " << decision << endl;
    #endif
    if (decision == "end") {
        endNote(cerr);
        return 0;
    }
    else if (decision == "undo") {
        undoRound(*pWait);
        return 1;
    } // undo
    else if (decision.length() >= 4) {
        history.push_back((*board).makeMove(round%2, decision));
    } // undefined move
    else {
        if (decision.length() == 3) {
            #ifdef DEBUG
            cerr << "finds decision" << endl;
            #endif
        } // defined move
        else if (decision[0] >= '1' && decision[0] <= '9'){
            decision = smartMove(possibleMoves, decision[0]-'0');
        } // bot request
        else {
            cout << "something is wrong at processRound" << endl;
            return 0;
        }
        #ifdef DEBUG
        cerr << "pushing the move into history" << endl;
        #endif
        history.push_back(move(possibleMoves[decision[0]-'0'][decision[1]-'0']));
        possibleMoves[decision[0]-'0'][decision[1]-'0'] = nullptr;
        #ifdef DEBUG
        cerr << "finished pushing the move into history" << endl;
        #endif
    }

    // do the move
    history.back().get()->process(round, *pMove);
    #ifdef DEBUG
    cerr << "Capture::act() is called" << endl;
    #endif
    return 1;
}

void Game::processGame(){
    init();

    #ifdef DEBUG
    cerr << "initialized game" << endl;
    #endif

    printGame(*this);
    
    int state = 1;
    while (state == 1){
        state = processRound();
    }
}

void Game::init(){
    // cerr << players.size() << endl;
    players[0].get()->init();
    players[1].get()->init();
}

void Game::undoRound(Player & other){
    round -= 2;
    history.back().get()->undo(other);
}

std::string Game::smartMove(vector<vector<unique_ptr<Move>>> & moves, int it){
    string res = "  ";
    res[0] = getValidMove(moves) + '0';
    res[1] = '0';

    cout << *moves[res[0]-'0'][res[1]-'0'] << endl;
    return res;
}

