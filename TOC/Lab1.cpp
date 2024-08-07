// Design a DFA that accepts the string "0010" over the alphabet {0,1}
#include <iostream>
#include <string>

using namespace std;

int main() {
    string usersString;

    // Prompt the user to enter a binary string
    cout << "Enter a binary string (only 0s and 1s): ";
    cin >> usersString;

    // Check if the entered string contains characters other than 0 and 1
    bool invalidInput = false;
    for (char c : usersString) {
        if (c != '0' && c != '1') {
            invalidInput = true;
            break;
        }
    }

    if (invalidInput) {
        cout << "Error: Only alphabets 0 and 1 are allowed." << endl;
    } else {
        // Print the entered string
        cout << "Entered string: " << usersString << endl;

        // Manually check if the substring "0010" is present
        string toFind = "0010";
        bool found = false;

        for (size_t i = 0; i <= usersString.length() - toFind.length(); ++i) {
            if (usersString.substr(i, toFind.length()) == toFind) {
                found = true;
                break;
            }
        }

        if (found) {
            cout << "Accepted" << endl;
        } else {
            cout << "Rejected" << endl;
        }
    }

    return 0;
}
