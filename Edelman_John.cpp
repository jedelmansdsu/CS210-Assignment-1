#include <iostream>
#include <limits> // Used for input checking
#include <vector>
using namespace std;


class TicTacToe {
    char player;
    int turns_elapsed;
public:
    /* Constructor*/
    TicTacToe(){
        player = 'X';
        turns_elapsed = 0;
    }
    /* This is your game board*/

    vector<vector<char>> gameBoard
    {
    {'1', '2', '3'},
    {'4', '5', '6'},
    {'7', '8', '9'}
    };

    const unsigned long long max_gameboard_size = {gameBoard.size() * gameBoard[0].size()}; // Will be 9 on a normal 3x3 board

    /* This prints your game board*/
    void printGameBoard()
    {
        for (int i = 0; i < gameBoard.size(); i++)
        {
            for (int j = 0; j < gameBoard[i].size(); j++)
            {
                cout << gameBoard[i][j] << " ";
            }
            cout << endl;
        }
    }

    void switchPlayer() {
        if (player == 'X') {
            player = 'O';
        } else if (player == 'O') {
            player = 'X';
        }
    }

    char getPlayer() {
        return player;
    }

    void elapseTurn() {
        turns_elapsed++;
    }

    int getTurnsElapsed() {
        return turns_elapsed;
    }

    /* This method modifes the game board*/
    void modifyGameBoard(char player, int position)
    {
        /*write code to modify the game board here*/
        // Will check if position is valid in main function for easier control flow
        gameBoard[position / gameBoard.size()][position % gameBoard.size()] = player; // I should buy a hat that says #1 MODULO FAN
    }

    // Check if a player has won the game
    bool checkWin(char player) {
        for (int i = 0; i < gameBoard.size(); i++) {
            if (gameBoard[i][0] == player && gameBoard[i][1] == player && gameBoard[i][2] == player) {
                // Check rows for win condition
                return true;
            }
            if (gameBoard[0][i] == player && gameBoard[1][i] == player && gameBoard[2][i] == player) {
                // Check columns for win condition
                return true;
            }
        }
        if (gameBoard[1][1] == player) {
            // Check diagonals for win condition
            if ((gameBoard[0][0] == player && gameBoard[2][2] == player) || (gameBoard[2][0] == player && gameBoard[0][2] == player)) {
                return true;
            }
        }
        return false;
    }

    // Check if the game is a draw
    bool checkDraw() {
        // If there are no open spaces left, the game is a draw
        if (turns_elapsed >= 8) {
            return true;
        }
        return false;
    }
};

int main() {
    cout << "TIC TAC TOE" << endl;
    TicTacToe game;
    while (true) {
        game.printGameBoard();

        int position = -1;
        // Gets the position to place X or O in, ignoring invalid inputs
        while (position < 0 || position > game.max_gameboard_size - 1) {
            cout << "Player " << game.getPlayer() << " enter position:";
            cin >> position;
            position -= 1; // Accounts for the fact that the vector is zero-indexed, but the visible board is indexed starting from 1
            if (position < 0 || position > game.max_gameboard_size - 1) {
                cout << "Please input an integer between 1 and " << game.max_gameboard_size << "." << endl;
                if (cin.fail()) {
                    // Handles non-integer input to stop the program from breaking when characters are written to cin
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    /* This last line is a little beyond my limited C++ knowledge, but from what I understand based on my research,
                     * numeric_limits is a class template, providing the method max() to determine the maximum possible size of
                     * streamsize, which is also the maximum possible size of the input stream. Therefore, cin.ignore flushes
                     * all of the bad input, up until it reaches a newline (the delimiter). I'm sure I'll get a better grasp
                     * on this as I use more C++. */
                }
            } else if (game.gameBoard[position / 3][position % 3] == 'X' || game.gameBoard[position / 3][position % 3] == 'O') {
                cout << "You can't make a move on an occupied space!" << endl;
                position = -1;
            }

        }
        game.modifyGameBoard(game.getPlayer(), position); // Places an X or O at the chosen position

        if (game.checkWin(game.getPlayer()) == true) {
            game.printGameBoard();
            cout << "Player " << game.getPlayer() << " wins!" << endl;
            break;
        }
        if (game.checkDraw() == true) {
            game.printGameBoard();
            cout << "The game is a draw!" << endl;
            break;
        }
        game.switchPlayer();
        game.elapseTurn();
    }
    cout << "GAME OVER" << endl;
    return 0;
}