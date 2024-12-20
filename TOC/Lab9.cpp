#include <iostream>
#include <string>
using namespace std;

// Function to simulate the NFA
bool simulateNFA(string input) {
    int state = 0;

    for (int i = 0; i < input.length(); i++) {
        char symbol = input[i];
        switch (state) {
            case 0:
                if (symbol == '0')
                    state = 1;
                else
                    state = 0;
                break;
            case 1:
                if (symbol == '1')
                    state = 2;
                else
                    state = 1;
                break;
            case 2:
                if (symbol == '1')
                    state = 3;
                else
                    state = 2;
                break;
            case 3:
                if (symbol == '1')
                    state = 3;
                else
                    state = 2;
                break;
        }
    }

    return state == 3;
}

int main() {
    string input;
    cout << "Enter the input string (0/1): ";
    cin >> input;

    if (simulateNFA(input)) {
        cout << "The string " << input << " is accepted by the NFA." << endl;
    } else {
        cout << "The string " << input << " is rejected by the NFA." << endl;
    }

    return 0;
}
