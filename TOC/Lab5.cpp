// Design a DFA that accepts substring "aa" over the alphabet {a,b}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string userString;

    cout << "Enter a string: ";
    cin >> userString;

    // Check if the user input string contains only 'a' and 'b' characters
    bool validString = true;
    for (char c : userString) {
        if (c != 'a' && c != 'b') {
            validString = false;
            break;
        }
    }

    // Check if the string contains "aa"
    bool containsAA = false;
    for (int i = 0; i < userString.length() - 1; i++) {
        if (userString[i] == 'a' && userString[i + 1] == 'a') {
            containsAA = true;
            break;
        }
    }

    if (containsAA) {
        cout << "String is accepted." << endl;
    } else {
        cout << "String is not accepted." << endl;
    }

    return 0;
}