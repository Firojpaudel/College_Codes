#include <iostream>
#include <string>

using namespace std;

/*
Program to perform Euclidean Algorithm to find GCD of two numbers

Theory part:
    The Euclidean Algorithm finds the Greatest Common Divisor (GCD) of two numbers
    using the principle: GCD(a, b) = GCD(b, a % b) until the remainder is 0.
    
    Where:
        - a is the first number,
        - b is the second number,
        - GCD is the largest number that divides both a and b without a remainder.
*/

// Function to calculate GCD using Euclidean Algorithm
int euclidean_gcd(int a, int b) {
    // Ensure positive numbers
    if (a < 0) a = -a;
    if (b < 0) b = -b;
    
    // Base case: when one number is 0, the other is the GCD
    if (b == 0) {
        return a;
    }
    
    // Recursive call: GCD(a, b) = GCD(b, a % b)
    return euclidean_gcd(b, a % b);
}

int main() {
    int num1, num2;

    cout << string(36, '=') << endl;
    cout << string(5, ' ') << "Euclidean Algorithm Program" << endl;
    cout << string(36, '=') << endl;

    cout << "Enter the first number: ";
    cin >> num1;

    cout << "Enter the second number: ";
    cin >> num2;

    // Calculate GCD
    int gcd = euclidean_gcd(num1, num2);
    
    cout << "\nGCD of " << num1 << " and " << num2 << " is: " << gcd << endl;

    return 0;
}