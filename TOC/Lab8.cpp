// Design a DFA that accepts the string which has number of 'a' twice than the number of 'b' over the alphabet {a,b}

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

    // Check if the string has number of 'a' twice than the number of 'b'
    int countA = 0, countB = 0;
    for (char c : userString) {
        if (c == 'a') {
            countA++;
        } else if (c == 'b') {
            countB++;
        }
    }

    bool hasTwiceAsManyAs = validString && countA == 2 * countB;

    if (hasTwiceAsManyAs) {
        cout << "String is accepted." << endl;
    } else {
        cout << "String is not accepted." << endl;
    }

    return 0;
}