# Basic Console Tic Tac Toe

## Overview
This is a console-based implementation of the classic Tic-Tac-Toe game, written in C++. The game supports playing against a simple AI opponent or watching AI vs AI matches. The AI uses basic logic to prioritize winning moves, block opponent wins, or choose randomly otherwise, often resulting in draws during AI vs AI. Games can be restarted with a cleared screen, and the interface is text-based with user input for moves and choices.

## Features
- **Game Modes:** Play as X or O against the AI, or watch AI vs AI simulations.
- **AI Logic:** "Smart" AI that checks for winning opportunities, blocks opponent wins, and falls back to random moves.
- **Cross-Platform Support:** Clears the console screen on Windows (cls) and Unix-like systems (clear).
- **Restart Option:** After each game, choose to restart (clearing the screen) or quit.
- **Delay in AI Moves:** Brief pauses during AI turns for better visibility in AI vs AI mode.
- **Win/Draw Detection:** Automatically checks for wins or draws after each move.
- **User Input Validation:** Ensures valid moves and handles invalid inputs gracefully.

## File Structure
- **tictactoe.cpp:** The single source file containing all game logic, board management, AI functions, and the main loop.
- **c_cpp_properties.json:** (Optional) Configuration for Visual Studio Code to support IntelliSense and compilation.

## Requirements
- C++11 or later
- Standard C++ libraries (<iostream>, <cstdlib>, <ctime>, <thread>, <chrono>, <vector>)
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
		g++ -std=c++11 tictactoe.cpp -o tictactoe```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++latest tictactoe.cpp /Fe:tictactoe.exe```
3. Run the executable:
	- Unix-like systems
		```bash
		./tictactoe```
	- Windows
		```cmd
		tictactoe.exe```

## How to play
1. Start the game and choose a mode:
	- Play vs Computer (you'll be prompted to choose X or O).
	- Watch AI vs AI.
2. The board is displayed as a 3x3 grid with numbers 1-9 for cell positions.
3. If playing, enter a number (1-9) for your move when prompted.
4. In AI vs AI mode, moves are automatic with a short delay.
5. After a win or draw, the result is shown.
6. Enter 'r' to restart (clears screen) or 'q' to quit.

## Gameplay Notes
- Board Layout: Cells are numbered 1-9 (top-left to bottom-right) for easy input.
- Winning Conditions: Three in a row horizontally, vertically, or diagonally.
- AI Behavior: Prioritizes immediate wins, then blocks opponent wins, else random. This makes AI vs AI games typically end in draws.
- User Moves: Invalid inputs (occupied cells or out-of-range) prompt re-entry.
- Symbols: X always starts; user can choose side in vs AI mode.
- Delays: 1-second pause in AI moves for readability in simulations.

## Future Improvements
- Add color output for X/O using ANSI codes.
- Implement a menu for difficulty levels (random AI vs smart AI).
- Support for larger boards (4x4 Tic-Tac-Toe).
- Add score tracking across multiple games.
- Include sound effects or ASCII art enhancements.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2023 Basic Console Tic Tac Toe".