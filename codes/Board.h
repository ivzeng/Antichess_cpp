#ifndef BOARD_H
#define BOARD_H

class Piece;
class Option;

class Board{
    /* fields */
    Piece * board[8][8];

    /* function */

public:
    Board();
    void process(Option & option);      // do an option
    void undo(Option & option);         // undo an option
};
#endif
