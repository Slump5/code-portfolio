// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// Deck.h
// This header defines the Deck class.
// Deck manages a vector of Card objects, providing methods for shuffling,
// drawing, checking emptiness, and adding cards (for recycling waste).

#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

// Deck: Class representing a standard 52-card deck.
// - Public methods for shuffling, drawing, checking status, adding cards.
// - Private: Vector of cards; friend access for Game (undo/save).
class Deck {
public:
    Deck();                      // Constructor: Initializes full deck (52 cards)
    void shuffle();              // Randomly shuffles the cards
    Card draw();                 // Draws and removes top card
    bool empty() const;          // Checks if deck is empty
    int cardsRemaining() const;  // Returns number of cards left
    void addCards(std::vector<Card>& pile);  // Adds cards from a pile (e.g., waste recycle)

private:
    std::vector<Card> cards;     // Internal storage of cards
    friend class Game;           // Allow Game to access cards for state saving/undo
};

#endif