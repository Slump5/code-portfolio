// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// Game.cpp
// This file implements the Game class defined in Game.h.
// It handles the core logic of the Solitaire game, including dealing cards,
// displaying the game state, processing user inputs for moves, drawing cards,
// undoing actions, checking for win conditions, and managing game state history.
// The game supports one-card or three-card draw modes and tracks score and time.

#include "Game.h"
#include <iostream>
#include <sstream>
#include <iomanip>
#include <limits>

// Constructor: Initializes the game.
// - Prompts user for draw mode (1 or 3 cards).
// - Shuffles the deck and deals initial cards to tableau.
// - Starts the game timer.
Game::Game() : tableau(7), foundations(4) {
    deck.shuffle();
    deal();
    startTime = std::chrono::steady_clock::now();
}

// deal: Sets up the initial tableau layout.
// - Creates 7 piles, each with increasing number of cards (1 to 7).
// - Top card of each pile is face-up; others are face-down.
void Game::deal() {
    for (int col = 0; col < 7; ++col) {  // For each column (pile)
        for (int row = 0; row <= col; ++row) {  // Add cards to pile
            Card c = deck.draw();               // Draw from deck
            c.faceUp = (row == col);            // Face-up only if top card
            tableau[col].push_back(c);          // Add to tableau pile
        }
    }
}

// display: Renders the current game state to the console.
// - Clears the screen (platform-specific).
// - Shows elapsed time.
// - Displays foundations (top card or empty).
// - Shows tableau piles.
// - Shows stock (remaining cards) and waste pile (last drawn cards).
// - Displays current score and undo count.
void Game::display() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    std::cout << "===== Solitaire Console Game " 
          << (drawMode == 1 ? "1-Card Draw" : "3-Card Draw") 
          << " =====\n";

    // Calculate and display elapsed time
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    std::cout << "\nTime Elapsed: " << minutes << " min " << seconds << " sec\n";

    // Foundations
    std::cout << "\nFoundations:\n";
    const char suits[4] = { 'H', 'D', 'C', 'S' };
    for (int i = 0; i < 4; ++i) {
        std::cout << suits[i] << ": ";
        if (foundations[i].empty())
            std::cout << "(empty)";
        else
            std::cout << foundations[i].back().toString();
        std::cout << "  ";
    }

    // Tableau
    std::cout << "\n\nTableau:\n";
    for (int i = 0; i < 7; ++i) {
        std::cout << "Pile " << i + 1 << ": ";
        for (const Card& c : tableau[i]) {
            std::cout << c.toString() << " ";
        }
        std::cout << "\n";
    }

    // Stock & Waste
    std::cout << "\nStock: " << deck.cardsRemaining() << " cards left\n";
    std::cout << "Waste: ";
    int visible = std::min((int)waste.size(), (drawMode == 1 ? 1 : 3));
    for (int i = visible; i > 0; --i) {
        std::cout << waste[waste.size() - i].toString() << " ";
    }
    std::cout << "\n";

    // Score and Commands
    std::cout << "\nScore: " << score << " | Undos: " << undoCount << "\n";
    std::cout << "\nCommands:\n"
              << "d: Draw cards\n"
              << "m <src> <dst>: Move from tableau src to dst\n";

    // ✅ Correct help text for draw modes
    if (drawMode == 1) {
        std::cout << "w <dst>: Move waste to tableau dst\n"
                  << "wf: Move waste to foundation\n";
    } else {
        std::cout << "w <dst>: Move top waste card to tableau dst\n"
                  << "wf: Move top waste card to foundation\n";
    }

    std::cout << "f <src>: Move from tableau src to foundation\n"
              << "u: Undo (-15 points)\n"
              << "q: Quit to Main Menu\n>";
}


