#include<iostream>
using namespace std;

// Function to print the optimal parenthesization
void printParenthesis(int s[][100], int i, int j, char& name) {
    if (i == j) {
        cout << name++;
        return;
    }
    cout << "(";
    printParenthesis(s, i, s[i][j], name);
    printParenthesis(s, s[i][j] + 1, j, name);
    cout << ")";
}

// Function to perform Matrix Chain Multiplication with step-by-step output
void matrixChainMultiplication(int p[], int n) {
    int m[100][100];  // Table for minimum scalar multiplications
    int s[100][100];  // Table for split points
    int step = 1;
    
    // Step 1: Initialize tables
    cout << "Step " << step++ << ": Initializing table for single matrices" << endl;
    for (int i = 1; i <= n; i++) {
        m[i][i] = 0;  // No multiplications for single matrix
    }
    
    // Step 2: Fill tables for chains of increasing length
    for (int l = 2; l <= n; l++) {
        cout << "Step " << step++ << ": Computing chains of length " << l << endl;
        for (int i = 1; i <= n - l + 1; i++) {
            int j = i + l - 1;
            m[i][j] = 999999;  // Infinity
            cout << "  Considering chain A" << i << " to A" << j << ": ";
            
            for (int k = i; k < j; k++) {
                int cost = m[i][k] + m[k + 1][j] + p[i - 1] * p[k] * p[j];
                cout << "Try split at k=" << k << " (cost = " << cost << "), ";
                if (cost < m[i][j]) {
                    m[i][j] = cost;
                    s[i][j] = k;
                    cout << "Updated min cost = " << m[i][j];
                }
                cout << endl;
            }
        }
    }
    
    // Step 3: Print the minimum cost and optimal parenthesization
    cout << "Step " << step++ << ": Final results" << endl;
    cout << "Minimum number of scalar multiplications: " << m[1][n] << endl;
    cout << "Optimal parenthesization: ";
    char name = 'A';
    printParenthesis(s, 1, n, name);
    cout << endl;
    
    // Print the m table for reference
    cout << "Cost table (m[i][j]):" << endl;
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j <= n; j++) {
            if (m[i][j] == 999999)
                cout << "INF ";
            else
                cout << m[i][j] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n;
    cout << "Enter the number of matrices: ";
    cin >> n;
    int p[100];  // Array to store dimensions
    cout << "Enter " << n + 1 << " dimensions (p0, p1, ..., pn):" << endl;
    for (int i = 0; i <= n; i++) {
        cout << "p" << i << ": ";
        cin >> p[i];
    }
    
    cout << "Matrix chain dimensions:" << endl;
    for (int i = 1; i <= n; i++) {
        cout << "Matrix A" << i << ": " << p[i - 1] << " x " << p[i] << endl;
    }
    
    // Perform Matrix Chain Multiplication
    matrixChainMultiplication(p, n);
    
    return 0;
}