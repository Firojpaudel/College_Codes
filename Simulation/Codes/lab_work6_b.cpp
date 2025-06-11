#include <iostream>
#include <iomanip>
#include <array>
#include <string>

using namespace std;


void printLine(int width) {
    cout << string(width, '=') << endl; 
}

// Function to validate LCM parameters
bool isValidLCMParameters(int m, int a, int c, int x0) {
    if (m <= 0) return false;
    if (a <= 0) return false;
    if (c < 0) return false;
    if (x0 < 0 || x0 >= m) return false; // Seed must be in [0, m-1]
    return true;
}

int main() {
    const int SIZE = 100;
    array<int, SIZE> x; // Fixed-size array for random numbers
    int m = 1000, a = 15, c = 7, x0 = 13; // LCM parameters

    // Validate parameters
    if (!isValidLCMParameters(m, a, c, x0)) {
        printLine(50);
        cout << "| Error: Invalid LCM parameters.              |\n";
        printLine(50);
        return 1;
    }

    // Initialize the first number with the seed
    x[0] = x0;

    // Generate random numbers using the Linear Congruential Method (LCM)
    for (int i = 0; i < SIZE - 1; i++) {
        x[i + 1] = (a * x[i] + c) % m;
    }


    printLine(50);
    cout << "| Multiplicative Congruential Random Numbers     |\n";
    cout << "| Parameters: X0=" << x0 << ", m=" << m << ", a=" << a << ", c=" << c << setw(13)<<" |\n";
    printLine(50);
    cout << "| Generated Numbers (100):"<<setw(25)<<"|\n";
    printLine(50);
    for (int i = 0; i < SIZE; i++) {
        cout << setw(5) << x[i];
        if (i % 10 == 9) cout << "\n";
        else cout << " ";
    }
    if (SIZE % 10 != 0) cout << "\n";
    printLine(50);

    return 0;
}