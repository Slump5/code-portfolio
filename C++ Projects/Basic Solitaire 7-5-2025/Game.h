// Game.h
#ifndef GAME_H
#define GAME_H

#include <vector>
#include <stack>
#include <chrono>
#include "Deck.h"

struct GameState {
    std::vector<std::vector<Card>> tableau;
    std::vector<std::vector<Card>> foundations;
    std::vector<Card> waste;
    Deck deck;
    int score;
    int undoCount;
};

class Game {
public:
    Game();
    void play();

private:
    Deck deck;
    std::vector<Card> waste;
    std::vector<std::vector<Card>> tableau;
    std::vector<std::vector<Card>> foundations;
    std::stack<GameState> history;

    int score = 0;
    int undoCount = 0;
    int drawMode = 1;
    std::chrono::time_point<std::chrono::steady_clock> startTime;

    void deal();
    void display();
    void drawCard();
    void moveCard(int src, int dst);
    void moveWasteToTableau(int dst);
    void moveToFoundation(int src);
    void moveWasteToFoundation();
    void undo();
    void saveState();
    bool checkWin();
    bool isRed(const Card& c);
};

#endif
