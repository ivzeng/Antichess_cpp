# include <iostream>
# include "Game.h"
# include "IO.h"

using namespace std;

int main(int argc, char *argv[]) {
    // checks validity of arguments
    if (argc != 2){
        err_argc();
        return -1;
    }
    if ((argv[0][0] != 'h' && argv[0][0] != 'H' && argv[0][0] != 'c' && argv[0][0] != 'C') 
        || (argv[1][0] != 'h' && argv[1][0] != 'H' && argv[1][0] != 'c' && argv[1][0] != 'C') ){
        err_argvType();
        return -1;
    }
    Game game{argv};
    game.processGame();
    return 0;
}