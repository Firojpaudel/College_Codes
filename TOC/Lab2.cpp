// Design a DFA that accepts the string "aaabbb" over the alphabet {a,b}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string usersString;

    cout << "Enter a string: ";
    cin >> usersString;

    // Check if the user input string contains only 'a' and 'b' characters and if it contains the substring "aaabbb"
    bool validString = true;
    for (char c : usersString) {
        if (c != 'a' && c != 'b') {
            validString = false;
            break;
        }
    }

    if (validString && usersString.find("aaabbb") != -1) {
        cout << "YES\n";
    } else {
        cout << "NO\n";
    }

    return 0;
}
