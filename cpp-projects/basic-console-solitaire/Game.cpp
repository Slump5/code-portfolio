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

// Constructor: Initializes the game.
// - Prompts user for draw mode (1 or 3 cards).
// - Shuffles the deck and deals initial cards to tableau.
// - Starts the game timer.
Game::Game() : tableau(7), foundations(4) {
    std::cout << "Play [1] one-card draw or [3] three-card draw? ";
    std::cin >> drawMode;
    if (drawMode != 3) drawMode = 1;  // Default to 1 if not 3
    std::cin.ignore();  // Clear input buffer
    deck.shuffle();     // Randomize deck order
    deal();             // Distribute cards to tableau
    startTime = std::chrono::steady_clock::now();  // Record start time for scoring
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
        system("cls");  // Clear screen on Windows
    #else
      system("clear");  // Clear screen on Unix-like systems
    #endif

    std::cout << "===== Solitaire Console Game =====\n";

    // Calculate and display elapsed time
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    std::cout << "\nTime Elapsed: " << minutes << " min " << seconds << " sec\n";

    // Foundations display
    std::cout << "\nFoundations:\n";
    const char suits[4] = { 'H', 'D', 'C', 'S' };  // Suit symbols
    for (int i = 0; i < 4; ++i) {
        std::cout << suits[i] << ": ";
        if (foundations[i].empty())
            std::cout << "(empty)";  // No cards in foundation
        else
            std::cout << foundations[i].back().toString();  // Top card
        std::cout << "  ";
    }

    // Tableau display
    std::cout << "\n\nTableau:\n";
    for (int i = 0; i < 7; ++i) {
        std::cout << "Pile " << i + 1 << ": ";
        for (const Card& c : tableau[i]) {
            std::cout << c.toString() << " ";  // Print each card in pile
        }
        std::cout << "\n";
    }

    // Stock and Waste display
    std::cout << "\nStock: " << deck.cardsRemaining() << " cards left\n";
    std::cout << "Waste: ";
    for (auto it = waste.rbegin(); it != waste.rend(); ++it) {  // Show last drawn cards
        std::cout << it->toString() << " ";
        if (std::distance(waste.rbegin(), it) == drawMode - 1) break;  // Limit to draw mode
    }
    std::cout << "\n";

    // Score and Undo display
    std::cout << "\nScore: " << score << " | Undos: " << undoCount << "\n";
    std::cout << "\nCommands:\n"
              << "d: Draw | q: Quit | u: Undo\n"
              << "m <src> <dst>: Move from tableau src to dst\n"
              << "w <dst>: Move waste to tableau dst\n"
              << "f <src>: Move from tableau src to foundation\n"
              << "wf: Move waste to foundation\n> ";
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
    score -= 10;  // Penalty for drawing (adjust as needed)
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

// moveWasteToTableau: Moves top waste card to a tableau pile.
// - Validates color alternation and value sequence.
// - Saves state before moving.
// - Updates score.
void Game::moveWasteToTableau(int dst) {
    if (waste.empty() || dst < 0 || dst >= 7) return;

    Card top = waste.back();
    auto& dPile = tableau[dst];

    if (!dPile.empty()) {
        Card dstTop = dPile.back();
        if (isRed(top) == isRed(dstTop) || top.value != dstTop.value - 1) return;
    } else if (top.value != 13) return;  // King to empty

    saveState();
    dPile.push_back(top);
    waste.pop_back();
    score += 5;  // Bonus for waste to tableau
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

// moveWasteToFoundation: Moves top waste to matching foundation.
// - Similar validation as moveToFoundation.
// - Saves state.
// - Updates score.
void Game::moveWasteToFoundation() {
    if (waste.empty()) return;

    Card top = waste.back();
    int fIdx = top.suit;
    auto& f = foundations[fIdx];

    if (!f.empty() && top.value != f.back().value + 1) return;
    if (f.empty() && top.value != 1) return;

    saveState();
    f.push_back(top);
    waste.pop_back();
    score += 10;
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
        display();  // Refresh screen
        std::getline(std::cin, input);  // Read command

        if (input == "q") break;  // Quit game
        else if (input == "d") drawCard();  // Draw cards
        else if (input == "u") undo();  // Undo last action
        else if (input == "wf") moveWasteToFoundation();  // Waste to foundation
        else if (input[0] == 'm') {
            int a, b;
            if (sscanf(input.c_str(), "m %d %d", &a, &b) == 2)
                moveCard(a - 1, b - 1);  // Tableau move (0-indexed)
        } else if (input[0] == 'w') {
            int a;
            if (sscanf(input.c_str(), "w %d", &a) == 1)
                moveWasteToTableau(a - 1);  // Waste to tableau
        } else if (input[0] == 'f') {
            int a;
            if (sscanf(input.c_str(), "f %d", &a) == 1)
                moveToFoundation(a - 1);  // Tableau to foundation
        }

        if (checkWin()) {  // Win condition met
            auto end = std::chrono::steady_clock::now();
            int seconds = std::chrono::duration_cast<std::chrono::seconds>(end - startTime).count();
            int bonus = std::max(0, 500 - seconds);  // Time bonus
            score += bonus;
            display();  // Show final state
            std::cout << "\n🎉 You won! Final score: " << score
                      << " (+" << bonus << " time bonus, " << undoCount << " undos used)\n";
            break;  // End game
        }
    }
}