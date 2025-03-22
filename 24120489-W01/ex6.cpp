#include <iostream>

using namespace std;
const int n = 8; // N-Queens size
int board[n][n]; // 8x8 Chessboard
int solutions = 0; // Count valid solutions

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i ++) {
        if (board[i][col] == 1) return false; // Check column
        else if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) 
            return false;// Check left diagonal
        else if (col + (row - i) <  n &&  board[i][col + (row - i)] == 1) 
            return false; // Check right diagonal
    }
    return true;
}
void queens(int row) {
    if (row == n) {
        // All queens placed successfully
        solutions ++;
        return;
    }
    for (int col = 0; col < n; col ++) {
        if (isSafe(row, col)) {
            board[row][col] = 1; ; // Place queen
            queens(row + 1); // Recur for next row
            board[row][col] = 0; // Backtrack
        }
    }
}
//c: Marks whether a queen is placed on this column
//ld: Marks whether a queen is placed on this left diagonal
//rd: Marks whether a queen is placed on this right diagonal
bool c[1001], ld[1001], rd[1001];

void queens2(int row) {
    if (row == n) {
        solutions ++;
        return;
    }
    for (int col = 0; col < n; col ++) {
        ////check if a queen can be placed at row (row), column (col)
        if (!c[col] && !ld[row - col + n] && !rd[row + col]) {
            c[col] = ld[row - col + n] = rd[row + col] = 1;//Mark
            // Recur for next row
            queens2(row + 1);
            //BackTrack
            c[col] = ld[row - col + n] = rd[row + col] = 0;
        }
    }
}
int main() {
    queens2(0);
    cout << solutions;
    return 0;
}