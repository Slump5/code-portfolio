// Thomas Hoerger - Copyright © 2023 Basic Console Tic Tac Toe
// ----------------------------------------------------
// Turn-based Tic-Tac-Toe with simple AI logic.
// The user can choose to:
//   1. Play against the computer as X or O.
//   2. Watch the computer play both sides (AI vs AI).
//
// The AI is "smart": it tries to win if possible, otherwise it blocks
// the opponent from winning. If neither is possible, it picks randomly.
// This makes the AI vs AI almost always end in a draw.
//
// After each game, the user can restart (r) or quit (q).
// When restarting, the screen is cleared so only the new game shows.
//

#include <iostream>
#include <cstdlib>      // For std::system() and std::rand()
#include <ctime>        // For seeding random generator
#include <thread>       // For std::this_thread::sleep_for()
#include <chrono>       // For std::chrono::seconds
#include <vector>       // For storing empty cells for random move

#ifdef _WIN32
    #define CLEAR_CMD "cls"   // Windows uses cls to clear console
#else
    #define CLEAR_CMD "clear" // Linux/macOS uses clear
#endif

// Game board and state
char board[3][3];         // 3x3 Tic-Tac-Toe board
bool game_over = false;    // Flag to track if game has ended
bool is_draw = false;      // Flag to track if game is a draw
bool user_playing = false; // True if user chose to play against AI
char user_symbol = 'X';    // Will be set if user is playing
char ai_symbol   = 'O';    // Opposite of user

// Clear console screen
void clear_screen() {
    std::system(CLEAR_CMD); // Executes system command to clear terminal
}

// Reset game state
void reset_game() {
    // Set all cells to empty
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            board[i][j] = ' ';
    game_over = false;  // Reset game over flag
    is_draw = false;    // Reset draw flag
}

// Check if game is over
bool is_game_over() {
    // Check rows and columns for a win
    for (int i = 0; i < 3; ++i) {
        if (board[i][0] != ' ' && board[i][0] == board[i][1] && board[i][1] == board[i][2])
            return true; // Row win
        if (board[0][i] != ' ' && board[0][i] == board[1][i] && board[1][i] == board[2][i])
            return true; // Column win
    }
    // Check diagonals for a win
    if (board[0][0] != ' ' && board[0][0] == board[1][1] && board[1][1] == board[2][2])
        return true; // Main diagonal
    if (board[0][2] != ' ' && board[0][2] == board[1][1] && board[1][1] == board[2][0])
        return true; // Anti-diagonal

    // Check for draw: if all cells are filled and no winner
    bool draw = true;
    for (int i = 0; i < 3; ++i)
        for (int j = 0; j < 3; ++j)
            if (board[i][j] == ' ')
                draw = false; // At least one empty cell exists

    if (draw) {
        is_draw = true; // Mark game as draw
        return true;
    }
    return false; // Game continues
}

// Print board to console
void print_board() {
    for (int i = 0; i < 3; ++i) {
        for (int j = 0; j < 3; ++j) {
            std::cout << board[i][j]; // Print cell content
            if (j < 2) std::cout << "|"; // Print vertical separator
        }
        std::cout << std::endl;
        if (i < 2) std::cout << "-----" << std::endl; // Print horizontal separator
    }
    std::cout << std::endl; // Extra line for readability
}

// Check if placing `player` in (r,c) makes them win
bool is_winning_move(int r, int c, char player) {
    if (board[r][c] != ' ') return false; // Cannot place on non-empty cell
    board[r][c] = player; // Temporarily place symbol
    bool win = false;

    // Check row, column, and both diagonals
    if ((board[r][0] == player && board[r][1] == player && board[r][2] == player) ||
        (board[0][c] == player && board[1][c] == player && board[2][c] == player) ||
        (board[0][0] == player && board[1][1] == player && board[2][2] == player) ||
        (board[0][2] == player && board[1][1] == player && board[2][0] == player)) {
        win = true; // Found winning combination
    }
    board[r][c] = ' '; // Undo temporary move
    return win;
}

// AI move: try to win, block, or random
void ai_move(char player) {
    char opponent = (player == 'X') ? 'O' : 'X'; // Determine opponent symbol

    // 1. Try to win by checking all empty spots
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (is_winning_move(r, c, player)) {
                board[r][c] = player; // Make winning move
                std::cout << "Player " << player << " plays to WIN at (" << r+1 << "," << c+1 << ")\n";
                print_board();
                std::this_thread::sleep_for(std::chrono::seconds(1)); // Pause for readability
                return;
            }

    // 2. Block opponent's winning move
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (is_winning_move(r, c, opponent)) {
                board[r][c] = player; // Block opponent
                std::cout << "Player " << player << " BLOCKS at (" << r+1 << "," << c+1 << ")\n";
                print_board();
                std::this_thread::sleep_for(std::chrono::seconds(1));
                return;
            }

    // 3. Otherwise pick a random empty spot
    std::vector<std::pair<int,int>> empty;
    for (int r = 0; r < 3; ++r)
        for (int c = 0; c < 3; ++c)
            if (board[r][c] == ' ')
                empty.push_back({r,c}); // Collect all empty cells

    if (!empty.empty()) {
        int idx = std::rand() % empty.size(); // Pick random index
        int r = empty[idx].first;
        int c = empty[idx].second;
        board[r][c] = player; // Make random move
        std::cout << "Player " << player << " plays randomly at (" << r+1 << "," << c+1 << ")\n";
        print_board();
        std::this_thread::sleep_for(std::chrono::seconds(1));
    }
}

// User makes a move
void user_move(char player) {
    int row, col;
    while (true) {
        // Prompt user for input
        std::cout << "Your turn (" << player << ")! Enter row (1-3) and column (1-3): ";
        std::cin >> row >> col;
        row--; col--; // Convert to 0-based index
        if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == ' ') {
            board[row][col] = player; // Place symbol
            break;
        } else {
            std::cout << "Invalid move, try again.\n"; // Invalid input
        }
    }
    print_board(); // Show updated board
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr))); // Seed random generator
    char input;

    do {
        clear_screen(); // Clear previous game display
        reset_game();   // Reset board and game state

        // Choose mode
        std::cout << "Choose game mode:\n";
        std::cout << "1. Play vs Computer\n";
        std::cout << "2. Watch AI vs AI\n";
        std::cout << "Enter choice (1 or 2): ";
        int mode;
        std::cin >> mode;
        user_playing = (mode == 1); // If 1, user will play

        if (user_playing) {
            std::cout << "Do you want to be X (go first) or O (go second)? Enter X or O: ";
            std::cin >> user_symbol;
            user_symbol = toupper(user_symbol); // Ensure uppercase
            ai_symbol = (user_symbol == 'X') ? 'O' : 'X'; // Opposite for AI
        }

        print_board(); // Show empty board
        char current_player = 'X'; // X always starts

        // Game loop
        while (!game_over) {
            if (user_playing && current_player == user_symbol) {
                user_move(user_symbol); // User's turn
            } else {
                ai_move(current_player); // AI's turn
            }

            // Check for win/draw
            if (is_game_over()) {
                if (is_draw)
                    std::cout << "It's a draw!\n";
                else
                    std::cout << "Player " << current_player << " wins!\n";
                game_over = true;
                break;
            }

            // Switch player
            current_player = (current_player == 'X') ? 'O' : 'X';
        }

        // Prompt for restart or quit
        std::cout << "\nGame over. Type 'r' to restart or 'q' to quit: ";
        std::cin >> input;

    } while (input == 'r'); // Loop if user chooses to restart

    std::cout << "Thanks for playing! Goodbye.\n";
    return 0;
}
