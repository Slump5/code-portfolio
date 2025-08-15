// Card.h
#ifndef CARD_H
#define CARD_H

#include <string>

enum Suit { Hearts, Diamonds, Clubs, Spades };

struct Card {
    Suit suit;
    int value;
    bool faceUp;

    std::string toString() const;
    std::string suitToChar() const;
};

#endif