#include "BoardGame_Classes.h"
#include <bits/stdc++.h>

template <typename T>
class fourinrowBoard : public Board<T> {
private:
    // Helper function to check if there is a winning line in any direction (horizontal, vertical, diagonal).
    bool check_direction(int x, int y, int dx, int dy) {
        T symbol = this->board[x][y];
        
        // Check the next 3 cells in the given direction
        for (int step = 1; step < 4; ++step) {
            int nx = x + step * dx; // Calculate new x position
            int ny = y + step * dy; // Calculate new y position
            
            // If out of bounds or the cells don't match the symbol, return false
            if (nx < 0 || nx >= this->rows || ny < 0 || ny >= this->columns || this->board[nx][ny] != symbol)
                return false;
        }
        return true; // If all 4 cells match the symbol, return true
    }

public:
    // Constructor to initialize a 6x7 grid (standard Connect 4 board).
    fourinrowBoard() {
        this->rows = 6;
        this->columns = 7;
        this->board = new T*[this->rows];
        
        // Initialize each row in the board.
        for (int i = 0; i < this->rows; ++i) {
            this->board[i] = new T[this->columns]();
        }
    }

    // Function to update the board with a symbol at the given column.
    bool update_board(int x, int y, T symbol) {
        // Check if the column is within bounds
        if (y < 0 || y >= this->columns || x != 0) return false;
        
        // Traverse from bottom to top to find the first empty row in the column
        for (int i = this->rows - 1; i >= 0; --i) {
            if (this->board[i][y] == 0) { // Empty cell found
                this->board[i][y] = symbol; // Place the symbol
                ++this->n_moves; // Increment the number of moves
                return true;
            }
        }
        return false; // No empty space in the column
    }

    // Function to display the board in a readable format
    void display_board() {
        // Print column indices for easier reference
        for (int j = 0; j < this->columns; ++j) {
            cout << "  " << j << " "; // Display column number
        }
        cout << endl;

        // Print the grid, each cell enclosed in brackets for clarity
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] == 0) {
                    cout << "[ ] "; // Empty cell
                } else {
                    cout << "[" << this->board[i][j] << "] "; // Occupied cell
                }
            }
            cout << endl; // Move to the next row after printing all columns
        }
        cout << "---------------" << endl; // Separator after printing the grid
    }

    // Function to check if there is a winner by scanning all cells
    bool is_win() {
        // Loop through each cell in the grid to check for a potential win starting from each cell
        for (int i = 0; i < this->rows; ++i) {
            for (int j = 0; j < this->columns; ++j) {
                if (this->board[i][j] != 0) { // Check only non-empty cells
                    // Check for winning conditions in all 4 directions (horizontal, vertical, diagonal)
                    if (check_direction(i, j, 0, 1) || // Horizontal check
                        check_direction(i, j, 1, 0) || // Vertical check
                        check_direction(i, j, 1, 1) || // Diagonal down-right check
                        check_direction(i, j, 1, -1)) // Diagonal down-left check
                        return true; // If a win is found in any direction, return true
                }
            }
        }
        return false; // No winner found
    }

    // Function to check if the board is full and the game is a draw (no winner)
    bool is_draw() {
        return this->n_moves == this->rows * this->columns; // Game is a draw if all cells are filled
    }

    // Function to check if the game is over (either win or draw)
    bool game_is_over() {
        return is_win() || is_draw(); // Game is over if there is a winner or a draw
    }
};

// Human player class that allows for manual player input
template <typename T>
class humanPlayer : public Player<T> {
public:
    // Constructor to initialize a human player with a name and symbol
    humanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

    // Function to get the player's move (which column to place the symbol in)
    void getmove(int& x, int& y) {
        cout << this->name << ", enter column (0-6): "; // Prompt the player to choose a column
        cin >> y; // Player input for the column
        x = 0; // Always zero for column-based input (Connect 4 works column by column)
    }
};

// Random player class that generates a random move
template <typename T>
class Random_Player : public RandomPlayer<T> {
public:
    // Constructor for a random player with a symbol
    Random_Player(T symbol) : RandomPlayer<T>(symbol) {
        this->dimension = 3;
        this->name = "Random Computer Player"; // Set the player's name
        srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
    }

    // Function to generate a random move (random column choice)
    void getmove(int& x, int& y) {
        x = 0; // Always zero (since Connect 4 moves happen by column)
        y = rand() % 7; // Randomly pick a column from 0 to 6
    }
};












