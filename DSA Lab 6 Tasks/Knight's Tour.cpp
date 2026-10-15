#include <iostream>
#include <iomanip>
using namespace std;

const int MAX_N = 20;               
int N;
int board[MAX_N][MAX_N];            
long long callCount = 0;            

const int dx[8] = { 2, 1, -1, -2, -2, -1, 1, 2 };   
const int dy[8] = { 1, 2, 2, 1, -1, -2, -2, -1 };   

bool isSafe(int r, int c) {
    return r >= 0 && r < N && c >= 0 && c < N && board[r][c] == -1;
}

bool solveKnightTour(int row, int col, int moveNumber) {
    ++callCount;
    board[row][col] = moveNumber;               

    if (moveNumber == N * N) return true;      

    for (int k = 0; k < 8; ++k) {
        int nr = row + dx[k], nc = col + dy[k];
        if (isSafe(nr, nc)) {
            if (solveKnightTour(nr, nc, moveNumber + 1))
                return true;
        }
    }

    board[row][col] = -1;                      
    return false;
}

void printBoard() {
    for (int i = 0; i < N; ++i) {
        for (int j = 0; j < N; ++j) cout << setw(4) << board[i][j];
        cout << "\n";
    }
}

int main() {
    int sx, sy;
    cout << "Enter board size N (1-" << MAX_N << "): ";
    cin >> N;
    cout << "Enter starting row and column (starting from 0): ";
    cin >> sx >> sy;

    if (N < 1 || N > MAX_N || sx < 0 || sx >= N || sy < 0 || sy >= N) {
        cout << "Invalid input.\n";
        return 1;
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            board[i][j] = -1;

    if (solveKnightTour(sx, sy, 1)) {
        cout << "Tour found:\n";
        printBoard();
    }
    else {
        cout << "No tour was found by the search from (" << sx << ", " << sy << ").\n";
    }
    cout << "Recursive calls made: " << callCount << "\n";
    return 0;
}