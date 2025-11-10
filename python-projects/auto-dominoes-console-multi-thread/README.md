# Auto Dominoes (Multithreading Example)

## Overview
This is a console-based implementation of a multithreaded Dominoes game, written in Python.  
The program demonstrates the use of **multithreading**, **thread synchronization**, and **safe concurrent access** to shared resources, simulating two automated players taking turns to place domino pieces on a shared game table.

## Features
- **Multithreaded Gameplay:** Each player runs in a separate thread.
- **Thread Safety:** Uses `threading.Lock` to prevent race conditions.
- **Automated Turns:** Players automatically place or draw pieces based on available moves.
- **Shared Game State:** The table and remaining domino pool are synchronized.
- **Automatic Win/Draw Detection:** The game ends when a player wins or both pass.
- **Clean Console Output:** Clearly displays player turns, moves, and table updates.
- **Randomized Start:** A random player begins each game for variety.

## File Structure
- **auto-dominoes.py:** Contains the main game logic and all class definitions.
- **Auto-Dominoes-Implementation-Steps.docx:** Provides a detailed explanation of how the game and multithreading system were implemented.
- **README.md:** Documentation and usage instructions for the program.

### Key Classes
- **CPlayer:** Represents a player, holding their pieces and performing safe thread operations.
- **CDominoes:** Generates all 28 domino tiles (0|0 through 6|6).
- **CRandom:** Shuffles the domino pieces randomly.
- **CTable:** Handles synchronized display of the game table in ASCII format.
- **GameState:** Manages player turns, remaining pieces, and synchronized shared data.

## Requirements
- Python 3.10 or later
- Standard Python libraries (`threading`, `random`, `time`)
- Terminal or command prompt to view console output

## Running the Program
1. Clone the repository:
	```bash
	git clone <repository-url>
	cd <repository-directory>
	```
2. Run the program:
	```bash
	python auto-dominoes.py
	```
3. The game will automatically start, randomly selecting a player to begin.

## How to Play
1. The program simulates two players running in parallel threads.
2. Each player attempts to place a domino piece that matches either end of the table.
3. If a player has no matching piece, they draw from the remaining pile.
4. If the draw pile is empty, the player passes.
5. The game continues until:
	- One player runs out of dominoes (win), or  
	- Both players pass (draw).

## Gameplay Notes
- **Automatic Flipping:** Pieces are flipped automatically to match connections.
- **Turn Synchronization:** Threads wait for their turn using `GameState` locks.
- **Draw Behavior:** Players draw from the pool if no match is found.
- **Ending Conditions:** The game declares a winner or draw automatically.
- **Thread-Safe Display:** The table is printed using synchronized console access.

## Future Improvements
- Add manual input for real-time player interaction.
- Extend to multiplayer (3–4 players) with dynamic threading.
- Add scoring and match history logging.
- Implement GUI using Tkinter or Pygame for visual display.

## License
This project is for personal use.  
Retain the copyright:
**Thomas Hoerger - Copyright © 2025 Auto Dominoes Multithreading Example**
