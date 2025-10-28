// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire
// Game.h

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stack>
#include <chrono>
#include "Deck.h"

// GameState: snapshot for undo.
struct GameState {
    std::vector<std::vector<Card>> tableau;     // Tableau piles
    std::vector<std::vector<Card>> foundations; // Foundation piles
    std::vector<Card> waste;                    // Waste pile
    Deck deck;                                  // Deck state
    int score;                                  // Score at this state
    int undoCount;                              // Undos used
};

// Game: Solitaire logic.
class Game {
public:
    Game();        // Initializes deck/tableau; does NOT prompt for draw mode
    void play();   // Main loop

    // ✅ Single declaration of drawMode (so main.cpp can set it)
    int drawMode = 1;  // 1 or 3-card draw, set by menu in main.cpp

private:
    Deck deck;     // The deck of cards
    std::vector<Card> waste;  // Waste pile
    std::vector<std::vector<Card>> tableau;     // 7 tableau piles
    std::vector<std::vector<Card>> foundations; // 4 foundations (by suit)
    std::stack<GameState> history;              // Undo stack

    int score = 0;        // Current score
    int undoCount = 0;    // Number of undos used
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    void deal();                   // Initial layout
    void display();                // Render state
    void drawCard();               // Deck → waste
    void moveCard(int src, int dst);                  // Tableau → tableau
    void moveWasteToTableau(int dst, int pos = -1);   // Waste → tableau (top card only in our rules)
    void moveToFoundation(int src);                   // Tableau → foundation
    void moveWasteToFoundation(int pos = -1);         // Waste → foundation (top card only in our rules)
    void undo();                   // Undo last state
    void saveState();              // Save to history
    bool checkWin();               // All foundations complete?
    bool isRed(const Card& c);     // Hearts/Diamonds?
    int getWasteCardIndex(int pos);// (unused now for 3-card realism; safe to keep)
};

#endif
