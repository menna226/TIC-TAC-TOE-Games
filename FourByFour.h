#ifndef FOURBYFOURBOARD_H
#define FOURBYFOURBOARD_H

#include "BoardGame_Classes.h"
#include <vector>
#include <utility>
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <ctime>
#include <cctype>
using namespace std;

class FourByFourBoard : public Board<char> {
public:
    FourByFourBoard();
    ~FourByFourBoard();

    bool isValid(int r, int c);
    bool areAdjacent(int x1, int y1, int x2, int y2);
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool checkStreaks();
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
    vector<pair<int, int>> get_current_positions(char symbol);
};

class FourByFourPlayer : public Player<char> {
public:
    FourByFourPlayer(string n, char symbol);
    void getmove(int& x, int& y) override;
};

class FourByFourRandomPlayer : public RandomPlayer<char> {
public:
    FourByFourRandomPlayer(char symbol);
    void getmove(int& x, int& y) override;
};




//--------------------------------------- IMPLEMENTATION


FourByFourBoard::FourByFourBoard() {
    rows = 4;
    columns = 4;
    board = new char*[rows];
    for(int i = 0; i < rows; i++){
        board[i] = new char[columns]();
    }
    board[0][0] = 'o';
    board[0][1] = 'x';
    board[0][2] = 'o';
    board[0][3] = 'x';
    board[rows-1][0] = 'x';
    board[rows-1][1] = 'o';
    board[rows-1][2] = 'x';
    board[rows-1][3] = 'o';
}

FourByFourBoard::~FourByFourBoard(){
    for(int i = 0; i < rows; i++){
        delete [] board[i];
        board[i] = nullptr;
    }
    delete[] board;
    board = nullptr;
}

bool FourByFourBoard::isValid(int r, int c) {
    return !(r < 0 || r >= rows || c < 0 || c >= columns);
}

bool FourByFourBoard::areAdjacent(int x1, int y1, int x2, int y2) {
    return abs(x1 - x2) + abs(y1 - y2) == 1;
}

bool FourByFourBoard::update_board(int x, int y, char symbol) {
    if(x == -1 || y == -1) return false;

    int tx = x & 3;
    int ty = (x >> 2) & 3;
    if(board[tx][ty] != symbol) return false;

    int new_row = y & 3;
    int new_column = (y >> 2) & 3;
    if(!areAdjacent(tx, ty, new_row, new_column) || board[new_row][new_column] != '\0')
        return false;

    board[new_row][new_column] = board[tx][ty];
    board[tx][ty] = '\0';
    return true;
}

void FourByFourBoard::display_board() {
    for (int i = 0; i < rows; i++) {
        cout << "\n| ";
        for (int j = 0; j < columns; j++) {
            if(board[i][j] == '\0')
                cout << "(" << i << "," << j << ") | ";
            else
                cout << setw(3) << board[i][j] << setw(5) << "| ";
        }
        cout << "\n-----------------------------------------";
    }
    cout << endl;
}

bool FourByFourBoard::checkStreaks() {
    int counter = 0;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if (isValid(i, j + 2) && board[i][j] == board[i][j + 1] && board[i][j + 2] == board[i][j] && board[i][j] != '\0') {
                return true;
            }
            if (isValid(i + 2, j) && board[i][j] == board[i+1][j] && board[i][j] == board[i+2][j] && board[i][j] != '\0') {
                return true;
            }
            if (isValid(i + 2, j + 2) && board[i][j] == board[i + 1][j + 1] && board[i][j] == board[i + 2][j + 2] && board[i][j] != '\0') {
                return true;
            }
            if (isValid(i - 2, j - 2) && board[i][j] == board[i - 1][j - 1] && board[i][j] == board[i - 2][j - 2] && board[i][j] != '\0') {
                return true;
            }
        }
    }
    return false;
}

bool FourByFourBoard::is_win() {
    return checkStreaks();
}

bool FourByFourBoard::is_draw() {
    return false;
}

bool FourByFourBoard::game_is_over() {
    return is_win();
}

vector<pair<int, int>> FourByFourBoard::get_current_positions(char symbol) {
    vector<pair<int, int>> positions;
    for(int i = 0; i < rows; i++) {
        for(int j = 0; j < columns; j++) {
            if(board[i][j] == symbol) {
                positions.push_back({i, j});
            }
        }
    }
    return positions;
}

