// Game.cpp
#include "Game.h"
#include <iostream>
#include <sstream>
#include <iomanip>

Game::Game() : tableau(7), foundations(4) {
    std::cout << "Play [1] one-card draw or [3] three-card draw? ";
    std::cin >> drawMode;
    if (drawMode != 3) drawMode = 1;
    std::cin.ignore();
    deck.shuffle();
    deal();
    startTime = std::chrono::steady_clock::now();
}

void Game::deal() {
    for (int col = 0; col < 7; ++col) {
        for (int row = 0; row <= col; ++row) {
            Card c = deck.draw();
            c.faceUp = (row == col);
            tableau[col].push_back(c);
        }
    }
}

void Game::display() {
    #ifdef _WIN32
        system("cls");
    #else
      system("clear");
    #endif

    std::cout << "===== Solitaire Console Game =====\n";

    // Show elapsed time at the top
    auto now = std::chrono::steady_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::seconds>(now - startTime).count();
    int minutes = elapsed / 60;
    int seconds = elapsed % 60;
    std::cout << "\nTime Elapsed: " << minutes << " min " << seconds << " sec\n";

    // Foundations
    std::cout << "\nFoundations:\n";
    const char suits[4] = { 'H', 'D', 'C', 'S' };
    for (int i = 0; i < 4; ++i) {
        std::cout << suits[i] << ": ";
        if (foundations[i].empty())
            std::cout << "(empty)";
        else
            std::cout << foundations[i].back().toString();
        std::cout << "  ";
    }

    // Tableau
    std::cout << "\n\nTableau:\n";
    for (int i = 0; i < 7; ++i) {
        std::cout << "Pile " << i + 1 << ": ";
        for (const Card& c : tableau[i]) {
            std::cout << c.toString() << " ";
        }
        std::cout << "\n";
    }

    // Waste
    std::cout << "\nWaste pile: ";
    if (waste.empty()) {
        std::cout << "(empty)";
    } else {
        int start = std::max(0, (int)waste.size() - 3);
        for (int i = start; i < waste.size(); ++i) {
            std::string str = waste[i].toString();
            if (i == waste.size() - 1)
                std::cout << ">" << str << "< ";
            else
                std::cout << str << " ";
        }
    }
    std::cout << "\n";

    // Score and undo tracker
    std::cout << "\nScore: " << score << "   |   Undos used: " << undoCount << "\n";

    // Command list
    std::cout << "\nAvailable Commands:\n";
    std::cout << "  d           - Draw card(s) from deck\n";
    std::cout << "  m X Y       - Move face-up card(s) from tableau X to Y\n";
    std::cout << "  w Y         - Move top waste card to tableau Y\n";
    std::cout << "  f X         - Move top tableau card to foundation\n";
    std::cout << "  wf          - Move top waste card to foundation\n";
    std::cout << "  u           - Undo last move (-15 pts)\n";
    std::cout << "  q           - Quit\n";
}


bool Game::isRed(const Card& c) {
    return c.suit == Hearts || c.suit == Diamonds;
}

void Game::drawCard() {
    saveState();
    if (!deck.empty()) {
        int count = (drawMode == 3) ? std::min(3, deck.cardsRemaining()) : 1;
        for (int i = 0; i < count; ++i) {
            Card c = deck.draw();
            c.faceUp = true;
            waste.push_back(c);
        }
    } else if (!waste.empty()) {
        std::cout << "Deck empty. Recycling waste pile...\n";
        deck.addCards(waste);
        deck.shuffle();
    } else {
        std::cout << "No cards to draw.\n";
    }
}

