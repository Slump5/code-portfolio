// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire

// Card.cpp
// This file implements the methods for the Card struct defined in Card.h.
// It provides functionality to convert suit enums to string representations
// and to generate a string representation of the entire card, handling
// face-down cards and special values like Ace, Jack, Queen, King.

#include "Card.h"

// suitToChar: Converts the Suit enum to a single-character string.
// - Returns "H" for Hearts, "D" for Diamonds, "C" for Clubs, "S" for Spades.
// - Defaults to "?" for invalid suits (error handling).
std::string Card::suitToChar() const {
    switch (suit) {
        case Hearts: return "H";    // Hearts suit symbol
        case Diamonds: return "D";  // Diamonds suit symbol
        case Clubs: return "C";     // Clubs suit symbol
        case Spades: return "S";    // Spades suit symbol
    }
    return "?";  // Unknown suit (should not occur in normal play)
}

// toString: Generates a string representation of the card.
// - If faceUp is false, returns "XX" to indicate a face-down card.
// - For face-up cards:
//   - Converts value to string: "A" for 1, "J" for 11, "Q" for 12, "K" for 13.
//   - Appends the suit character from suitToChar().
// - Used for displaying cards in the game interface.
std::string Card::toString() const {
    if (!faceUp) return "XX";  // Face-down card representation

    std::string valStr;
    if (value == 1) valStr = "A";          // Ace
    else if (value == 11) valStr = "J";    // Jack
    else if (value == 12) valStr = "Q";    // Queen
    else if (value == 13) valStr = "K";    // King
    else valStr = std::to_string(value);   // Numeric values 2-10

    return valStr + suitToChar();  // Combine value and suit (e.g., "AH" for Ace of Hearts)
}