#include "BoardGame_Classes.h"
#include "NumericalTicTacToc.h"
#include <bits/stdc++.h>
using namespace std;
int main() {
    srand(time(0));

    while (true) {
        cout << "\n--- Numerical Tic-Tac-Toe Menu ---\n";
        cout << "1. Play Game\n";
        cout << "2. Exit\n";
        cout << "Enter your choice: ";
        int choice;
        cin >> choice;

        if (choice == 2) {
            cout << "Goodbye!\n";
            break;
        } else if (choice == 1) {
            Num<int> board;

            // Choose Player 1 type
            cout << "Choose Player 1 type:\n";
            cout << "1. Human\n";
            cout << "2. Random\n";
            int player1_choice;
            cin >> player1_choice;

            Player<int>* player1;
            if (player1_choice == 1) {
                string name;
                cout << "Enter name for Player 1: ";
                cin >> name;
                player1 = new HumanPlayer<int>(name, 1); // Player 1 uses odd numbers
            } else {
                player1 = new Random_Player<int>(1); // Computer player using odd numbers
            }

            // Choose Player 2 type
            cout << "Choose Player 2 type:\n";
            cout << "1. Human\n";
            cout << "2. Random\n";
            int player2_choice;
            cin >> player2_choice;

            Player<int>* player2;
            if (player2_choice == 1) {
                string name;
                cout << "Enter name for Player 2: ";
                cin >> name;
                player2 = new HumanPlayer<int>(name, 2); // Player 2 uses even numbers
            } else {
                player2 = new Random_Player<int>(2); // Computer player using even numbers
            }

            // Set up the players on the board
            player1->setBoard(&board);
            player2->setBoard(&board);

            Player<int>* players[2] = { player1, player2 };
            unordered_set<int> used_numbers; // Track used numbers
            board.display_board();
            int x, y;

            while (!board.game_is_over()) {
                for (int i : {0, 1}) {
                    int number;
                    cout << "Turn: " << players[i]->getname() << endl;

                    // Input for number selection
                    do {
                        if (dynamic_cast<Random_Player<int>*>(players[i])) {
                            number = (rand() % 9) + 1; // Random number between 1 and 9
                            if (used_numbers.find(number) == used_numbers.end() &&
                                ((i == 0 && number % 2 != 0) || (i == 1 && number % 2 == 0))) {
                                break;
                            }
                        } else {
                            cout << players[i]->getname() << ", enter your number: ";
                            cin >> number;
                            if (used_numbers.find(number) != used_numbers.end()) {
                                cout << "Number already used. Try again.\n";
                            } else if ((i == 0 && number % 2 == 0) || (i == 1 && number % 2 != 0)) {
                                cout << "Invalid number for the player. Try again.\n";
                            } else {
                                break;
                            }
                        }
                    } while (true);

                    used_numbers.insert(number);

                    // Now prompt for the board coordinates
                    do {
                        players[i]->getmove(x, y);
                    } while (!board.update_board(x, y, number));

                    board.display_board();
                    if (board.is_win()) {
                        cout << players[i]->getname() << " wins!\n";
                        break;
                    }
                    if (board.is_draw()) {
                        cout << "It's a draw!\n";
                        break;
                    }
                }
                if (board.is_win() || board.is_draw()) {
                    break;
                }
            }

            // Clean up dynamic memory
            delete player1;
            delete player2;

        } else {
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}