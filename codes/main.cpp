# include <iostream>
# include "Game.h"
# include "IO.h"

using namespace std;

int main(int argc, char *argv[]) {
    // checks validity of arguments
    if (!checkArgv(argc, argv)) return -1; 
    Game game{argv};
    game.processGame();
    return 0;
}