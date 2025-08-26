// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// Game.h
// This header defines the Game class and GameState struct.
// Game manages the Solitaire game logic, including piles (tableau, foundations, waste),
// deck, score, timer, and history for undo.
// It declares methods for gameplay actions and helpers.

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stack>
#include <chrono>
#include "Deck.h"

// GameState: Struct to capture a snapshot of the game for undo functionality.
// - Stores tableau, foundations, waste, deck, score, and undo count.
struct GameState {
    std::vector<std::vector<Card>> tableau;     // Tableau piles
    std::vector<std::vector<Card>> foundations; // Foundation piles
    std::vector<Card> waste;                    // Waste pile
    Deck deck;                                  // Current deck state
    int score;                                  // Score at this state
    int undoCount;                              // Undos used so far
};

// Game: Class representing the Solitaire game.
// - Public: Constructor and play() to start the game.
// - Private: Members for game state, methods for actions and helpers.
class Game {
public:
    Game();        // Initializes game, prompts for draw mode, shuffles and deals
    void play();   // Main loop: display, input, process moves, check win

private:
    Deck deck;     // The deck of cards
    std::vector<Card> waste;  // Waste pile (drawn cards)
    std::vector<std::vector<Card>> tableau;     // 7 tableau piles
    std::vector<std::vector<Card>> foundations; // 4 foundation piles (by suit)
    std::stack<GameState> history;              // Stack for undo states

    int score = 0;     // Current score
    int undoCount = 0; // Number of undos used
    int drawMode = 1;  // 1 or 3 card draw
    std::chrono::time_point<std::chrono::steady_clock> startTime;  // Game start time

    void deal();                   // Initial card distribution to tableau
    void display();                // Render game state to console
    void drawCard();               // Draw from deck to waste
    void moveCard(int src, int dst);  // Move between tableau piles
    void moveWasteToTableau(int dst); // Move waste to tableau
    void moveToFoundation(int src);   // Move tableau to foundation
    void moveWasteToFoundation();     // Move waste to foundation
    void undo();                   // Revert to previous state
    void saveState();              // Save current state to history
    bool checkWin();               // Check if all foundations are complete
    bool isRed(const Card& c);     // Helper: Is card red (Hearts/Diamonds)?
};

#endif