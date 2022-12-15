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
        cerr << "game::addPlayer(): some thing is wrong" << endl;
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
        endNote(cerr, (board->isCheck() ? pWait->getColour() : -1));
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
    history.back()->process(round, *pMove);
    #ifdef DEBUG
    cerr << "done the move" << endl;
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
    if (history.size() == 0) {
        err_emptyHist(cerr);
        round -= 1;
        return ;
    }
    round -= 2;
    history.back().get()->undo(other);
    history.pop_back();
}

std::string Game::smartMove(vector<vector<unique_ptr<Move>>> & moves, int it){
    string res = "  ";
    res[0] = getValidMove(moves) + '0';
    res[1] = '0';

    cout << *moves[res[0]-'0'][res[1]-'0'] << endl;
    return res;
}

int Game::positionScore(int player) {
    int score = 0;
    for (auto & piece : getPlayer().at(player)->getPieces()) {
        score += piece->getValue();
    }

    return score;
}

/*
std::unique_ptr<Move> & Game::findBestMove(std::unique_ptr<Board> board, int depth, int it, int player) {
    if (depth != 0) {
        vector<vector<unique_ptr<Move>>> possibleMoves(2);
        getPlayer().at(player)->searchMoves(round, *board, possibleMoves);
        for (auto trymove : possibleMoves) {
            if (it == 0) {
                string decision{trymove};
                (*board).makeMove(player, decision)
                if (player == 0){
                    return findBestMove(board, depth--, it++, 1);
                } else {
                    return findBestMove(board, depth--, it++, 0);
                }
            } else {

            }
        }
    } else {
        vector<vector<unique_ptr<Move>>> possibleMoves(2);
        getPlayer().at(player)->searchMoves(round, *board, possibleMoves);
        int bestScore = 0;
        std::unique_ptr<Move> bestMove = nullptr;
        for (auto trymove : possibleMoves) {
            int tempScore = positionScore(player);
            if (tempScore > bestScore) {
                bestScore = tempScore;
                bestMove = trymove;
            }
        }
    }
}
*/

std::string Game::findBestMoveWrapper(Board & board, int depth, int it, int player) {
    int bestScore = 0;
    std::string bestMove = "";

    std::vector<std::vector<std::unique_ptr<Move>>> possibleMoves(2);
    getPlayer().at(player)->searchMoves(round, board, possibleMoves);

    for (auto & trymove : possibleMoves.at(0)) {
        //string decision{trymove};
        //board.makeMove(player, decision);
        int temp = getPositionScoreAtDepth(board, depth - 1, it + 1, player);
        if (temp > bestScore) {
            bestScore = temp;
            bestMove = trymove->representation();
        }
    }

    for (auto & trymove : possibleMoves.at(1)) {
        //string decision{trymove};
        //board.makeMove(player, decision);
        int temp = getPositionScoreAtDepth(board, depth - 1, it + 1, player);
        if (temp > bestScore) {
            bestScore = temp;
            bestMove = trymove->representation();
        }
    }

    return bestMove;
}

int Game::getPositionScoreAtDepth(Board & board, int depth, int it, int player){
    if (depth != 0) {
        std::vector<std::vector<std::unique_ptr<Move>>> possibleMoves(2);
        getPlayer().at(round%2)->searchMoves(round, board, possibleMoves);
        for (auto & trymove : possibleMoves.at(0)) {
            //string decision{trymove};
            //board.makeMove(round%2, decision);
            return getPositionScoreAtDepth(board, depth - 1, it + 1, player);
        }
        for (auto & trymove : possibleMoves.at(1)) {
            //string decision{trymove};
            //board.makeMove(round%2, decision);
            return getPositionScoreAtDepth(board, depth - 1, it + 1, player);
        }
    } else {
        return positionScore(player);
    }
}