#include <iostream>
#include "driver.h"
#include "visual.h"

using namespace std;

const int UNKNOWN = 0;
const int RED = 1;
const int BLUE = 2;

const int NUM_ROWS = 6;
const int NUM_COLS = 7;

bool four_in_a_row_of_color(const int board[6][7], int row, char color) {

    for (int i = 0; i < (NUM_COLS - 3); i++) {
        if ((board[row][i] == color) && (board[row][i + 1] == color) &&
            (board[row][i + 2] == color) && board[row][i + 3] == color) {

            return true;
        }
    }

    return false;
}
bool four_in_a_col_of_color(const int board[6][7], int col, char color) {

    for (int i = 0; i < (NUM_ROWS - 3); i++) {
        if ((board[i][col] == color) && (board[i + 1][col] == color) &&
            (board[i + 2][col] == color) && board[i + 3][col] == color) {
            return true;
        }
    }

    return false;
}
bool four_in_a_diagonal_right_of_color(const int board[6][7], char color) {

    for (int i = 0; i < (NUM_ROWS - 3); i++) {
        for (int j = 3; j < NUM_COLS; j++) {
            if ((board[i][j] == color) && (board[i + 1][j - 1] == color) &&
                (board[i + 2][j - 2] == color) && (board[i + 3][j - 3] == color)) {

                return true;
            }
        }
    }

    return false;
}
bool four_in_a_diagonal_left_of_color(const int board[6][7], char color) {

    for (int i = 0; i < (NUM_ROWS - 3); i++) {
        for (int j = 0; j < (NUM_COLS - 3); j++) {
            if ((board[i][j] == color) && (board[i + 1][j + 1] == color) &&
                (board[i + 2][j + 2] == color) && (board[i + 3][j + 3] == color)) {

                return true;
            }
        }
    }

    return false;
}
bool four_of_color(const int board[6][7], char color) {

    for (int i = 0; i < NUM_ROWS; i++) {
        if (four_in_a_row_of_color(board, i, color)) {
            return true;
        }
    }

    for (int i = 0; i < NUM_COLS; i++) {
        if (four_in_a_col_of_color(board, i, color)) {
            return true;
        }
    }

    if (four_in_a_diagonal_left_of_color(board, color) || four_in_a_diagonal_right_of_color(board, color)) {
        return true;
    }

    return false;
}
bool four(const int board[6][7]) {

    return (four_of_color(board, RED) || four_of_color(board, BLUE));
}

int countUnknownSquares(int board[6][7]) {
    int unknownCount = 0;

    for (int i = 0; i < 6; i++) {
        for (int j = 0; j < 7; j++) {
            if (board[i][j] == 0) {
                unknownCount++;
            }
        }
    }

    return unknownCount;
}

void endGame(const int board[6][7], bool redWins, bool yellowWins, bool tie, bool& winnerPrinted) {

    setup();
    
    if (!winnerPrinted) {
        
        if (redWins) {
            cout << "RED WINS!" << endl;
            winnerPrinted = true;
        }
        else if (yellowWins) {
            cout << "YELLOW WINS!" << endl;
        }
        else if (tie) {
            cout << "It's a tie." << endl;
        }

        exit;
    }
}