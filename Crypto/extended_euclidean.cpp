#include <iostream>
#include <string>

using namespace std;

/*
Program to perform Extended Euclidean Algorithm to find GCD and Bézout's coefficients

Theory:
    The Extended Euclidean Algorithm computes the Greatest Common Divisor (GCD) of two numbers
    and determines coefficients x and y satisfying the equation: ax + by = gcd(a, b)
    
    Parameters:
        - a: First integer input
        - b: Second integer input
        - gcd: Largest integer dividing both a and b without a remainder
        - x, y: Integer coefficients for Bézout's identity
*/

// Function to compute GCD and coefficients x, y using Extended Euclidean Algorithm
int extended_euclidean(int a, int b, int& x, int& y) {
    int original_a = a;
    
    a = (a < 0) * (-a) + (a >= 0) * a;
    b = (b < 0) * (-b) + (b >= 0) * b;
    
    int is_base = (b == 0);
    x = is_base * ((original_a < 0) * (-1) + (original_a >= 0) * 1);
    y = 0;
    
    int gcd = is_base * a;
    if (is_base) return gcd;
    
    int x1, y1;
    gcd = extended_euclidean(b, a % b, x1, y1);
    
    x = y1;
    y = x1 - (a / b) * y1;
    
    return gcd;
}

int main() {
    int num1, num2;
    int x, y;

    cout << string(40, '=') << endl;
    cout << string(5, ' ') << "Extended Euclidean Algorithm Program" << endl;
    cout << string(40, '=') << endl;

    cout << "Enter the first number: ";
    cin >> num1;

    cout << "Enter the second number: ";
    cin >> num2;

    int gcd = extended_euclidean(num1, num2, x, y);
    
    cout << "\nGCD of " << num1 << " and " << num2 << " is: " << gcd << endl;
    cout << "Coefficients (x, y) for Bezout's identity (" << num1 << "x + " << num2 << "y = gcd):" << endl;
    cout << "x = " << x << ", y = " << y << endl;
    cout << "Verification: " << num1 << " * " << x << " + " << num2 << " * " << y << " = " << (num1 * x + num2 * y) << endl;

    return 0;
}