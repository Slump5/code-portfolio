// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// Deck.cpp
// This file implements the Deck class defined in Deck.h.
// It handles deck initialization, shuffling, drawing, and recycling cards.

#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>

// Constructor: Builds a standard 52-card deck.
// - Loops through all suits and values (1-13).
// - All cards start face-down.
Deck::Deck() {
    for (int s = Hearts; s <= Spades; ++s) {  // For each suit
        for (int v = 1; v <= 13; ++v) {       // For each value (Ace=1 to King=13)
            cards.push_back({ static_cast<Suit>(s), v, false });  // Add card
        }
    }
}

// shuffle: Randomizes the order of cards in the deck.
// - Uses std::shuffle with a time-seeded random engine.
void Deck::shuffle() {
    std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));  // Seed with time
    std::shuffle(cards.begin(), cards.end(), rng);  // Shuffle vector
}

// draw: Removes and returns the top (back) card from the deck.
Card Deck::draw() {
    Card c = cards.back();  // Get last card
    cards.pop_back();       // Remove it
    return c;               // Return the drawn card
}

// empty: Checks if the deck has no cards left.
bool Deck::empty() const {
    return cards.empty();  // True if size == 0
}

// cardsRemaining: Returns the current number of cards in the deck.
int Deck::cardsRemaining() const {
    return cards.size();  // Vector size
}

// addCards: Adds cards from a given pile (e.g., waste) to the deck.
// - Flips added cards face-down.
// - Used for recycling when deck is empty.
void Deck::addCards(std::vector<Card>& pile) {
    while (!pile.empty()) {         // While pile has cards
        Card c = pile.back();       // Get top of pile
        c.faceUp = false;           // Flip face-down for deck
        cards.push_back(c);         // Add to deck
        pile.pop_back();            // Remove from pile
    }
}