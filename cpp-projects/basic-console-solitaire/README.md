# Solitaire Console Game

## Overview
This is a console-based implementation of the classic Klondike Solitaire card game, written in C++. The game supports both one-card and three-card draw modes, includes an undo feature, tracks elapsed time, and calculates a score with a time bonus for winning. The game is played through a text-based interface where players input commands to manipulate the card piles.

## Features
- **Game Modes:** Choose between one-card or three-card draw modes.
- **Tableau and Foundations:** Seven tableau piles and four foundation piles for building card sequences.
- **Waste and Deck:** Draw cards from the deck to the waste pile and recycle when the deck is empty.
- **Undo System:** Revert moves with a score penalty (-15 points per undo).
- **Scoring:** Tracks score with a time bonus for completing the game quickly.
- **Cross-Platform Display:** Clears console screen for Windows (cls) and Unix-like systems (clear).
- **Interactive Commands:** Simple commands to draw cards, move cards between piles, and send cards to foundations.

## File Structure
- **Card.h / Card.cpp:** Defines the Card struct with suit, value, and face-up status, along with methods to convert cards to string representations.
- **Deck.h / Deck.cpp:** Implements the Deck class for creating, shuffling, and drawing cards, with support for recycling the waste pile.
- **Game.h / Game.cpp:** Contains the Game class, handling game logic, user input, state saving for undo, and display rendering.
- **main.cpp:** Entry point that initializes and starts the game.
- **c_cpp_properties.json:** Configuration for Visual Studio Code to support IntelliSense and compilation.

## Requirements
- C++17 or later
- Standard C++ libraries (<vector>, <stack>, <chrono>, <random>, <algorithm>, <iostream>, <sstream>, <iomanip>, <ctime>)
- A C++ compiler (g++, clang++, or cl.exe for Windows)
- Optional: Visual Studio Code with C/C++ extension for IntelliSense support

## Compilation and Running
1. Clone the repository:
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Compile the program:
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++17 main.cpp Game.cpp Deck.cpp Card.cpp -o solitaire```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++17 main.cpp Game.cpp Deck.cpp Card.cpp /Fe:solitaire.exe```
3. Run the executable:
	- Unix-like systems
		```bash
		./solitaire```
	- Windows
		```cmd
		solitaire.exe```
		
## How to play
1. Start the game and choose between one-card (1) or three-card (3) draw mode.
2. The game displays the foundations, tableau, waste pile, score, and available commands.
3. Use the following commands:
	- **d:** Draw card(s) from the deck.
	- **m X Y:** Move face-up card(s) from tableau pile X to pile Y.
	- **w Y:** Move the top waste card to tableau pile Y.
	- **f X:** Move the top card from tableau pile X to its foundation.
	- **wf:** Move the top waste card to its foundation.
	- **u:** Undo the last move (-15 points).
	- **q:** Quit the game.
4. Win by moving all cards to the foundation piles (Ace to King, by suit). A time bonus is awarded based on completion speed.

## Gameplay Notes
- **Tableau Rules:** Cards must be placed in descending order (King to Ace) with alternating colors (red/black).
- **Foundation Rules:** Cards must be placed in ascending order (Ace to King) within the same suit.
- **Empty Piles:** Only Kings can be placed on empty tableau piles.
- **Undo Penalty:** Each undo reduces the score by 15 points.
- **Time Bonus:** On winning, a bonus of up to 500 points is awarded, reduced by the elapsed time in seconds.

## Future Improvements
- Add color output for red/black suits using ANSI codes.
- Implement a save/load game feature.
- Add a scoring system for specific moves (tableau to foundation).
- Support for additional Solitaire variants.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2025 Basic Console Solitaire".