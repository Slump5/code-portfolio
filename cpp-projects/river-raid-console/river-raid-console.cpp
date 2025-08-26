// Thomas Hoerger - Copyright © 2024 River Raid Console Game
// -----------------------------------------
// Console-based River Raid style game
// Player controls a plane and fires mortars to destroy descending ships.
// Features:
// - 3 ships (H, J, B) moving down the board
// - Player can move left/right and fire mortars
// - Mortars cycle through 5 slots
// - Board updates every 2 seconds for ships/mortars
// - Game ends when player quits (Q)

// Include necessary libraries
#include <iostream>   // For input/output
#include <thread>     // For multithreading (plane and ship movement)
#include <mutex>      // For thread-safe updates to board
#include <vector>     // For storing ship positions and mortars
#include <cstdlib>    // For rand()
#include <ctime>      // For seeding random generator

std::mutex mtx;      // Mutex to prevent race conditions during board updates
bool GameOver = false; // Global flag to end the game

// Structure to represent a ship
struct Ship {
    int row;       // Current row of the ship
    int col;       // Current column of the ship
    char symbol;   // Character to display on the board
};

// Initialize 3 ships at starting positions
Ship shipH{6, 2, 'H'};
Ship shipJ{5, 3, 'J'};
Ship shipB{3, 2, 'B'};

// Game board: 7 rows x 5 columns
// '^' represents the plane, other cells are empty
char board[7][5] = {
    {' ', ' ', '^', ' ', ' '}, // Plane starting position
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '},
    {' ', ' ', ' ', ' ', ' '}
};

int kills = 0;                     // Tracks total ships destroyed
int Mortar[5][2] = {{0,0},{0,0},{0,0},{0,0},{0,0}}; // Stores active mortar positions
int planePosition = 2;             // Current column of the plane

// Utility function to check if two ships occupy the same cell
bool samePosition(const Ship &a, const Ship &b) {
    return (a.row == b.row && a.col == b.col);
}

// Respawn a ship at the top row, avoiding collisions with other ships
void newShip(Ship &ship) {
    do {
        ship.col = std::rand() % 5; // Random column between 0 and 4
        ship.row = 6;               // Top row
    } while (
        (ship.col == shipH.col && ship.symbol != 'H') ||
        (ship.col == shipJ.col && ship.symbol != 'J') ||
        (ship.col == shipB.col && ship.symbol != 'B')
    );
}

// Print the current game board to the console
void printGame() {
    std::cout << "---------------\n||           ||\n";
    for (int i = 6; i >= 0; i--) {   // Print from top row to bottom
        std::cout << "|| ";
        for (int j = 0; j < 5; j++) {
            std::cout << board[i][j]; // Print cell contents
            if (j < 4) std::cout << "|"; // Column separator
        }
        std::cout << " ||\n";
        if (i >= 1) std::cout << "---------------\n";
    }
    std::cout << "||           ||\n---------------\n";
    std::cout << "Kills: " << kills << "\n********************************\n";
}

// Check if a mortar hit a ship and update kills & respawn
bool isKill(int row, int col) {
    if (board[row][col] == 'H') { newShip(shipH); kills++; return true; }
    if (board[row][col] == 'J') { newShip(shipJ); kills++; return true; }
    if (board[row][col] == 'B') { newShip(shipB); kills++; return true; }
    return false;
}

