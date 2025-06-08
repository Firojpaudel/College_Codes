#include<iostream>
using namespace std;

// Function to check if a queen can be placed at board[row][col]
bool isSafe(int board[][100], int row, int col, int N) {
    // Check column above
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }
    // Check upper-left diagonal
    for (int i = row, j = col; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }
    // Check upper-right diagonal
    for (int i = row, j = col; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }
    return true;
}

// Function to solve N-Queens with step-by-step output
bool nQueens(int board[][100], int row, int N, int& step) {
    // Base case: all queens placed
    if (row == N) {
        cout << "Step " << step++ << ": Solution found!" << endl;
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < N; j++) {
                cout << (board[i][j] == 1 ? "Q " : ". ");
            }
            cout << endl;
        }
        return true;
    }
    
    // Try placing queen in each column of current row
    cout << "Step " << step++ << ": Trying to place queen in row " << row << endl;
    for (int col = 0; col < N; col++) {
        if (isSafe(board, row, col, N)) {
            cout << "  Placing queen at (" << row << ", " << col << ")" << endl;
            board[row][col] = 1;
            
            // Recursively place queens in next rows
            if (nQueens(board, row + 1, N, step))
                return true;
            
            // Backtrack if placement fails
            cout << "Step " << step++ << ": Backtracking, removing queen from (" << row << ", " << col << ")" << endl;
            board[row][col] = 0;
        }
    }
    cout << "Step " << step++ << ": No valid placement in row " << row << endl;
    return false;
}

int main() {
    int N;
    cout << "Enter the board size (N): ";
    cin >> N;
    int board[100][100] = {0};  // Initialize board with 0 (no queens)
    int step = 1;
    
    cout << "Initial board:" << endl;
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << ". ";
        }
        cout << endl;
    }
    
    // Solve N-Queens
    if (!nQueens(board, 0, N, step)) {
        cout << "Step " << step++ << ": No solution exists for N = " << N << endl;
    }
    
    return 0;
}