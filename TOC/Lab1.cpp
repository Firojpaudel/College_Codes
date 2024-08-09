// Design a DFA that accepts the string "0010" over the alphabet {0,1}
#include <iostream>
#include <string>

using namespace std;

int main() {
    string usersString;

    // Prompt the user to enter a binary string
    cout << "Enter a binary string (only 0s and 1s): ";
    cin >> usersString;

    // Check if the entered string is exactly "0010"
    if (usersString == "0010") {
        cout << "Accepted" << endl;
    } else {
        cout << "Rejected" << endl;
    }

    return 0;
}
