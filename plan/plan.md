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
3. start the game loop where 
each player will take a turn at each round. Specifically, the game will set up a board and search for all valid moves for the player who takes turn, then the player's ```getDecision()``` will be call to get a decision and the game class will read the redcision and preform. If the decision is a charactor from '1' to '9', then the game's ```smartMove()``` will run to simulate a few round and find a (at least) good move.
4. If one player has no more valid move, end the game.
---
## More details

### Classes
- Game: the main class that handles the rounds and game analysis; contains players and a history of moves; provides functions including do/undo round, move-searching, obtaining the board, and print game status

- Player: the class that owns the piece; provides functions on collecting move and sending the decision to the game class

- Piece: the derived peice class; records the position and status of a peice; provides instructions on move-scanning and value of the peice

- Board: the class that provides an intuitive view of the game; provide helper functions for scannig and visualizing the game

- Move: the derived class of each move; includes the functions for processing a move.

### Move-searching algorithm
In our design, we used the most intuitive strategic: DFS and backtracking.

Specifically, there is a recursive function ```Game::getPositionScoreAtDepth(moves, ...)``` that computes the expected outcome of every possible moves in move, and a wapper function ```findBestMoveWrapper(moves)``` that returns the decision (the move that has the highest outcome).

The number of rounds to be simulated depends on the number of available moves, so the time it take to compute each time is similar. The expected number of operations is around 10<sup>5</sup>, and the expected time taken is around 8 seconds.

---