// drawCard: Draws cards from deck to waste based on drawMode.
// - If deck is empty, recycles waste back to deck (face-down).
// - Flips drawn cards face-up.
// - Saves state before drawing for undo.
void Game::drawCard() {
    saveState();  // Backup current state
    if (deck.empty()) {  // Recycle waste if deck empty
        deck.addCards(waste);
    }
    for (int i = 0; i < drawMode; ++i) {
        if (!deck.empty()) {
            Card c = deck.draw();
            c.faceUp = true;  // Face-up in waste
            waste.push_back(c);
        }
    }

    // Keep only top visible cards face-up (1 or 3)
    int visible = (drawMode == 1 ? 1 : 3);
    for (int i = 0; i < (int)waste.size() - visible; ++i) {
        waste[i].faceUp = false;
    }
    // ✅ Ensure top visible cards are face-up
    for (int i = std::max(0, (int)waste.size() - visible); i < (int)waste.size(); ++i) {
        waste[i].faceUp = true;
    }

    score -= 0;  // Penalty for drawing (adjust as needed)
}

// moveCard: Moves a sequence of cards from one tableau pile to another.
// - Validates move: Alternating colors, descending values, enough movable cards.
// - Saves state before moving.
// - Reveals new top card in source pile if needed.
// - Updates score for successful move.
void Game::moveCard(int src, int dst) {
    if (src < 0 || src >= 7 || dst < 0 || dst >= 7 || src == dst) return;  // Invalid piles

    auto& sPile = tableau[src];
    auto& dPile = tableau[dst];

    if (sPile.empty()) return;  // Nothing to move

    // Find how many cards can be moved (face-up sequence)
    int movable = 1;
    for (auto it = sPile.rbegin() + 1; it != sPile.rend(); ++it) {
        if (!it->faceUp || (it->value != (it - 1)->value + 1) ||
            isRed(*it) == isRed(*(it - 1))) break;
        movable++;
    }

    // Check if move is valid
    Card top = sPile.back();
    if (!dPile.empty()) {
        Card dstTop = dPile.back();
        if (isRed(top) == isRed(dstTop) || top.value != dstTop.value - 1) return;  // Invalid sequence
    } else if (top.value != 13) return;  // Empty pile only accepts King

    saveState();  // Backup state

    // Move the cards
    for (int i = 0; i < movable; ++i) {
        dPile.push_back(sPile.back());
        sPile.pop_back();
    }

    // Reveal new top in source if applicable
    if (!sPile.empty()) sPile.back().faceUp = true;

    score += 10 * movable;  // Score bonus for move
}

// ===== NEW HELPER FUNCTION =====
int Game::getWasteCardIndex(int pos) {
    if (waste.empty()) return -1;
    int visible = (drawMode == 1 ? 1 : 3);
    visible = std::min(visible, (int)waste.size());
    if (pos < 1 || pos > visible) pos = visible;  // Default/top if invalid
    return waste.size() - visible + (pos - 1);
}

// moveWasteToTableau: Moves selected waste card to a tableau pile.
// - Allows selecting one of top 3 cards in 3-card mode.
// - Saves state before moving.
void Game::moveWasteToTableau(int dst, int pos) {
    if (waste.empty() || dst < 0 || dst >= 7) return;

    // Always use top card only (real 3-card rules)
    int idx = waste.size() - 1;
    Card top = waste[idx];
    auto& dPile = tableau[dst];

    if (!dPile.empty()) {
        Card dstTop = dPile.back();
        if (isRed(top) == isRed(dstTop) || top.value != dstTop.value - 1) return;
    } else if (top.value != 13) return;  // Only King on empty

    saveState();
    dPile.push_back(top);
    waste.pop_back();
    score += 5;

    if (!waste.empty()) waste.back().faceUp = true;  // Reveal next waste
}


// moveToFoundation: Moves top card from tableau to matching foundation.
// - Validates suit and ascending value.
// - Saves state.
// - Reveals new top in tableau.
// - Updates score.
void Game::moveToFoundation(int src) {
    if (src < 0 || src >= 7 || tableau[src].empty()) return;

    Card top = tableau[src].back();
    int fIdx = top.suit;  // Foundation index by suit
    auto& f = foundations[fIdx];

    if (!f.empty() && top.value != f.back().value + 1) return;
    if (f.empty() && top.value != 1) return;  // Ace starts foundation

    saveState();
    f.push_back(top);
    tableau[src].pop_back();
    if (!tableau[src].empty()) tableau[src].back().faceUp = true;
    score += 10;  // Bonus for to foundation
}

