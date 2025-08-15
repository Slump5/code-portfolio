// Deck.cpp
#include "Deck.h"
#include <algorithm>
#include <random>
#include <ctime>

Deck::Deck() {
    for (int s = Hearts; s <= Spades; ++s) {
        for (int v = 1; v <= 13; ++v) {
            cards.push_back({ static_cast<Suit>(s), v, false });
        }
    }
}

void Deck::shuffle() {
    std::default_random_engine rng(static_cast<unsigned>(std::time(nullptr)));
    std::shuffle(cards.begin(), cards.end(), rng);
}

Card Deck::draw() {
    Card c = cards.back();
    cards.pop_back();
    return c;
}

bool Deck::empty() const {
    return cards.empty();
}

int Deck::cardsRemaining() const {
    return cards.size();
}

void Deck::addCards(std::vector<Card>& pile) {
    while (!pile.empty()) {
        Card c = pile.back();
        c.faceUp = false;
        cards.push_back(c);
        pile.pop_back();
    }
}
