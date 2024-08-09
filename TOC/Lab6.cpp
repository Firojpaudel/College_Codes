// Design a DFA that contains odd number of 1s over the alphabet {0,1}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string userString;

    cout << "Enter a string: ";
    cin >> userString;

    // Check if the user input string contains only '0' and '1' characters
    bool validString = true;
    for (char c : userString) {
        if (c != '0' && c != '1') {
            validString = false;
            break;
        }
    }

    // Check if the string contains odd number of '1's
    int countOnes = 0;
    for (char c : userString) {
        if (c == '1') {
            countOnes++;
        }
    }

    bool containsOddOnes = validString && countOnes % 2 != 0;

    if (containsOddOnes) {
        cout << "String is accepted." << endl;
    } else {
        cout << "String is not accepted." << endl;
    }

    return 0;
}