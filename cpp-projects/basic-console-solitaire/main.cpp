// Thomas Hoerger - Copyright © 2025 Basic Console Solitaire
// main.cpp - Entry point with main menu and game mode selection.

#include "Game.h"
#include <iostream>
#include <limits>      //  for std::numeric_limits
#include <algorithm>   //  for std::max
#include <thread>      //  for std::this_thread
#include <chrono>      //  for std::chrono

#ifdef _WIN32
#ifndef NOMINMAX
#define NOMINMAX
#endif
#include <windows.h>
#else
#include <cstdlib>
#endif

void clearScreen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

int main() {
    while (true) {
        clearScreen();
        std::cout << "=============================\n";
        std::cout << "   Basic Console Solitaire\n";
        std::cout << "=============================\n";
        std::cout << "1. Play One-Card Draw\n";
        std::cout << "2. Play Three-Card Draw\n";
        std::cout << "3. Quit\n";
        std::cout << "Select option (1-3): ";

        int choice;
        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 3) {
            std::cout << "\nGoodbye!\n";
            std::this_thread::sleep_for(std::chrono::seconds(1));  // wait 1 seconds
            break;
            break;
        }

        std::cin.ignore(10000, '\n'); // clear buffer
        clearScreen();

        Game game;
        game.drawMode = (choice == 2 ? 3 : 1);
    game.play();  // run the game until user quits with 'q'
    }

    return 0;
}
