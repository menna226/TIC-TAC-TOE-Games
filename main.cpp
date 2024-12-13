#include "BoardGame_Classes.h"

#include"FourInRowGame.h"
#include<bits/stdc++.h>
using namespace std;


int main() {
    int choice;
    Player<char>* players[2];
    fourinrowBoard<char>* B = new fourinrowBoard<char>();
    string playerXName, player2Name;

    cout << "Welcome to FoutInRow Game. :)\n";

    // Set up player 1
    cout << "Enter Player 1 name: ";
    cin >> playerXName;
    cout << "Choose Player 1 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[0] = new humanPlayer<char>(playerXName, 'X');
            break;
        case 2:
            players[0] = new Random_Player<char>('X');
            break;
        default:
            cout << "Invalid choice for Player 1. Exiting the game.\n";
            return 1;
    }

    // Set up player 2
    cout << "Enter Player 2 name: ";
    cin >> player2Name;
    cout << "Choose Player 2 type:\n";
    cout << "1. Human\n";
    cout << "2. Random Computer\n";
    cin >> choice;

    switch(choice) {
        case 1:
            players[1] = new humanPlayer<char>(player2Name, 'O');
            break;
        case 2:
            players[1] = new Random_Player<char>('O');
            break;
        default:
            cout << "Invalid choice for Player 2. Exiting the game.\n";
            return 1;
    }

    // Create the game manager and run the game
    GameManager<char> fourinrowBoard(B, players);
    fourinrowBoard.run();

    // Clean up
    delete B;
    for (int i = 0; i < 2; ++i) {
        delete players[i];
    }

    return 0;
}


