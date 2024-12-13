#include <bits/stdc++.h>
#include "BoardGame_Classes.h"

using namespace std;

// Template class for the board
template <typename T>
class Num : public Board<T> {
public:
    // Constructor for the Num class to initialize a 3x3 board
    Num();

    // Function to update the board with a move at position (x, y)
    bool update_board(int x, int y, T symbol);

    // Function to display the current state of the board
    void display_board();

    // Function to check if there is a winner (sum of 15 in any row, column, or diagonal)
    bool is_win();

    // Function to check if the game has ended in a draw
    bool is_draw();

    // Function to check if the game is over (either won or drawn)
    bool game_is_over();
};

// Constructor for Num class
template <typename T>
Num<T>::Num() {
    this->rows = 3; // Set number of rows (3x3 grid)
    this->columns = 3; // Set number of columns (3x3 grid)
    this->board = new T*[this->rows]; // Dynamically allocate memory for the rows

    // Allocate memory for each column in each row
    for (int i = 0; i < this->rows; ++i) {
        this->board[i] = new T[this->columns](); // Initialize cells with 0
    }
}

// Function to update the board with a move
template <typename T>
bool Num<T>::update_board(int x, int y, T symbol) {
    // Check if the move is out of bounds or if the cell is already occupied
    if (x < 0 || x >= this->rows || y < 0 || y >= this->columns || this->board[x][y] != 0) {
        return false; // Invalid move
    }
    
    // Place the symbol in the cell
    this->board[x][y] = symbol;
    ++this->n_moves; // Increment the number of moves
    return true; // Valid move
}

// Function to display the current board
template <typename T>
void Num<T>::display_board() {
    // Loop through the rows
    for (int i = 0; i < this->rows; ++i) {
        // Loop through the columns
        for (int j = 0; j < this->columns; ++j) {
            // Print empty space or the current symbol in the cell
            if (this->board[i][j] == 0) {
                cout << "[ ] "; // Empty cell
            } else {
                cout << "[" << this->board[i][j] << "] "; // Occupied cell with symbol
            }
        }
        cout << endl; // Print a new line at the end of each row
    }
    cout << "---------------" << endl; // Print a separator line after the board
}

// Function to check if there's a winner
template <typename T>
bool Num<T>::is_win() {
    // Check each row and column to see if the sum of the values is 15 (winning condition)
    for (int i = 0; i < 3; i++) {
        // Check each row and column
        if (this->board[i][0] + this->board[i][1] + this->board[i][2] == 15) return true; // Row sum
        if (this->board[0][i] + this->board[1][i] + this->board[2][i] == 15) return true; // Column sum
    }
    
    // Check diagonals (left-to-right and right-to-left)
    if (this->board[0][0] + this->board[1][1] + this->board[2][2] == 15) return true;
    if (this->board[0][2] + this->board[1][1] + this->board[2][0] == 15) return true;
    
    return false; // No winner found
}

// Function to check for a draw
template <typename T>
bool Num<T>::is_draw() {
    // Check if all cells are filled and no winner exists
    return this->n_moves == this->rows * this->columns && !is_win();
}

// Function to check if the game is over (either won or drawn)
template <typename T>
bool Num<T>::game_is_over() {
    return is_win() || is_draw(); // Game ends if there's a winner or it's a draw
}

// Template class for HumanPlayer
template <typename T>
class HumanPlayer : public Player<T> {
public:
    // Constructor for HumanPlayer that initializes the player's name and symbol
    HumanPlayer(string name, T symbol);

    // Function to get the human player's move
    void getmove(int& x, int& y);
};

// Constructor for HumanPlayer
template <typename T>
HumanPlayer<T>::HumanPlayer(string name, T symbol) : Player<T>(name, symbol) {}

// Get move from the human player
template <typename T>
void HumanPlayer<T>::getmove(int& x, int& y) {
    // Prompt the player to enter the row and column for the move
    cout << this->name << ", enter your move (row and column): ";
    cin >> x >> y; // Read row and column inputs
}

// Template class for RandomPlayer
template <typename T>
class Random_Player : public Player<T> {
public:
    // Constructor for RandomPlayer that initializes the player's symbol
    Random_Player(T symbol);

    // Function to get the computer player's move (random)
    void getmove(int& x, int& y);
};

// Constructor for RandomPlayer
template <typename T>
Random_Player<T>::Random_Player(T symbol) : Player<T>("Computer", symbol) {
    srand(static_cast<unsigned int>(time(0))); // Seed the random number generator
}

// Get move from the random player
template <typename T>
void Random_Player<T>::getmove(int& x, int& y) {
    // Keep generating random moves until a valid move is found
    while (true) {
        x = rand() % 3; // Random row (0 to 2)
        y = rand() % 3; // Random column (0 to 2)

        // Ensure the chosen cell is empty (valid move)
        if (this->boardPtr->update_board(x, y, 0)) {
            break; // Valid move found, exit loop
        }
    }

    // Output the chosen move
    cout << "Computer chooses move: " << x << " " << y << endl;
}
