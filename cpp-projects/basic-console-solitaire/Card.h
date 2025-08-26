// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// Card.h
// This header defines the Suit enum and Card struct.
// Card represents a playing card with suit, value, and face-up status.
// Declares methods for string conversion.

#ifndef CARD_H
#define CARD_H

#include <string>

// Suit: Enum for card suits (Hearts, Diamonds, Clubs, Spades).
enum Suit { Hearts, Diamonds, Clubs, Spades };

// Card: Struct for a single card.
// - Members: suit, value (1-13), faceUp (visible or not).
// - Methods: toString() for display, suitToChar() helper.
struct Card {
    Suit suit;     // Card's suit
    int value;     // Card's value (1=Ace, 11=Jack, 12=Queen, 13=King)
    bool faceUp;   // True if card is visible

    std::string toString() const;     // Full string rep (e.g., "AH")
    std::string suitToChar() const;   // Suit to char (e.g., "H")
};

#endif