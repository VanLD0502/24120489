#include <iostream>

using namespace std;
const int n = 9;
int board[n][n];
int solutions = 0;
bool isSafe(int row, int col) {
    for (int i = 0; i < row; i ++) {
        if (board[i][col] == 1) return false;
        else if (col - (row - i) >= 0 && board[i][col - (row - i)] == 1) return false;
        else if (col + (row - i) <  n&&  board[i][col + (row - i)] == 1) {
            return false;
        }
    }
    return true;
}
void queens(int row) {
    if (row == n) {
        solutions ++;
        return;
    }
    for (int col = 0; col < n; col ++) {
        if (isSafe(row, col)) {
            board[row][col] = 1;
            queens(row + 1);
            board[row][col] = 0;
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
        if (!c[col] && !ld[row - col + n] && !rd[row + col]) {
            c[col] = ld[row - col + n] = rd[row + col] = 1;
            queens2(row + 1);
            c[col] = ld[row - col + n] = rd[row + col] = 0;
        }
    }
}
int main() {
    queens2(0);
    cout << solutions;
    return 0;
}