#include <iostream>
#include <ctime>
#include <windows.h>
#include <conio.h>
#include <ctype.h>

using namespace std;

void gridPrinter();
char write(int x);
void playGame();
int isGameOver(bool &gameOver);
void cls();
void computerMove();
void playAgain();
int computerMoveCompare(int a, int b, int c);

int gridElement[9]; // 0->Empty; 1->'O' (User Played); -1->'X' (Computer Played);
static bool showInstructions = true;
static int computerWins = 0;
static int playerWins = 0;

int counter=0;

int main() {

    for (int i=0; i<9; i++) {
        gridElement[i] = 0;
    };

    if (showInstructions) {
    cout << "\tNOUGHTS AND CROSSES" << endl << endl;
    cout << "     |     |     " << endl;
    cout << "  1  |  2  |  3  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  4  |  5  |  6  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  7  |  8  |  9  " << endl;
    cout << "     |     |     " << endl;

    cout << endl << "In the grid above, enter the numbers for the corresponding place to mark your turn there. ";
    cout << "The rules are simple. Standard noughts and crosses. First to get three in a row wins. May the best man win!";

    cout << endl << endl << "Press any key to continue.\t";
    getch();

    };

    playGame();
}

void playGame() {
    int result;
    bool gameOver = false;

    while (gameOver == false) {
        cls();
        gridPrinter();
        int input;

        bool validMove;

        do {
            cout << endl << endl << "Your Turn: ";

            cin >> input;

            if (cin.fail()) {
                cout << "A little more careful the next time." << endl;
                validMove = false;

                cin.clear();
                cin.ignore();
                validMove = false;
            }

            else {
                input--;

                if (input > 8 || input < 0) {
                    cout << "A little more careful the next time." << endl;
                    validMove = false;
                }

                else {
                    if (gridElement[input] == 0) {
                        validMove = true;
                        gridElement[input] = 1;
                    }

                    else {
                        cout << "A little more careful the next time." << endl;
                        validMove = false;
                    };
                };
            };

        } while (!(validMove));

        cls();
        gridPrinter();

        result = isGameOver(gameOver);

        if (result == -10) {
            Sleep(500);
            cout << endl << "..." << endl;
            Sleep(500);
            cout << endl << ".." << endl;
            Sleep(500);
            cout << endl << "." << endl;
            Sleep(500);

            computerMove();

            cls();
            gridPrinter();

            result = isGameOver(gameOver);
        };

        if (result == 1) {
            playerWins++;

            cout << endl << "YOU'VE WON!" << endl << endl;
            cout << "SCORE:" << endl << "You: " << playerWins << endl << "Me: " << computerWins << endl << endl;
            cout << "Wanna play again (y/n)?\t";


            playAgain();
        }

        else if (result == -1) {
            computerWins++;

            cout << endl << "GOTCHA!" << endl << endl;
            cout << "SCORE:" << endl << "You: " << playerWins << endl << "Me: " << computerWins << endl << endl;
            cout << "Wanna play again (y/n)?\t";


            playAgain();
        }

        else if (result == 0) {
            cout << endl << "Tie ho gya ye toh!!" << endl << endl;
            cout << "SCORE:" << endl << "You: " << playerWins << endl << "Me: " << computerWins << endl << endl;
            cout << "Waapis khelna hai (y/n)?\t";

            playAgain();
        };
    };
}

void gridPrinter() {
    cout << "\tNOUGHTS AND CROSSES" << endl << endl;
    cout << "     |     |     " << endl;
    cout << "  " << write(gridElement[0]) << "  |  " << write(gridElement[1]) << "  |  " << write(gridElement[2]) << "  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << write(gridElement[3]) << "  |  " << write(gridElement[4]) << "  |  " << write(gridElement[5]) << "  " << endl;
    cout << "_____|_____|_____" << endl;
    cout << "     |     |     " << endl;
    cout << "  " << write(gridElement[6]) << "  |  " << write(gridElement[7]) << "  |  " << write(gridElement[8]) << "  " << endl;
    cout << "     |     |     " << endl;
}

char write(int x) {
    switch(x) {
    case 1:
        return 'O';
        break;
    case -1:
        return 'X';
        break;
    default:
        return ' ';
        break;
    };
};

int isGameOver(bool &gameOver) {
    //See if a winner is there
    gameOver = false;

    if (gridElement[4] != 0) {
        int x = gridElement[4];

        if ((gridElement[0] == x) && (gridElement[8] == x)) {
            gameOver = true;
            return x;
        }

        else if ((gridElement[2] == x) && (gridElement[6] == x)) {
            gameOver = true;
            return x;
        }

        else if ((gridElement[1] == x) && (gridElement[7] == x)) {
            gameOver = true;
            return x;
        }

        else if ((gridElement[3] == x) && (gridElement[5] == x)) {
            gameOver = true;
            return x;
        };
    };

    if (gridElement[0] != 0) {
        int x = gridElement[0];

        if ((gridElement[1]) == x && (gridElement[2] == x)) {
            gameOver = true;
            return x;
        }

        else if ((gridElement[3] == x) && (gridElement[6] == x)) {
            gameOver = true;
            return x;
        };
    };

    if (gridElement[8] != 0) {
        int x = gridElement[8];

        if ((gridElement[2] == x) && (gridElement[5] == x)) {
            gameOver = true;
            return x;
        }

        else if ((gridElement[6] == x) && (gridElement[7] == x)) {
            gameOver = true;
            return x;
        };
    };

    gameOver = true;

    for (int i=0; i<9; i++) {
        if (gridElement[i] == 0) {
            gameOver = false;
            return -10;
        };
    };

    if (gameOver == true) {
        return 0;
    };
};

void cls() {
    system("cls");
}

void computerMove() {
    int imminentVictory = computerMoveCompare(0, 1, 2);

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(3, 4, 5);
    }

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(6, 7, 8);
    }

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(0, 3, 6);
    }

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(1, 4, 7);
    }

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(2, 5, 8);
    }

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(0, 4, 8);
    }

    if (imminentVictory == -42) {
        imminentVictory = computerMoveCompare(2, 4, 6);
    }

    if (imminentVictory == -42) {
        srand(time(0));
        int count = ((rand()%9)+1);

        int i = 0;

        while (count > 0) {
            if (gridElement[i] == 0) {
                count--;
            };

            i++;

            i = i%9;
        };

        gridElement[(i+8)%9] = -1;
    }

    else {
        gridElement[imminentVictory] = -1;
    }
};

int computerMoveCompare(int a, int b, int c) {
    if ((gridElement[a] == 0) && (gridElement[b] != 0) && (gridElement[b] == gridElement[c])) {
        return a;
    }

    else if ((gridElement[b] == 0) && (gridElement[c] != 0) && (gridElement[a] == gridElement[c])) {
        return b;
    }

    else if ((gridElement[c] == 0) && (gridElement[a] != 0) && (gridElement[a] == gridElement[b])) {
        return c;
    }

    else {
        return -42;
    };
};

void playAgain() {
    char playAgainInput;
    cin >> playAgainInput;

    if (playAgainInput == 'Y' || playAgainInput == 'y') {
        showInstructions = false;
        main();
    }

    else {
        cout << "See you next time!" << endl << endl;
    };
}






















