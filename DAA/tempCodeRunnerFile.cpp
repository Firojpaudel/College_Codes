/*Program that calculates the nth Fibonacci number*/
#include<iostream>
using namespace std;

// Function to calculate the nth Fibonacci number
int fibonacci(int n) {
    if (n == 0)
        return 0;
    if (n == 1)
        return 1;
    int a = 0, b = 1, c;
    for (int i = 2; i <= n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return b;
}

int main() {
    int n;
    cout << "Enter a non-negative number: ";
    cin >> n;
    if (n < 0) {
        cout << "Fibonacci is not defined for negative numbers." << endl;
    } else {
        cout << "The " << n << "th Fibonacci number is: " << fibonacci(n) << endl;
    }
    return 0;
}