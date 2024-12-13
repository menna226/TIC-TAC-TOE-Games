#include "BoardGame_Classes.h"
#include<iostream>
#include <iomanip> 
#include <cstdlib>
#include <ctime>
#include <cctype>
#include <vector>
using namespace std;


class FourByFourBoard: public Board<char>{
    private:
    int new_row;
    int new_column;
    FourByFourRandomPlayer* random_player;
    public:
    FourByFourBoard(FourByFourRandomPlayer* player) : random_player(player){
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
    ~FourByFourBoard(){
        for(int i = 0; i < rows; i++){
            delete [] board[i];
            board[i] = nullptr;
        }
        delete[] board;
        board = nullptr;
    }
    bool isValid(int r, int c){
        if(r < 0 || r >= rows)
            return false;
        if (c < 0 || c >= columns)
            return false;
        return true;    
    }
    bool areAdjacent(int x1, int y1, int x2, int y2){
    return abs(x1 - x2) + abs(y1 - y2) == 1;
    }
    bool update_board(int x, int y, char symbol) override{
        if(!isValid(x, y) || board[x][y] != symbol)
            return false;
        if(random_player == nullptr){
            cout << "Enter your move, " << " (row and column): ";
            cin >> new_row >> new_column;
            if(!isValid(new_row, new_column) || !areAdjacent(x, y, new_row, new_column) || board[new_row][new_column] != '\0')
                return false;
        }
        else if(random_player != nullptr){

        }
        
        board[new_row][new_column] = board[x][y];
        board[x][y] = '\0';
        return true;
    }
    void display_board() override{
        for (int i = 0; i < this->rows; i++) {
            cout << "\n| ";
            for (int j = 0; j < this->columns; j++) {
                if(board[i][j] == '\0')
                    cout << "(" << i << "," << j << ") | ";
                else
                    cout << setw(3) << this->board[i][j] << setw(5) << "| ";
            }
            cout << "\n-----------------------------------------";
        }
        cout << endl;
    }
    bool checkStreaks(){
        int counter = 0;
        for(int i = 0; i < this->rows; i++){
            for(int j = 0; j < this->columns; j++){
                // check for horizontal
                if (isValid(i, j + 2) && board[i][j] == board[i][j + 1] && board[i][j + 2] == board[i][j] && board[i][j] != '\0') {
                    return true;
                }
                // check for vertical
                if (isValid(i+2, j) && board[i][j] == board[i+1][j] && board[i][j]== board[i+2][j] && board[i][j] != '\0') {
                    return true;
                }
                // check for diagonal
                if (isValid(i+2, j+2) && board[i][j] == board[i+1][j+1]  && board[i][j] == board[i+2][j+2] && board[i][j] != '\0') {
                    return true;
                }
                if (isValid(i-2, j-2) && board[i][j] == board[i-1][j-1]  && board[i][j] == board[i-2][j-2] && board[i][j] != '\0') {
                    return true;
                }
            }
        }
        return false;
    }
    bool is_win() override{
       return checkStreaks();
    } 
    bool is_draw() override{
        return false;
    }
    bool game_is_over() override{
        return is_win();
    }
    vector<pair<int, int>> get_avaliable_positions_for_randomplayer(){
        vector<pair<int, int>> positions;
        for(int i = 0; i < rows; i++){
            for(int j = 0; j < columns; j++){
                if(board[i][j] == random_player->getsymbol()){
                    positions.push_back({i, j});
                }
            }
        }
        return positions;
    }
};

class FourByFourPlayer : public Player<char>{
    public:
    int current_row;
    int current_column;
    FourByFourPlayer(string n, char symbol): Player(n, symbol){}
    void getmove(int& x, int& y) override{
        cout << "Choose the position you want to move " << name << " (row and column): ";
        cin >> x >> y;
        

    }
};

class FourByFourRandomPlayer : public RandomPlayer<char>{
    public:
    FourByFourRandomPlayer(char symbol) : RandomPlayer(symbol){}
    void getmove(int& x, int& y) override{
        FourByFourBoard* fourByFourBoard = static_cast<FourByFourBoard*>(boardPtr);
        vector<pair<int, int>> positions = fourByFourBoard->get_avaliable_positions_for_randomplayer();
            int randomIndex = rand() % positions.size(); 
            x = positions[randomIndex].first;  
            y = positions[randomIndex].second;
    }
};

string get_name(){
    string name;
    cout << "Please enter your name: " << name << "\n";
    cin >> name;
    return name;
}
char get_symbol(){
    char symbol;
    do{
        cout << "Please choose a symbol [x or o]: " << "\n";
        cin >> symbol;
        symbol = tolower(symbol); 
        if (symbol != 'o' && symbol != 'x') cout << "INVALID!\n";
    }while (symbol != 'o' && symbol != 'x');
    return symbol;
}

int main(){
    int option;
    do {
        cout << "Please choose an option.\n";
        cout << "1- Play with computer.\n";
        cout << "2- Play with a human.\n";
        cout << "3- Explain game.\n";
        cout << "4- Exit game.\n";
        cin >> option;

        if(option == 1){
            string name = get_name();
            char symbol = get_symbol();

            Player<char>* player0 = new FourByFourPlayer(name, symbol);
            Player<char>* player1 = (symbol == 'o') ? new FourByFourRandomPlayer('x') : new FourByFourRandomPlayer('o');
            Player<char>* players[2] = {player0, player1};
            Board<char>* board = new FourByFourBoard(static_cast<FourByFourRandomPlayer*>(player1));
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        } 
        else if(option == 2){
            string name0 = get_name();
            char symbol0 = get_symbol();
            string name1 = get_name();
            char symbol1 = get_symbol();

            Player<char>* player0 = new FourByFourPlayer(name0, symbol0);
            Player<char>* player1 = new FourByFourPlayer(name1, symbol1);
            Player<char>* players[2] = {player0, player1};
            Board<char>* board = new FourByFourBoard(nullptr);
            GameManager<char> gameManager(board, players);
            gameManager.run();
            delete player0;
            delete player1;
            delete board;
        } 
        else if(option == 3){
        
        } 
        else if(option == 4){
            cout << "GOOD BYE 4*4 GAME BOARD!!\n";
            exit(0);
        } 
        else{
            cout << "INVALID!!\n";
        }
    }while(option != 4);
}
