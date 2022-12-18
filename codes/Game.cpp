#include <cmath>
#include <algorithm>

#include "Game.h"
#include "Player.h"
#include "Board.h"
#include "Piece.h"
#include "Move.h"
#include "IO.h"


using namespace std;

Game::Game(char * player[]): round{0}, players{}, history{} {
    // set players
    if (player[1][0] == 'w') {
        addPlayer(0, 'c');
        addPlayer(1, 'h');
    }
    else if (player[1][0] == 'b') {
        addPlayer(0, 'h');
        addPlayer(1, 'c');
    }
    else {
        addPlayer(0, player[1][0]);
        addPlayer(1, player[2][0]);
    }
}

Game::Game(const Game & game): round{game.round}, players{}, history{} {
    players.push_back(game.players[0].get()->copy());
    players.push_back(game.players[1].get()->copy());
}

void Game::addPlayer(int i, char type){
    if (type == 'c') {
        players.push_back( make_unique<AlphaWind>(i));
    }
    else if (type == 'h') {
        players.push_back(make_unique<Human>(i));
    }
    else {
        // cerr << "game::addPlayer(): some thing is wrong" << endl;
    }
}

unique_ptr<Board> Game::getBoard() const{
    unique_ptr<Board> board = make_unique<Board>();
    players[0].get()->updateBoard(*board);
    players[1].get()->updateBoard(*board);
    board->setKP(getPlayerM().getPieces()[0]->getPosition());
    return board;
}

const vector<unique_ptr<Player>> & Game::getPlayer() const {
    return players;
}

const Player & Game::getPlayerM() const {
    return *(players[round%2]);
}

Player * Game::playerM() {
    return players[round%2].get();
}

Player * Game::playerW() {
    return players[(round+1)%2].get();
}

int Game::processRound(){
    #ifdef DEBUG
    // cerr << "processRound()" << endl;
    #endif

    Player * pMove = playerM();
    Player * pWait = playerW();
    unique_ptr<Board> board{getBoard()};
    vector<vector<unique_ptr<Move>>> possibleMoves(2);
    #ifdef DEBUG
    beginRoundNote(cout, *board, round);
    #else
    beginRoundNote(cerr, *board, round);
    #endif


    // search for move
    pMove->searchMoves(round, *board, possibleMoves);

    // check game status 
    if (getValidMove(possibleMoves) == -1) {
        endNote(cerr, (board->isCheck() ? pWait->getColour() : -1));
        return 0;
    }

    // select the move
    string decision{pMove->move(possibleMoves)};
    
    #ifdef DEBUG
    // cerr << "get decision: " << decision << endl;
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
        history.push_back((*board).makeMove((round+1)%2, decision));
    } // undefined move
    else {
        if (decision.length() == 3) {
            #ifdef DEBUG
            // cerr << "finds decision" << endl;
            #endif
        } // defined move
        else if (decision[0] >= '1' && decision[0] <= '9'){
            decision = smartMove(possibleMoves, decision[0]-'0');
            cout << *(possibleMoves[decision[0]-'0'][decision[1]-'0']) << endl;
    
        } // bot request
        else {
            // cerr << "something is wrong at processRound" << endl;
            return 0;
        }
        #ifdef DEBUG
        // cerr << "pushing the move into history" << endl;
        #endif
        history.push_back(move(possibleMoves[decision[0]-'0'][decision[1]-'0']));
        possibleMoves[decision[0]-'0'][decision[1]-'0'] = nullptr;
        #ifdef DEBUG
        // cerr << "finished pushing the move into history" << endl;
        #endif
    }

    // do the move
    history.back()->process(round, *pMove);
    #ifdef DEBUG
    // cerr << "done the move" << endl;
    #endif
    round += 1;
    cerr << "history" << endl;
    printMoves(cerr, history);
    return 1;
}

void Game::processGame(){
    init();

    #ifdef DEBUG
    // cerr << "initialized game" << endl;
    #endif

    printGame(*this);
    
    int state = 1;
    while (state == 1){
        state = processRound();
    }
}

