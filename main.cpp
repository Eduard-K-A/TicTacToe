#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

void home(){}
// start
void start()
{
    cout << "1. Single Player" << endl;
    cout << "2. 2 Player" << endl;
    cout << "3. Exit" << endl;
}

class TicTacToe
{
private:
    char x[3][3] = {
        {'1', '2', '3'},
        {'4', '5', '6'},
        {'7', '8', '9'}}; // board

    bool done = true;

public:
    void resetBoard()
    {
        char count = '1';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                x[i][j] = count++;
        done = true;
    }

    void displayBoard()
    {
        cout << "\n";
        for (int i = 0; i < 3; i++)
        {
            for (int j = 0; j < 3; j++)
            {
                cout << x[i][j] << (j < 2 ? " | " : "");
            }
            cout << "\n";
            if (i < 2)
                cout << "--+---+--\n";
        }
        cout << "\n";
    }

    bool isValidMove(int move)
    {
        char m = move + '0';
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (x[i][j] == m)
                    return true;
        return false;
    }

    void movePlayer(int move, char symbol)
    {
        for (int i = 0; i < 3; i++)
            for (int j = 0; j < 3; j++)
                if (x[i][j] == (char)(move + '0'))
                    x[i][j] = symbol;
    }

    void twoPlayer()
    {
        cout << "Playing on 2-Player Mode!" << endl;
        cout << "Instructions: Enter the number to make a move!" << endl;

        int move;
        int turn = 0;
        done = true;

        while (done && turn < 9)

        {
            clearScreen();
            displayBoard();
            cout << "Player " << (turn % 2 == 0 ? "1 (X)" : "2 (O)") << ": ";
            cin >> move;

            while (!isValidMove(move))
            {
                cout << "Invalid move. Try again: ";
                cin >> move;
            }

            movePlayer(move, (turn % 2 == 0 ? 'X' : 'O'));
            turn++;

            if (checkWin())
            {
                displayBoard();
                cout << "Player " << (turn % 2 == 1 ? "1 (X)" : "2 (O)") << " wins!" << endl;
                done = false;

                break;
            }
        }

        if (done && turn == 9)
        {
            displayBoard();
            cout << "It's a draw!" << endl;
        }
    }

    bool checkWin()
    {
        // Horizontal and vertical
        for (int i = 0; i < 3; i++)
        {
            if (x[i][0] == x[i][1] && x[i][1] == x[i][2])
                return true;
            if (x[0][i] == x[1][i] && x[1][i] == x[2][i])
                return true;
        }

        // Diagonals
        if (x[0][0] == x[1][1] && x[1][1] == x[2][2])
            return true;
        if (x[0][2] == x[1][1] && x[1][1] == x[2][0])
            return true;

        return false;
    }
    int easyAIMove() // sequential move
    {                // easy
        for (int i = 1; i <= 9; ++i)
        {
            if (isValidMove(i))
                return i; // take first available
        }
        return -1; // fallback
    }

    void clearScreen()
    {
        system("cls"); // Windows
    }

    int mediumAIMove() // random move
    {                  // medium
        int possibleMoves[9];
        int count = 0;

        for (int i = 1; i <= 9; ++i)
        {
            if (isValidMove(i))
            {
                possibleMoves[count++] = i;
            }
        }

        if (count > 0)
        {
            int randomIndex = rand() % count;
            return possibleMoves[randomIndex];
        }

        return -1; // fallback if no move is possible
    }

    void singlePlayer()
    {
        int mode = 0;
        int move = 0;
        int turn = 0;
        bool done = true;

        cout << "Single Play!" << endl;
        cout << "Choose Easy[0] or Medium[1]: ";
        cin >> mode;

        if (mode == 0)
        {
            cout << "Easy Mode. Good luck!" << endl;
        }
        else if (mode == 1)
        {
            cout << "Medium Mode. Good luck!" << endl;
        }

        cout << "You are player 1 (X)." << endl;

        while (done && turn < 9)
        {
            clearScreen();
            if (turn % 2 == 0)
            { // player's move
                displayBoard();
                cout << "Enter move: ";
                cin >> move;

                while (!isValidMove(move))
                {
                    cout << "Invalid Move. Try again: ";
                    cin >> move;
                }
                movePlayer(move, 'X');
            }
            else
            {
                // random computer move
                cout << "Computer's move..." << endl;
                if (mode == 0)
                {
                    move = easyAIMove();
                    movePlayer(move, 'O');
                }
                else if (mode == 1)
                {
                    move = mediumAIMove();
                    movePlayer(move, 'O');
                }
            }

            turn++;

            if (checkWin())
            {
                displayBoard();
                if (turn % 2 == 1)
                {
                    cout << "You win!" << endl;
                }
                else
                {
                    cout << "Computer wins!" << endl;
                }
                done = false;
                break;
            }

            if (done && turn == 9)
            {
                cout << "It's a draw!" << endl;
            }
        }
    }
};

int main()
{
    int choice = 0;
    TicTacToe game;
    srand(time(0)); // random number generator for single play
    cout << "Welcome to Tic-Tac-Toe Game!" << endl;

    do
    {
        start();
        cout << "Choose a number: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            game.resetBoard();
            game.singlePlayer();
            break;
        case 2:
            game.resetBoard();
            game.twoPlayer();
            break;
        case 3:
            cout << "Goodbye!\n";
            break;
        default:
            cout << "Invalid Input. Please try again!\n";
            break;
        }

    } while (choice != 3);

    return 0;
}