// Thread function: handles plane movement and firing
void movePlane() {
    int mortarTracker = 0;  // Index to track which mortar slot to use
    while (!GameOver) {
        char move;
        std::cin >> move;   // Get user input (A/D/W/Q)

        std::lock_guard<std::mutex> lock(mtx); // Lock board for thread-safe updates
        board[0][planePosition] = ' ';         // Clear old plane position

        switch (toupper(move)) {
            case 'D': // Move plane right
                if (planePosition < 4) planePosition++;
                else std::cout << "Can't move further right!\n";
                break;

            case 'A': // Move plane left
                if (planePosition > 0) planePosition--;
                else std::cout << "Can't move further left!\n";
                break;

            case 'W': { // Fire mortar
                int fireRow = 1; // Just above the plane
                int fireCol = planePosition;

                if (isKill(fireRow, fireCol)) {   // Check for immediate ship hit
                    board[fireRow][fireCol] = '*'; // Explosion marker
                } else {
                    // Launch mortar in available slot
                    Mortar[mortarTracker][0] = fireRow;
                    Mortar[mortarTracker][1] = fireCol;
                    board[fireRow][fireCol] = '!';
                    mortarTracker = (mortarTracker + 1) % 5; // Cycle through 5 mortar slots
                }
                break;
            }

            case 'Q': // Quit game
                GameOver = true;
                std::cout << "\nQuitting game.\nFinal Score: " << kills;
                std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Pause to show final score
                return;

            default:
                std::cout << "Invalid input.\n";
        }

        board[0][planePosition] = '^'; // Draw plane at new position
        printGame();                    // Show updated board
    }
}

// Thread function: moves ships downward and updates mortars
void moveShips() {
    while (!GameOver) {
        std::this_thread::sleep_for(std::chrono::milliseconds(2000)); // Update every 2 seconds
        std::lock_guard<std::mutex> lock(mtx); // Lock board for safe updates

        // 1. Move existing mortars upward
        for (int i = 0; i < 5; i++) {
            if (Mortar[i][0] > 0) {             // Only active mortars
                board[Mortar[i][0]][Mortar[i][1]] = ' '; // Clear old spot
                Mortar[i][0]++;                 // Move mortar up

                if (Mortar[i][0] >= 7) {       // Remove mortar if it goes off board
                    Mortar[i][0] = 0;
                    continue;
                }

                if (isKill(Mortar[i][0], Mortar[i][1])) { // Check for hit
                    board[Mortar[i][0]][Mortar[i][1]] = '*'; // Explosion
                    Mortar[i][0] = 0;                        // Remove mortar
                } else {
                    board[Mortar[i][0]][Mortar[i][1]] = '!'; // Draw mortar
                }
            }
        }

        // 2. Move ships downward
        Ship* ships[] = {&shipH, &shipJ, &shipB};
        for (Ship* s : ships) {
            board[s->row][s->col] = ' '; // Clear old ship position
            if (s->row <= 1) {           // If ship reached top, respawn
                newShip(*s);
            } else {
                s->row--;                // Move ship down
            }

            // Check if ship hits an active mortar
            bool hit = false;
            for (int i = 0; i < 5; i++) {
                if (Mortar[i][0] == s->row && Mortar[i][1] == s->col) {
                    board[s->row][s->col] = '*'; // Explosion
                    newShip(*s);                 // Respawn ship
                    Mortar[i][0] = 0;            // Remove mortar
                    kills++;                      // Increase kill count
                    hit = true;
                    break;
                }
            }

            if (!hit) {
                board[s->row][s->col] = s->symbol; // Draw ship if safe
            }
        }

        printGame(); // Show updated board

        // 3. Clear explosion markers after showing them once
        for (int i = 0; i < 7; i++) {
            for (int j = 0; j < 5; j++) {
                if (board[i][j] == '*') {
                    board[i][j] = ' ';
                }
            }
        }
    }
}

// Main function: initialize game and start threads
int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random generator

    // Welcome screen
    std::cout << "=============================\n";
    std::cout << "   Welcome to River Raid!\n";
    std::cout << "=============================\n";
    std::cout << "Controls: A = Left, D = Right, W = Fire, Q = Quit\n";
    std::cout << "Press S then Enter to start the game...\n";

    char start;
    do {
        std::cin >> start;                  // Wait for player to press 'S'
    } while (toupper(start) != 'S');

    printGame();                            // Print initial empty board

    // Start threads for plane control and ship/mortar movement
    std::thread t1(movePlane);
    std::thread t2(moveShips);

    t1.join(); // Wait for threads to finish
    t2.join();

    std::cout << "You sunk " << kills << " ships!\n"; // Final score
    return 0;
}
