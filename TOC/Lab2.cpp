// Design a DFA that accepts the string "aaabbb" over the alphabet {a,b}

#include <iostream>
#include <string>

using namespace std;

int main() {
    string usersString;

    cout << "Enter a string: ";
    cin >> usersString;

    // Check if the user input string is exactly "aaabbb"
    if (usersString == "aaabbb") {
        cout << "Accepted\n";
    } else {
        cout << "Rejected\n";
    }

    return 0;
}
