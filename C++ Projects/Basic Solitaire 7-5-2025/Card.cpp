// Card.cpp
#include "Card.h"

std::string Card::suitToChar() const {
    switch (suit) {
        case Hearts: return "H";
        case Diamonds: return "D";
        case Clubs: return "C";
        case Spades: return "S";
    }
    return "?";
}

std::string Card::toString() const {
    if (!faceUp) return "XX";

    std::string valStr;
    if (value == 1) valStr = "A";
    else if (value == 11) valStr = "J";
    else if (value == 12) valStr = "Q";
    else if (value == 13) valStr = "K";
    else valStr = std::to_string(value);

    return valStr + suitToChar();
}
