/*
    Construct a PDA that accepts string over Σ ={a,b} that contains equal number of a’s followed by equal number of b’s.
*/

#include <iostream>
#include <string>
using namespace std;

// Function to simulate the PDA
bool simulatePDA(string input) {
    int stack = 0; // Stack simulation using a counter
    bool seenB = false; // Track if 'b' has been seen

    for (int i = 0; i < input.length(); i++) {
        char symbol = input[i];

        if (symbol == 'a') {
            if (seenB) return false; // Reject if 'a' comes after 'b'
            stack++; // Push 'a' onto the stack
        } else if (symbol == 'b') {
            seenB = true; // Mark that 'b' has been seen
            if (stack == 0) {
                return false; // More 'b's than 'a's
            }
            stack--; // Pop 'a' from the stack
        } else {
            return false; // Invalid symbol
        }
    }

    return stack == 0; // Accept if stack is empty
}

int main() {
    string input;
    cout << "Enter the input string (a/b): ";
    cin >> input;

    if (simulatePDA(input)) {
        cout << "The string " << input << " is accepted by the PDA." << endl;
    } else {
        cout << "The string " << input << " is rejected by the PDA." << endl;
    }

    return 0;
}
