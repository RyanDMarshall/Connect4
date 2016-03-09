#include "visual.h"

using namespace std;

// End Game functions

bool four_in_a_row_of_color(const int board[6][7], int row, char color);
bool four_in_a_col_of_color(const int board[6][7], int col, char color);
bool four_in_a_diagonal_right_of_color(const int board[6][7], char color);
bool four_in_a_diagonal_left_of_color(const int board[6][7], char color);
bool four_of_color(const int board[6][7], char color);
bool four(const int board[6][7]);

int countUnknownSquares(int board[6][7]);

void endGame(const int board[6][7], bool redWins, bool yellowWins, bool tie, bool& winnerPrinted);