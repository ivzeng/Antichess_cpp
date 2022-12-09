## I have put my plan here:


#
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

#
## Basic process:

The program will
1. check if the argument is valid,
2. construct the Game and Players; intialize (putting Pieces to) and print the game.
3. Start the game loop where 
each player will take a turn at each round. Specifically, the Game will classify the two players (call them ```pMove, pWait```), intilize vector ```possibleMove = [[],[],[],[]]``` and class ```borad = Board()```, call ```updateBoard()``` to update ```board``` and ```pMove.searchMoves()``` to update ```possibleMoves```, check the status of the game (need to be worked on), call ```pMove.move()``` to get a move ('e2e4', "undo", etc.), and execute the move (create/copy the Move ```m``` from ```possibleMoves``` and run ```m.exec()``) and place it into hist.
4. end the game

## More details