// moveWasteToFoundation: Moves selected waste card to matching foundation.
// - Similar validation as moveToFoundation.
// - Saves state.
// - Updates score.
void Game::moveWasteToFoundation(int pos) {
    if (waste.empty()) return;

    // Always use top card only (real 3-card rules)
    int idx = waste.size() - 1;
    Card top = waste[idx];
    int fIdx = top.suit;
    auto& f = foundations[fIdx];

    if (!f.empty() && top.value != f.back().value + 1) return;
    if (f.empty() && top.value != 1) return;

    saveState();
    f.push_back(top);
    waste.pop_back();
    score += 10;

    if (!waste.empty()) waste.back().faceUp = true;  // Reveal next waste
}


// isRed: Helper to check if card is red (Hearts or Diamonds).
bool Game::isRed(const Card& c) {
    return c.suit == Hearts || c.suit == Diamonds;
}

// saveState: Pushes current game state to history stack for undo.
void Game::saveState() {
    history.push({tableau, foundations, waste, deck, score, undoCount});
}

// undo: Reverts to previous state from history.
// - Pops state, restores all piles/deck.
// - Adjusts score (penalty for undo).
// - Increments undo count.
void Game::undo() {
    if (history.empty()) {
        std::cout << "Nothing to undo.\n";
        return;
    }

    GameState state = history.top();
    history.pop();

    tableau = state.tableau;
    foundations = state.foundations;
    waste = state.waste;
    deck = state.deck;
    score = state.score - 15;  // Undo penalty
    undoCount = state.undoCount + 1;  // Track undos used
}

// checkWin: Checks if all foundations have 13 cards (full suits).
bool Game::checkWin() {
    for (auto& f : foundations)
        if (f.size() != 13) return false;
    return true;
}

// play: Main game loop.
// - Displays state, reads user input.
// - Processes commands: draw, undo, moves, quit.
// - Checks for win after each action, calculates final score with time bonus.
void Game::play() {
    std::string input;
    while (true) {
        display();
        std::getline(std::cin, input);

        // Normalize input: trim trailing CR (from Windows) and whitespace
        while (!input.empty() && isspace(static_cast<unsigned char>(input.back()))) input.pop_back();
        while (!input.empty() && isspace(static_cast<unsigned char>(input.front()))) input.erase(input.begin());

        // Skip empty input (e.g., user pressed Enter)
        if (input.empty()) continue;

        if (input == "q") {
            break;  // Return to main menu
        } else if (input == "d") drawCard();
        else if (input == "u") undo();

        // Waste → Foundation
        else if (input == "wf") {
            moveWasteToFoundation();
        }

        // Tableau → Foundation
        else if (input[0] == 'f') {
            int a;
            if (sscanf(input.c_str(), "f %d", &a) == 1)
                moveToFoundation(a - 1);
        }

        // Tableau → Tableau
        else if (input[0] == 'm') {
            int a, b;
            if (sscanf(input.c_str(), "m %d %d", &a, &b) == 2)
                moveCard(a - 1, b - 1);
        }

        // Waste → Tableau (ensure input has at least 2 chars before checking input[1])
        else if (input.size() >= 2 && input[0] == 'w' && input[1] == ' ') {
            int a;
            if (sscanf(input.c_str(), "w %d", &a) == 1)
                moveWasteToTableau(a - 1);
        }

        // Win check
        if (checkWin()) {
            auto end = std::chrono::steady_clock::now();
            int seconds = std::chrono::duration_cast<std::chrono::seconds>(end - startTime).count();
            int bonus = std::max(0, 500 - seconds);
            score += bonus;
            display();
            std::cout << "\n🎉 You won! Final score: " << score
                      << " (+" << bonus << " time bonus, " << undoCount << " undos used)\n";
            break;
        }
    }
}