void Game::moveCard(int src, int dst) {
    if (src < 0 || src >= 7 || dst < 0 || dst >= 7) return;
    saveState();

    auto& from = tableau[src];
    auto& to = tableau[dst];

    int index = -1;
    for (int i = 0; i < from.size(); ++i) {
        if (from[i].faceUp) {
            index = i;
            break;
        }
    }

    if (index == -1) return;
    Card moving = from[index];

    if (to.empty()) {
        if (moving.value != 13) {
            std::cout << "Only Kings can go to empty pile.\n";
            return;
        }
    } else {
        Card top = to.back();
        if (!top.faceUp || isRed(top) == isRed(moving) || moving.value != top.value - 1) {
            std::cout << "Invalid move.\n";
            return;
        }
    }

    to.insert(to.end(), from.begin() + index, from.end());
    from.erase(from.begin() + index, from.end());
    if (!from.empty() && !from.back().faceUp)
        from.back().faceUp = true;
}

void Game::moveWasteToTableau(int dst) {
    if (waste.empty() || dst < 0 || dst >= 7) return;
    saveState();

    Card c = waste.back();
    auto& pile = tableau[dst];

    if (pile.empty()) {
        if (c.value == 13) {
            pile.push_back(c);
            waste.pop_back();
        } else {
            std::cout << "Only Kings to empty.\n";
        }
    } else {
        Card top = pile.back();
        if (top.faceUp && isRed(c) != isRed(top) && c.value == top.value - 1) {
            pile.push_back(c);
            waste.pop_back();
        } else {
            std::cout << "Invalid move.\n";
        }
    }
}

void Game::moveToFoundation(int src) {
    if (src < 0 || src >= 7 || tableau[src].empty()) return;
    saveState();

    Card c = tableau[src].back();
    int suit = (int)c.suit;

    if (!c.faceUp) return;

    if (foundations[suit].empty()) {
        if (c.value == 1) {
            foundations[suit].push_back(c);
            tableau[src].pop_back();
        }
    } else if (foundations[suit].back().value == c.value - 1) {
        foundations[suit].push_back(c);
        tableau[src].pop_back();
    }

    if (!tableau[src].empty() && !tableau[src].back().faceUp)
        tableau[src].back().faceUp = true;
}

void Game::moveWasteToFoundation() {
    if (waste.empty()) return;
    saveState();

    Card c = waste.back();
    int suit = (int)c.suit;

    if (foundations[suit].empty()) {
        if (c.value == 1) {
            foundations[suit].push_back(c);
            waste.pop_back();
        }
    } else if (foundations[suit].back().value == c.value - 1) {
        foundations[suit].push_back(c);
        waste.pop_back();
    }
}

void Game::saveState() {
    GameState state;
    state.tableau = tableau;
    state.foundations = foundations;
    state.waste = waste;
    state.deck = deck;
    state.score = score;
    state.undoCount = undoCount;
    history.push(state);
}

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
    score = state.score - 15;
    undoCount = state.undoCount + 1;
}

bool Game::checkWin() {
    for (auto& f : foundations)
        if (f.size() != 13) return false;
    return true;
}

void Game::play() {
    std::string input;
    while (true) {
        display();
        std::getline(std::cin, input);

        if (input == "q") break;
        else if (input == "d") drawCard();
        else if (input == "u") undo();
        else if (input == "wf") moveWasteToFoundation();
        else if (input[0] == 'm') {
            int a, b;
            if (sscanf(input.c_str(), "m %d %d", &a, &b) == 2)
                moveCard(a - 1, b - 1);
        } else if (input[0] == 'w') {
            int a;
            if (sscanf(input.c_str(), "w %d", &a) == 1)
                moveWasteToTableau(a - 1);
        } else if (input[0] == 'f') {
            int a;
            if (sscanf(input.c_str(), "f %d", &a) == 1)
                moveToFoundation(a - 1);
        }

        if (checkWin()) {
            auto end = std::chrono::steady_clock::now();
            int seconds = std::chrono::duration_cast<std::chrono::seconds>(end - startTime).count();
            int bonus = std::max(0, 500 - seconds);
            score += bonus;
            display();
            std::cout << "\n🎉 You won! Final score: " << score
                      << " (+" << bonus << " time bonus, " << undoCount << " undos used)\n";
            break;
        }
    }
}