void Game::init(){
    // // cerr << players.size() << endl;
    players[0].get()->init();
    players[1].get()->init();
}

void Game::undoRound(Player & other){
    if (history.size() == 0) {
        err_emptyHist(cerr);
        return ;
    }
    round -= 1;
    history.back().get()->undo(other);
    history.pop_back();
}

string Game::smartMove(vector<vector<unique_ptr<Move>>> & moves, int it){
    string res = "  ";

    //cout << "Round: " << round << endl;

    vector<vector<unique_ptr<Move>>> possibleMoves(2);
    playerM()->searchMoves(round, *(getBoard()), possibleMoves);

    res[0] = getValidMove(moves) + '0';
    res[1] = findBestMoveWrapper(possibleMoves.at(getValidMove(moves)), it, round%2);

    //cout << res[0]-'0' << endl;
    //cout << res[1]-'0' << endl;
    //cout << moves[res[0]-'0'].size() << endl;
    //cout << moves[1].size() << endl;

    //cout << *moves[res[0]-'0'][res[1]-'0'] << endl;
    return res;
}


double Game::positionScore(int cur) {
    double score = 0;
    for (auto & piece : players[cur]->getPieces()) {
        if (piece->getStatus() == 1) {
            score = (double)score + (double)piece->getValue();
        }
    }
    return score;
}

char Game::findBestMoveWrapper(vector<unique_ptr<Move>> & moves, int depth, int cur) {
    double bestScore = -100;
    int bestMoveIdx = 0;
    char bestMove = 0;

    for (auto & trymove : moves) {
        trymove->process(round, *players[cur]);
        history.push_back(move(trymove));
        round +=1;
        vector<vector<unique_ptr<Move>>> possibleMoves(2);
        playerM()->searchMoves(round, *(getBoard()), possibleMoves); // other player search move
        // cerr << "Round: " << round << endl;
        // printMoves(cerr, possibleMoves);
        int validMoveRow = getValidMove(possibleMoves);
        if (validMoveRow == -1) {
            validMoveRow = 0;
        }

        double temp = getPositionScoreAtDepth(possibleMoves.at(validMoveRow), depth-1, cur);

        if (temp > bestScore) {
            bestScore = temp;
            bestMoveIdx = bestMove;
        }
        bestMove++;
        undoRound(*(players[cur]));
    }
    // cerr << "BestMove: " << bestMove + '0' << endl;
    return bestMoveIdx + '0';
}

double Game::getPositionScoreAtDepth(vector<unique_ptr<Move>> & moves, int depth, int cur){
    if (moves.size() == 0) {
        return (cur == round%2) ? -100 : 100;
    }
    if (depth == 0) {
        return (double)positionScore(cur) - (double)positionScore(1 - cur);
    }

    vector<double> outcomes{};

    for (auto & trymove : moves) {
        trymove->process(round, *playerM());
        history.push_back(move(trymove));
        round += 1;
        vector<vector<unique_ptr<Move>>> possibleMoves(2);
        playerM()->searchMoves(round, *(getBoard()), possibleMoves);
        // cerr << "Round: " << round << endl;
        // printMoves(cerr, possibleMoves);
        int validMoveRow = getValidMove(possibleMoves);
        if (validMoveRow == -1) {
            validMoveRow = 0;
        }
        outcomes.push_back((double)getPositionScoreAtDepth(possibleMoves.at(validMoveRow), depth - 1, cur));
        undoRound(*(playerW()));
    }

    // sort
    if (round%2 != cur) {
        sort(outcomes.begin(), outcomes.end());
    }
    else {
        sort(outcomes.begin(), outcomes.end(), greater<double>());
    }
    

    return expectedOutcome(outcomes, 15);
}

double expectedOutcome(vector<double> & outcomes, int upperBound) {
    int i = 0;
    double res = 0.0;
    while (i < upperBound-1 && (size_t)i < outcomes.size()-1){
        res =  (double)res + (double)outcomes[i]/(double)pow(2,i+1);
        i += 1;
    }
    res = (double)res + (double)outcomes[i]/(double)pow(2,i);
    return res;
}
