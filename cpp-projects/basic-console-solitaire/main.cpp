// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// main.cpp
// Entry point for the Solitaire console game.
// Creates a Game instance and starts the play loop.

#include "Game.h"

// main: Program entry.
// - Instantiates Game and calls play() to run the game.
// - Returns 0 on exit.
int main() {
    Game game;  // Create game object
    game.play();  // Start the game loop
    return 0;   // Exit successfully
}