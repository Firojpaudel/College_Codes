#include<iostream>
using namespace std;

// Function to solve 0-1 Knapsack with step-by-step output
void zeroOneKnapsack(int val[], int wt[], int W, int n) {
    int dp[100][100];  // 2D table for max value
    int step = 1;
    
    // Step 1: Initialize table
    cout << "Step " << step++ << ": Initializing DP table" << endl;
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            if (i == 0 || w == 0)
                dp[i][w] = 0;
        }
    }
    
    // Step 2: Fill DP table
    for (int i = 1; i <= n; i++) {
        cout << "Step " << step++ << ": Considering item " << i << " (weight = " << wt[i-1] << ", value = " << val[i-1] << ")" << endl;
        for (int w = 0; w <= W; w++) {
            if (wt[i-1] <= w) {
                dp[i][w] = max(dp[i-1][w], dp[i-1][w - wt[i-1]] + val[i-1]);
                cout << "  Weight " << w << ": Include item " << i << "? Max(" << dp[i-1][w] << ", " 
                     << dp[i-1][w - wt[i-1]] + val[i-1] << ") = " << dp[i][w] << endl;
            } else {
                dp[i][w] = dp[i-1][w];
                cout << "  Weight " << w << ": Cannot include item " << i << ", value = " << dp[i][w] << endl;
            }
        }
    }
    
    // Step 3: Print maximum value
    cout << "Step " << step++ << ": Final maximum value" << endl;
    cout << "Maximum value in knapsack: " << dp[n][W] << endl;
    
    // Step 4: Trace back to find selected items
    cout << "Step " << step++ << ": Tracing selected items" << endl;
    cout << "Selected items: ";
    int w = W, i = n;
    while (i > 0 && w > 0) {
        if (dp[i][w] != dp[i-1][w]) {
            cout << "Item " << i << " (weight = " << wt[i-1] << ", value = " << val[i-1] << ") ";
            w = w - wt[i-1];
            i--;
        } else {
            i--;
        }
    }
    cout << endl;
    
    // Print DP table for reference
    cout << "DP Table:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int w = 0; w <= W; w++) {
            cout << dp[i][w] << " ";
        }
        cout << endl;
    }
}

int main() {
    int n, W;
    cout << "Enter the number of items: ";
    cin >> n;
    int val[100], wt[100];  // Arrays for values and weights
    cout << "Enter the values of " << n << " items:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Value of item " << i + 1 << ": ";
        cin >> val[i];
    }
    cout << "Enter the weights of " << n << " items:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Weight of item " << i + 1 << ": ";
        cin >> wt[i];
    }
    cout << "Enter the knapsack capacity: ";
    cin >> W;
    
    cout << "Items:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i + 1 << ": value = " << val[i] << ", weight = " << wt[i] << endl;
    }
    
    // Perform 0-1 Knapsack
    zeroOneKnapsack(val, wt, W, n);
    
    return 0;
}