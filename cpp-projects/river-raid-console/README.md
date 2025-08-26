# River Raid Console Game

## Overview
This is a C++ console-based implementation of a simplified "River Raid" game, inspired by the classic Atari game. The player controls a plane at the bottom of a 7x5 grid, moving left or right and firing mortars to destroy enemy ships (H, J, B) that spawn at the top and move downward. The game uses multithreading to handle plane movement (user input) and enemy ship/mortar movement simultaneously. The objective is to score points by destroying enemy ships while avoiding collisions. The game includes a simple text-based interface, mutex-based thread synchronization, and basic collision detection.

## Features
- **Game Board:** A 7x5 grid where the player's plane (`^`) moves at the bottom row, and enemy ships (`H`, `J`, `B`) spawn at the top and move downward.
- **Player Controls:** 
  - `A`: Move plane left.
  - `D`: Move plane right.
  - `W`: Fire a mortar (`!`) upward from the plane's position.
  - `Q`: Quit the game and display the final score.
- **Enemy Movement:** Three enemy ships spawn at random columns in the top row and move downward every 2 seconds.
- **Mortar Mechanics:** Up to 5 mortars can be active, moving upward each tick. Mortars hitting ships cause an explosion (`*`) and score a point.
- **Collision Detection:** Mortars hitting ships or ships reaching the plane's row trigger respawns and score updates.
- **Threading:** Two threads manage:
  - Player input and plane movement (`movePlane`).
  - Enemy ships and mortar movement (`moveShips`).
- **Synchronization:** Uses `std::mutex` to prevent race conditions when updating the game board.
- **Scoring:** Tracks kills (destroyed ships) and displays them after each move.
- **Game Over:** Triggered by pressing `Q`, showing the final score.

## File Structure
- **river-raid-console.cpp:** The main and only source file, containing all game logic, rendering, threading, and input handling.

## Requirements
- C++11 or later
- Standard C++ libraries (`<iostream>`, `<thread>`, `<mutex>`, `<vector>`, `<cstdlib>`, `<ctime>`, `<chrono>`)
- A C++ compiler (g++, clang++, or cl.exe for Windows)
- No external input files required

## Compilation and Running
1. Clone the repository (if applicable):
	```bash
	git clone <repository-url>
	cd <repository-directory>```
2. Compile the program:
	- On Unix-like systems (Linux/MacOS):
		```bash
		g++ -std=c++11 river-raid-console.cpp -o riverraid```
	- On Windows (with MSVC):
		```cmd
		cl /EHsc /std:c++11 river-raid-console.cpp /Fe:riverraid.exe```
3. Run the executable:
	- Unix-like systems:
		```bash
		./riverraid```
	- Windows:
		```cmd
		riverraid.exe```

## How to Use
1. Compile and run the program as described above.
2. The game will display a welcome message and controls.
3. Press S and Enter to start the game.
4. The game board is displayed, showing the plane (^), enemy ships (H, J, B), mortars (!), and explosions (*).
5. Use A and D to move the plane, W to fire mortars, and Q to quit.
6. The game updates every 2 seconds for enemy and mortar movement, with immediate updates for player actions.
7. The score (kills) is displayed below the board after each update.
8. Upon quitting (Q), the final score is shown, and the program exits.

## Project Notes
- **Game Loop:** Uses two threads: one for real-time player input and one for periodic (2-second) updates of ships and mortars.
- **Board Rendering:** ASCII-based 7x5 grid with borders, updated after each player or game tick.
- **Mortar Limits:** Supports up to 5 active mortars, cycling through slots to avoid overflow.
- **Collision Handling:** Mortars hitting ships or ships reaching the plane's row trigger explosions and respawns.
- **Randomization:** Enemy ship spawns use std::rand() with time-based seeding for varied starting positions.
- **Thread Safety:** std::mutex ensures safe concurrent access to the shared game board.
- **Performance:** Lightweight, with minimal memory usage (small fixed-size board and arrays).
- **Limitations:** No advanced collision (e.g., ships colliding with each other), no difficulty scaling, and no win condition (game ends only on quit).

## Future Improvements
- Add difficulty levels (faster ship movement or more ships).
- Implement ship-to-ship collision detection.
- Add a win condition (reach a score threshold).
- Introduce obstacles or power-ups on the board.
- Enhance visuals with colored ASCII output (using ANSI codes).
- Add sound effects or background music (platform-dependent).
- Support customizable board sizes or multiple lives for the player.
- Create a high-score system with persistent storage.

## License
This project is for personal use. Retain the copyright notice: "Thomas Hoerger - Copyright © 2024 River Raid Console Game".