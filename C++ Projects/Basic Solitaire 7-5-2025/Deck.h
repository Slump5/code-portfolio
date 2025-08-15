// Deck.h
#ifndef DECK_H
#define DECK_H

#include <vector>
#include "Card.h"

class Deck {
public:
    Deck();
    void shuffle();
    Card draw();
    bool empty() const;
    int cardsRemaining() const;
    void addCards(std::vector<Card>& pile);

private:
    std::vector<Card> cards;
    friend class Game; // allow Game to access cards for undo/save
};

#endif