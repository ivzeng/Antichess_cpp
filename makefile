CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = ./codes/main.o ./codes/Game.o codes/IO.o codes/Player.o codes/Piece.o codes/Move.o codes/Board.o
EXEC = exe/Antichess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}


.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC}