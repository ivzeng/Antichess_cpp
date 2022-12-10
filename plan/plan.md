## I have put my plan here:
---
## Start the program:

Go to the root directory /Antichess_cpp,

complie,

```
MakeFile
```

excecute,
```
./Antichess/Antichess human computer
./Antichess/Antichess h c
./Antichess/Antichess black
./Antichess/Antichess white
```

---
## Basic process:

The program will
1. check if the argument is valid,
2. construct the Game and Players; intialize (putting Pieces to) and print the game.
3. Start the game loop where 
each player will take a turn at each round. Specifically, the Game will classify the two players (call them ```pMove, pWait```), intilize vector ```possibleMove = [[],[],[],[]]``` and class ```borad = Board()```, call ```updateBoard()``` to update ```board``` and ```pMove.searchMoves()``` to update ```possibleMoves```, check the status of the game (need to be worked on), call ```pMove.decide()``` to get a move ("00" (```possibleMove[0][0]```),"e2e4" (if the move is not in ```possibleMove```), "undo", etc.), and execute the move (create/copy the Move ```m``` from ```possibleMoves``` and run ```m.exec()``) and place it into hist.
4. end the game
---
## More details
---

## Todo list:
#
###  Board:

#### add fields:
```int curPlayer```: colour of the current player 0/1
```std::pair<int, int> kingPos```: position of the king of the current player

####  add functions:
```std::unique_ptr<Move> Board::makeMove(const std::string & can)```: takes a string in the coordinate algebraic notation, distinguish the move type, and produce the Move class

```bool Board::safeMove(std::pair<int,int> from, std::pair<int,int> to)```: determine if the curPlayer's king is safe if the piece at position ```from``` is moved to ```to```; (when 'moving' the piece, just do it on the board, not the pieces! remember to undo it in the end (be careful to the capture moves))

```bool Board::safe()```: determine if the curPlayer's king is safe at the time (helper function for ```safeMove```)

more scaning if required

#

### Piece:
#### add functions
```bool Piece::threat(std::pair<int,int> pos)```: return true if the piece can attack the piece at position ```pos```, do not consider validity of the move, the status of the piece or any blocking; (helper function for ```Board::safe```)


#

### Move:
```void Move::do()```: does a move (change the position of  the moved pieces, set the status of the captured piece to 0, etc.)

```void Move::undo()```: undoes the move

```std::unique<Move> Move::copy() const;```: see ```Piece::copy```

```virtual std::unique<Move> Move::clone() const;```: see ```Piece::clone```



