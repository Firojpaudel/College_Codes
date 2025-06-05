#include <iostream>
#include <iomanip>
#include <array>
#include <string>

using namespace std;

void printLine(int width) {
    cout << string(width, '=') << endl;
}

// Validate LCM parameters
bool isValidLCMParameters(int m, int a, int c, int x0) {
    if (m <= 0) return false;
    if (a <= 0) return false;
    if (c < 0) return false;  // Increment must be non-negative
    if (x0 < 0 || x0 >= m) return false; // Seed must be in [0, m-1]
    return true;
}

int main() {
    const int SIZE = 100;
    array<int, SIZE> x;
    int m = 100, a = 5, c = 13, x0 = 11;

    // Validate parameters before generation
    if (!isValidLCMParameters(m, a, c, x0)) {
        printLine(50);
        cout << "| Error: Invalid LCM parameters.              |\n";
        printLine(50);
        return 1;
    }

    // Initialize the first number with the seed
    x[0] = x0;

    // Generate the sequence using the LCM formula
    for (int i = 0; i < SIZE - 1; i++) {
        x[i + 1] = (a * x[i] + c) % m;
    }


    printLine(50);
    cout << "| Linear Congruential Method Random Numbers      |\n";
    cout << "| Parameters: X0=" << x0 << ", m=" << m << ", a=" << a << ", c=" << c << setw(14)<<" |\n";
    printLine(50);
    cout << "| Generated Numbers (100):                       |\n";
    printLine(50);
    for (int i = 0; i < SIZE; i++) {
        cout << setw(4) << x[i];
        if (i % 10 == 9) cout << "\n";
        else cout << " ";
    }
    if (SIZE % 10 != 0) cout << "\n";
    printLine(50);

    return 0;
}