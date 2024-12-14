#ifndef INVERSE_XO_BOARD_H
#define INVERSE_XO_BOARD_H

#include "BoardGame_Classes.h"
#include <iostream>
#include <iomanip>

class InverseXOBoard : public Board<char> {
private:
    Player<char>** players;
public:
    InverseXOBoard(Player<char>* player[]);
    ~InverseXOBoard();
    bool update_board(int x, int y, char symbol) override;
    void display_board() override;
    bool checkStreaks(char symbol);
    bool is_win() override;
    bool is_draw() override;
    bool game_is_over() override;
};

class InverseXOPlayer : public Player<char> {
public:
    InverseXOPlayer(std::string n, char symbol);
    void getmove(int& x, int& y) override;
};

class InverseXORandomPlayer : public RandomPlayer<char> {
public:
    InverseXORandomPlayer(char symbol);
    void getmove(int& x, int& y) override;
};


//--------------------------------------- IMPLEMENTATION


InverseXOBoard::InverseXOBoard(Player<char>* player[]) {
    this->players = player;
    rows = 3;
    columns = 3;
    board = new char*[rows];
    for (int i = 0; i < rows; i++) {
        board[i] = new char[columns]();
    }
}

InverseXOBoard::~InverseXOBoard() {
    for (int i = 0; i < rows; i++) {
        delete[] board[i];
        board[i] = nullptr;
    }
    delete[] board;
    board = nullptr;
}

bool InverseXOBoard::update_board(int x, int y, char symbol) {
    if (n_moves == 9) {
        n_moves++;
        return true;
    }
    if (x >= 0 && x < this->rows && y >= 0 && y < this->columns && board[x][y] == '\0') {
        this->n_moves++;
        this->board[x][y] = symbol;
        return true;
    }
    return false;
}

void InverseXOBoard::display_board() {
    for (int i = 0; i < this->rows; i++) {
        std::cout << "\n| ";
        for (int j = 0; j < this->columns; j++) {
            if (board[i][j] == '\0')
                std::cout << "(" << i << "," << j << ") | ";
            else
                std::cout << std::setw(3) << this->board[i][j] << std::setw(5) << "| ";
        }
        std::cout << "\n-----------------------------------------";
    }
    std::cout << std::endl;
}

bool InverseXOBoard::checkStreaks(char symbol) {
    for (int i = 0; i < this->rows; i++) {
        if ((this->board[i][0] == this->board[i][1] && this->board[i][1] == this->board[i][2] && this->board[i][0] == symbol) ||
            (this->board[0][i] == this->board[1][i] && this->board[1][i] == this->board[2][i] && this->board[0][i] == symbol)) {
            return true;
        }
    }
    if ((this->board[0][0] == this->board[1][1] && this->board[1][1] == this->board[2][2] && this->board[0][0] == symbol) ||
        (this->board[0][2] == this->board[1][1] && this->board[1][1] == this->board[2][0] && this->board[0][2] == symbol)) {
        return true;
    }
    return false;
}

bool InverseXOBoard::is_win() {
    return checkStreaks(players[n_moves % 2]->getsymbol());
}

bool InverseXOBoard::is_draw() {
    return (this->n_moves == 10 && !this->is_win());
}

bool InverseXOBoard::game_is_over() {
    return this->is_win() || this->is_draw();
}

InverseXOPlayer::InverseXOPlayer(std::string n, char symbol) : Player(n, symbol) {}

void InverseXOPlayer::getmove(int& x, int& y) {
    std::cout << "Enter your move, " << name << " (row and column): ";
    std::cin >> x >> y;
}

InverseXORandomPlayer::InverseXORandomPlayer(char symbol) : RandomPlayer(symbol) {}

void InverseXORandomPlayer::getmove(int& x, int& y) {
    x = rand() % 3; 
    y = rand() % 3;
}


string get_name_Inverse() {
    string name;
    cout << "Please enter your name: ";
    cin >> name;
    return name;
}

char get_symbol_Inverse() {
    char symbol;
    do {
        cout << "Please choose a symbol [x or o]: ";
        cin >> symbol;
        symbol = tolower(symbol);
        if (symbol != 'o' && symbol != 'x') cout << "INVALID!\n";
    } while (symbol != 'o' && symbol != 'x');
    return symbol;
}

void InverseXODriver(){
    int option;
    do {
        cout << "Please choose an option.\n";
        cout << "1- Play with computer.\n";
        cout << "2- Play with a human.\n";
        cout << "3- Explain game.\n";
        cout << "4- Exit game.\n";
        cin >> option;

        if (option == 1) {
            string name = get_name_Inverse();
            char symbol = get_symbol_Inverse();

            Player<char>* player0 = new InverseXOPlayer(name, symbol);
            Player<char>* player1 = (symbol == 'o') ? new InverseXORandomPlayer('x') : new InverseXORandomPlayer('o');
            Player<char>* players[] = { player0, player1 };
            Board<char>* board = new InverseXOBoard(players);

            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        }
        else if (option == 2) {
            string name0 = get_name_Inverse();
            char symbol0 = get_symbol_Inverse();
            string name1 = get_name_Inverse();
            char symbol1 = get_symbol_Inverse();

            Player<char>* player0 = new InverseXOPlayer(name0, symbol0);
            Player<char>* player1 = new InverseXOPlayer(name1, symbol1);
            Player<char>* players[] = { player0, player1 };
            Board<char>* board = new InverseXOBoard(players);
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        }
        else if (option == 3) {
            cout << "Inverse Tic-Tac-Toe: The player who completes a row, column, or diagonal with their symbol loses the game.\n";
        }
        else if (option == 4) {
            cout << "GOOD BYE Inverse X O GAME BOARD!!\n";
            return;
        }
        else {
            cout << "INVALID!!\n";
        }
    } while (option != 4);
}



#endif // INVERSE_XO_BOARD_H
