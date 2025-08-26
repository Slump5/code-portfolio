# Console Dominoes Game

## Overview
This is a console-based implementation of a two-player Dominoes game, written in C++. The game pits a human player against a simple AI opponent. Each player starts with 10 domino pieces, with the remaining 8 pieces forming a boneyard for drawing. Players take turns placing dominoes on the head or tail of the table, matching numbers to connect pieces. The game ends when one player runs out of pieces, declaring them the winner.

## Features
- **Two-Player Mode:** Human vs. AI gameplay.
- **Domino Mechanics:** 28 unique domino pieces (0-0 to 6-6), with 10 dealt to each player and 8 in the boneyard.
- **Turn-Based Play:** Players place dominoes on either the head or tail of the table, ensuring matching numbers.
- **Boneyard Drawing:** Players draw from the boneyard when no playable pieces are available.
- **AI Logic:** The AI plays valid pieces by prioritizing tail matches, then head matches, or draws if no moves are possible.
- **Game End Detection:** The game ends when one player has no pieces left, with the winner and remaining pieces displayed.
- **Cross-Platform Support:** Console clearing works on Windows (`cls`) and Unix-like systems (`clear`).
- **Restart Option:** After each game, choose to restart (clears screen) or quit.
- **Input Validation:** Ensures valid user inputs for piece selection and placement (head/tail).

## File Structure
- **game.cpp:** The main source file containing all game logic, domino management, player/AI behavior, and the game loop.
- **settings.json:** Configures file associations for Visual Studio Code (e.g., associating `thread` with C++).
- **tasks.json:** Defines the build task for compiling the game using `g++`.
- **launch.json:** Configures debugging in Visual Studio Code with `gdb`.

## Requirements
- C++11 or later
- Standard C++ libraries (`<iostream>`, `<vector>`, `<algorithm>`, `<random>`, `<ctime>`, `<stdexcept>`, `<thread>`, `<chrono>`)
- A C++ compiler (`g++`, `clang++`, or `cl.exe` for Windows)
- Optional: Visual Studio Code with C/C++ extension for IntelliSense and debugging support
- MSYS2 or MinGW for Windows users (for `g++` and `gdb` as specified in `launch.json`)

## Compilation and Running
1. Clone the repository:
   ```bash
   git clone <repository-url>
   cd <repository-directory>```
2. Compile the program:
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++11 game.cpp -o dominoes```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++latest tictactoe.cpp /Fe:tictactoe.exe```
3. Run the executable:
	- Unix-like systems
		```bash
		./dominoes```
	- Windows
		```cmd
		dominoes.exe```
		
## How to Play
1. The game starts by randomly selecting the first player (human or AI).
2. The table is displayed, showing placed dominoes ([3|4] for a domino with 3 and 4 pips).
3. Human Turn:
	- Your hand is shown with numbered dominoes (1:[2|5] 2:[4|4]).
	- Enter the number of the domino to play.
	- If the domino can be played on both ends, choose h (head) or t (tail).
	- Invalid inputs (e.g., unplayable pieces or wrong positions) prompt re-entry.
4. AI Turn: The AI automatically selects a playable piece, preferring the tail, then the head, and draws if no moves are possible.
5. Drawing: If no playable pieces exist, the player draws from the boneyard until a playable piece is found or the boneyard is empty.
6. The game ends when one player has no pieces left.
7. The winner is announced, showing the opponent’s remaining pieces and the final table.
8. Enter r to restart (clears screen) or q to quit.

## Gameplay Notes
- **Domino Representation:** Each domino is shown as [left|right] (e.g., [3|4] for 3 pips on the left, 4 on the right).
- **Table Layout:** The table wraps after 8 pieces for readability.
- **Playable Pieces:** A domino can be played if either side matches the table’s head or tail value. The piece is flipped if needed.
- **First Move:** The first piece sets both head and tail; subsequent pieces connect to either end.
- **AI Behavior:** The AI prioritizes tail matches, then head matches, ensuring valid plays or drawing when necessary.
- **Delays:** Brief pauses (800ms) after AI moves and draws improve readability.

## Future Improvements
- Add ASCII art or color output for dominoes using ANSI codes.
- Implement a smarter AI with strategic piece selection (maximizing future plays).
- Add a scoring system based on remaining pieces’ pips.
- Support multiplayer mode (human vs. human).
- Include a graphical interface using a library like SFML or SDL.
- Add a menu for selecting game modes or difficulty levels.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 Dominoes Console Game".