FourByFourPlayer::FourByFourPlayer(string n, char symbol) : Player(n, symbol) {}

void FourByFourPlayer::getmove(int& x, int& y) {
    int tx, ty, new_row, new_column;
    cout << "Choose the position you want to move " << name << " (row and column): ";
    cin >> tx >> ty;
    if(tx > 3 || ty > 3){
        x = -1; 
        y = -1;
        return;
    }
    x = tx | (ty << 2);
    cout << "Enter your move, " << " (row and column): ";
    cin >> new_row >> new_column;
    if(new_row > 3 || new_column > 3){
        x = -1; 
        y = -1;
        return;
    }
    y = new_row | (new_column << 2);
}

FourByFourRandomPlayer::FourByFourRandomPlayer(char symbol) : RandomPlayer(symbol) {}

void FourByFourRandomPlayer::getmove(int& x, int& y) {
    int tx, ty, new_row, new_column;
    FourByFourBoard* fourByFourBoard = static_cast<FourByFourBoard*>(boardPtr);
    vector<pair<int, int>> positions = fourByFourBoard->get_current_positions(symbol);

    int randomIndex = rand() % positions.size();
    tx = positions[randomIndex].first;
    ty = positions[randomIndex].second;
    x = tx | (ty << 2);

    vector<pair<int, int>> adjacent_positions;
    if (fourByFourBoard->isValid(tx - 1, ty)) adjacent_positions.push_back({tx - 1, ty});
    if (fourByFourBoard->isValid(tx + 1, ty)) adjacent_positions.push_back({tx + 1, ty});
    if (fourByFourBoard->isValid(tx, ty - 1)) adjacent_positions.push_back({tx, ty - 1});
    if (fourByFourBoard->isValid(tx, ty + 1)) adjacent_positions.push_back({tx, ty + 1});

    int randomAdjacentIndex = rand() % adjacent_positions.size();
    new_row = adjacent_positions[randomAdjacentIndex].first;
    new_column = adjacent_positions[randomAdjacentIndex].second;
    y = new_row | (new_column << 2);
}


string get_name_FourByFour() {
    string name;
    cout << "Please enter your name: " << name << "\n";
    cin >> name;
    return name;
}

char get_symbol_FourByFour() {
    char symbol;
    do {
        cout << "Please choose a symbol [x or o]: " << "\n";
        cin >> symbol;
        symbol = tolower(symbol);
        if (symbol != 'o' && symbol != 'x') cout << "INVALID!\n";
    } while (symbol != 'o' && symbol != 'x');
    return symbol;
}

void FourByFourDriver() {
    int option;
    do {
        cout << "Please choose an option.\n";
        cout << "1- Play with computer.\n";
        cout << "2- Play with a human.\n";
        cout << "3- Explain game.\n";
        cout << "4- Exit game.\n";
        cin >> option;

        if(option == 1){
            string name = get_name_FourByFour();
            char symbol = get_symbol_FourByFour();

            Player<char>* player0 = new FourByFourPlayer(name, symbol);
            Player<char>* player1 = (symbol == 'o') ? new FourByFourRandomPlayer('x') : new FourByFourRandomPlayer('o');
            Player<char>* players[2] = {player0, player1};
            Board<char>* board = new FourByFourBoard();
            player1->setBoard(board);
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        } 
        else if(option == 2){
            string name0 = get_name_FourByFour();
            char symbol0 = get_symbol_FourByFour();
            string name1 = get_name_FourByFour();
            char symbol1 = get_symbol_FourByFour();

            Player<char>* player0 = new FourByFourPlayer(name0, symbol0);
            Player<char>* player1 = new FourByFourPlayer(name1, symbol1);
            Player<char>* players[2] = {player0, player1};
            Board<char>* board = new FourByFourBoard();
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        } 
        else if(option == 3){
            cout << "The game is a variation of Tic-Tac-Toe, where players can move pieces on a 4x4 board. The goal is to align three of your pieces in a row, column, or diagonal." << endl;
        } 
        else if(option == 4){
            cout << "GOOD BYE 4*4 GAME BOARD!!\n";
            return;
        } 
        else{
            cout << "INVALID!!\n";
        }
    }while(option != 4);
}


#endif // FOURBYFOURBOARD_H
