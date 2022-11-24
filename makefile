CXX = g++
CXXFLAGS = -std=c++14 -Wall
OBJECTS = ./codes/main.o ./codes/Game.o codes/IO.o codes/Player.o codes/Piece.o codes/Move.o codes/Board.o
DEPENDS = ${OBJECTS:.o=.d}
EXEC = Antichess/Antichess

${EXEC}: ${OBJECTS}
	${CXX} ${OBJECTS} ${CXXFLAGS} -o ${EXEC}

-include ${DEPENDS}

.PHONY: clean

clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS}