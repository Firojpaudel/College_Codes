#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void printLine(int width) {
    cout << string(width, '=') << endl;
}

// Function to calculate factorial
double factorial(int n) {
    double fact = 1.0;
    for (int i = 1; i <= n; i++) {
        fact *= i;
    }
    return fact;
}

int main() {
    float lambda = 12.0; // This is the arrival rate of cars per hr 
    double pr; // Probability for each x

    // Header
    printLine(50);
    cout << "|     Poisson Distribution (lambda = " << fixed << setprecision(1) << lambda << ")        |\n";
    printLine(50);

    // Validate lambda
    if (lambda <= 0) {
        printLine(50);
        cout << "| Error: Arrival rate must be positive.          |\n";
        printLine(50);
        return 1;
    }

    // Calculate and print Poisson probabilities for x = 0 to 15
    cout << "| " << setw(5) << "x" << " | " << setw(15) << "P(X = x)" << setw(27)<< " |\n";
    printLine(50);
    for (int x = 0; x <= 15; x++) {
        pr = (exp(-lambda) * pow(lambda, x)) / factorial(x);
        cout << "| " << setw(5) << x << " | " << fixed << setprecision(6) << setw(15) << pr << setw(27)<< " |\n";
    }
    printLine(50);

    return 0;
}