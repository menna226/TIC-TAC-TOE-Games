#ifndef FIVEBYFIVEBOARD_H
#define FIVEBYFIVEBOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

class FiveByFiveBoard : public Board<char> {
private:
    char odd_player_symbol;

public:
    FiveByFiveBoard();
    ~FiveByFiveBoard();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool isValid(int r, int c);
    int count_streaks(char symbol);
    int count(char symbol);
    char discover_player_at_first_move();
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class FiveByFivePlayer : public Player<char> {
public:
    FiveByFivePlayer(string n, char symbol);
    void getmove(int& x, int& y) override;
};

class FiveByFiveRandomPlayer : public RandomPlayer<char> {
public:
    FiveByFiveRandomPlayer(char symbol);
    void getmove(int& x, int& y) override;
};



//--------------------------------------- IMPLEMENTATION



FiveByFiveBoard::FiveByFiveBoard() {
    rows = 5;
    columns = 5;
    board = new char*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[columns]();
    }
}

FiveByFiveBoard::~FiveByFiveBoard() {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
        board[i] = nullptr;
    }
    delete[] board;
    board = nullptr;
}

bool FiveByFiveBoard::update_board(int x, int y, char symbol) {
    if (n_moves == 24) {
        ++n_moves;
        return true;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && board[x][y] == '\0') {
        board[x][y] = symbol;
        n_moves++;
        return true;
    }
    return false;
}

void FiveByFiveBoard::display_board() {
    for (int i = 0; i < this->rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (board[i][j] == '\0')
                cout << "(" << i << "," << j << ") | ";
            else
                cout << setw(3) << this->board[i][j] << setw(5) << "| ";
        }
        cout << "\n-----------------------------------------";
    }
    cout << endl;
}

bool FiveByFiveBoard::isValid(int r, int c) {
    if (r < 0 || r >= rows)
        return false;
    if (c < 0 || c >= columns)
        return false;
    return true;
}

int FiveByFiveBoard::count_streaks(char symbol) {
    int counter = 0;
    for (int i = 0; i < this->rows; i++) {
        for (int j = 0; j < this->columns; j++) {
            // check for horizontal
            if (isValid(i, j) && isValid(i, j + 1) && isValid(i, j + 2) && board[i][j] == symbol && board[i][j + 1] == symbol && board[i][j + 2] == symbol) {
                counter++;
            }
            // check for vertical
            if (isValid(i, j) && isValid(i + 1, j) && isValid(i + 2, j) && board[i][j] == symbol && board[i + 1][j] == symbol && board[i + 2][j] == symbol) {
                counter++;
            }
            // check for diagonal
            if (isValid(i, j) && isValid(i + 1, j + 1) && isValid(i + 2, j + 2) && board[i][j] == symbol && board[i + 1][j + 1] == symbol && board[i + 2][j + 2] == symbol) {
                counter++;
            }
            if (isValid(i, j) && isValid(i + 1, j - 1) && isValid(i + 2, j - 2) && board[i][j] == symbol && board[i + 1][j - 1] == symbol && board[i + 2][j - 2] == symbol) {
                counter++;
            }
        }
    }
    return counter;
}

int FiveByFiveBoard::count(char symbol) {
    int counter = 0;
    for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++) {
            if (board[i][j] == symbol)
                counter++;
        }
    }
    return counter;
}

char FiveByFiveBoard::discover_player_at_first_move() {
    int o_counter = count('o');
    return (o_counter == 1? 'o' : 'x'); 
}

bool FiveByFiveBoard::is_win() {
    if(n_moves == 1)
        odd_player_symbol = discover_player_at_first_move();
    
    if (n_moves < 24)
        return false;
    if (n_moves == 25)
        return true;

    int counter_for_x = count_streaks('x');
    int counter_for_o = count_streaks('o');

    cout << "X Counted: "<< counter_for_x << " " << "O Counted: "<< counter_for_o << "\n";

    if (odd_player_symbol == 'o') {
        return counter_for_x > counter_for_o;
    }
    if (odd_player_symbol == 'x') {
        return counter_for_o > counter_for_x;
    }
    return false;
}

bool FiveByFiveBoard::is_draw() {
    int counter_for_x = count_streaks('x');
    int counter_for_o = count_streaks('o');
    if (n_moves == 24 && counter_for_o == counter_for_x)
        return true;
    return false;
}

bool FiveByFiveBoard::game_is_over() {
    if (n_moves == 25)
        return true;
    return false;
}

FiveByFivePlayer::FiveByFivePlayer(string n, char symbol) : Player(n, symbol) {}

void FiveByFivePlayer::getmove(int& x, int& y) {
    cout << "Enter your move, " << name << " (row and column): ";
    cin >> x >> y;
}

FiveByFiveRandomPlayer::FiveByFiveRandomPlayer(char symbol) : RandomPlayer(symbol) {}

void FiveByFiveRandomPlayer::getmove(int& x, int& y){
    x = rand() % 5;
    y = rand() % 5;
}


char get_symbol_FiveByFive(){
    char symbol;
    do {
        cout << "Please choose a symbol [x or o]: ";
        cin >> symbol;
        symbol = tolower(symbol);
        if (symbol != 'o' && symbol != 'x') cout << "INVALID!\n";
    } while (symbol != 'o' && symbol != 'x');
    return symbol;
};
string get_name_FiveByFive(){
    string name;
    cout << "Please enter your name: ";
    cin >> name;
    return name;
};
void FiveByFiveDriver(){
    int option;
    do {
        cout << "Please choose an option.\n";
        cout << "1- Play with computer.\n";
        cout << "2- Play with a human.\n";
        cout << "3- Explain game.\n";
        cout << "4- Exit game.\n";
        cin >> option;

        if (option == 1) {
            string name = get_name_FiveByFive();
            char symbol = get_symbol_FiveByFive();

            Player<char>* player0 = new FiveByFivePlayer(name, symbol);
            Player<char>* player1 = (symbol == 'o') ? new FiveByFiveRandomPlayer('x') : new FiveByFiveRandomPlayer('o');
            Player<char>* players[2] = { player0, player1 };
            Board<char>* board = new FiveByFiveBoard();
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        }
        else if (option == 2) {
            string name0 = get_name_FiveByFive();
            char symbol0 = get_symbol_FiveByFive();
            string name1 = get_name_FiveByFive();
            char symbol1 = get_symbol_FiveByFive();

            Player<char>* player0 = new FiveByFivePlayer(name0, symbol0);
            Player<char>* player1 = new FiveByFivePlayer(name1, symbol1);
            Player<char>* players[2] = { player0, player1 };
            Board<char>* board = new FiveByFiveBoard();
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        }
        else if (option == 3) {
            cout << "This tic-tac-toe variation is played on a 5x5 grid. Players are either Xs or Os.\n";
            cout << "Players take turns placing an X or an O in one of the squares until all the squares except one are filled.\n";
            cout << "Each player has 12 turns, resulting in a total of 24 squares being filled.\n";
            cout << "Winning: The player with the most three-in-a-row sequences wins. Sequences can be vertical, horizontal, or diagonal.\n";
            cout << "A single mark can be counted in multiple three-in-a-row sequences.\n";
            cout << "If both players have the same number of three-in-a-row sequences, the game is a draw.\n";
        }
        else if (option == 4) {
            cout << "GOOD BYE 5*5 GAME BOARD!!\n";
            return;
        }
        else {
            cout << "INVALID!!\n";
        }
    } while (option != 4);
};



#endif // FIVEBYFIVEBOARD_H
