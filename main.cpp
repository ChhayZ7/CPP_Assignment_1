#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Game.h"

int main()
{
    // Seed the random number generator with the current time
    // so player names and deck shuffles are different each run
	srand(static_cast<unsigned int>(time(nullptr)));

    // Create the game (this sets up the deck and both players)
    Game game;

    // Start the game loop
    game.start();

    return 0;
}


