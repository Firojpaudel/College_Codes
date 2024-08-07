// Design a DFA that accepts the string starting with "aa" over the alphabet {a,b}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string usersString;

    cout << "Enter a string: ";
    cin >> usersString;

    // Check if the user input string contains only 'a' and 'b' characters
    bool validString = true;
    for (char c : usersString) {
        if (c != 'a' && c != 'b') {
            validString = false;
            break;
        }
    }

    // Check if the string starts with "aa"
    bool startsWithAA = validString && usersString.substr(0, 2) == "aa";

    if (startsWithAA) {
        cout << "String is accepted." << endl;
    } else {
        cout << "String is not accepted." << endl;
    }

    return 0;
}
