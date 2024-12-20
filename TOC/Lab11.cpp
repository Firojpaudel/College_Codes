/*
    Construct a TM for simulating a function f(x) = 2x for x = {1}.
*/
#include <iostream>
#include <string>
using namespace std;

// Function to simulate the Turing Machine
string simulateTuringMachine(string input) {
    string tape = input; // Start with the input
    int head = 0;        // Head starts at the beginning

    // Step 1: Traverse the input to mark all '1's as processed
    while (head < tape.length()) {
        if (tape[head] == '1') {
            tape[head] = 'X'; // Mark the current '1' as processed
            head++;
        } else {
            break; // Stop if we reach the end or an unexpected character
        }
    }

    // Step 2: Copy '1's for each marked 'X' to the end of the tape
    for (int i = 0; i < tape.length(); i++) {
        if (tape[i] == 'X') {
            tape += "1"; // Append '1' for each processed '1'
        }
    }

    // Step 3: Clean up the tape by replacing 'X' back to '1'
    for (int i = 0; i < tape.length(); i++) {
        if (tape[i] == 'X') {
            tape[i] = '1';
        }
    }

    return tape; // Return the final tape
}

int main() {
    string input;
    cout << "Enter the input string (only 1s representing x): ";
    cin >> input;

    // Validate input: only '1's are allowed
    for (int i = 0; i < input.length(); ++i) {  
        if (input[i] != '1') {  // Check the character at the current index
            cout << "Invalid input. Please enter a string containing only '1's." << endl;
            return 1;  // Exit with error code 1
        }
    }

    string result = simulateTuringMachine(input);

    cout << "The output tape is: " << result << endl;

    return 0;
}