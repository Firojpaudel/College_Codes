#include<iostream>
using namespace std;

// Function to solve Subset Sum with step-by-step output
void subsetSum(int arr[], int n, int sum) {
    bool dp[100][1000];  // 2D table for subset sum possibility
    int step = 1;
    
    // Step 1: Initialize table
    cout << "Step " << step++ << ": Initializing DP table" << endl;
    for (int i = 0; i <= n; i++) {
        for (int s = 0; s <= sum; s++) {
            if (s == 0)
                dp[i][s] = true;  // Sum 0 is always achievable
            else if (i == 0)
                dp[i][s] = false;  // No items, no sum
        }
    }
    cout << "  Base case: Sum 0 is achievable for all i" << endl;
    
    // Step 2: Fill DP table
    for (int i = 1; i <= n; i++) {
        cout << "Step " << step++ << ": Considering item " << i << " (value = " << arr[i-1] << ")" << endl;
        for (int s = 1; s <= sum; s++) {
            if (arr[i-1] <= s) {
                dp[i][s] = dp[i-1][s] || dp[i-1][s - arr[i-1]];
                cout << "  Sum " << s << ": Include item " << i << "? " << (dp[i-1][s] ? "true" : "false") 
                     << " OR " << (dp[i-1][s - arr[i-1]] ? "true" : "false") << " = " << (dp[i][s] ? "true" : "false") << endl;
            } else {
                dp[i][s] = dp[i-1][s];
                cout << "  Sum " << s << ": Cannot include item " << i << ", result = " << (dp[i][s] ? "true" : "false") << endl;
            }
        }
    }
    
    // Step 3: Print result
    cout << "Step " << step++ << ": Final result" << endl;
    if (dp[n][sum]) {
        cout << "Subset with sum " << sum << " exists!" << endl;
    } else {
        cout << "No subset with sum " << sum << " exists!" << endl;
    }
    
    // Step 4: Trace back to find the subset
    if (dp[n][sum]) {
        cout << "Step " << step++ << ": Tracing subset" << endl;
        cout << "Subset elements: ";
        int s = sum, i = n;
        while (i > 0 && s > 0) {
            if (dp[i][s] != dp[i-1][s]) {
                cout << arr[i-1] << " ";
                s = s - arr[i-1];
                i--;
            } else {
                i--;
            }
        }
        cout << endl;
    }
    
    // Print DP table for reference
    cout << "DP Table:" << endl;
    for (int i = 0; i <= n; i++) {
        for (int s = 0; s <= sum; s++) {
            cout << (dp[i][s] ? "T " : "F ");
        }
        cout << endl;
    }
}

int main() {
    int n, sum;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[100];  // Array for elements
    cout << "Enter the elements:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Element " << i + 1 << ": ";
        cin >> arr[i];
    }
    cout << "Enter the target sum: ";
    cin >> sum;
    
    cout << "Set elements:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Element " << i + 1 << ": " << arr[i] << endl;
    }
    
    // Perform Subset Sum
    subsetSum(arr, n, sum);
    
    return 0;
}