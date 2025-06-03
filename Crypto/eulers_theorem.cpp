#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to demonstrate Euler's Theorem

Theory:
    Euler's Theorem states that if a and n are coprime (i.e., gcd(a, n) = 1),
    then a^phi(n) ≡ 1 (mod n), where phi(n) is Euler's totient function, the count
    of integers from 1 to n that are coprime with n.
    
    Parameters:
        - a: Base number
        - n: Modulus, a positive integer
        - phi(n): Euler's totient function, number of integers from 1 to n coprime with n
        - Returns: Computed result of a^phi(n) mod n to verify the theorem
*/

// Function to compute GCD of two numbers using Euclidean algorithm
int gcd(int a, int b) {
    while (b > 0) {
        a = a % b;
        a = a + b;
        b = a - b;
        a = a - b;
    }
    return a;
}

// Function to compute Euler's totient function phi(n)
int euler_totient(int n) {
    int result = n;
    for (int i = 2; i * i <= n; i = i + 1) {
        if (n % i == 0) {
            while (n % i == 0) {
                n = n / i;
            }
            result = result - result / i;
        }
    }
    if (n > 1) {
        result = result - result / n;
    }
    return result;
}

// Function for modular exponentiation: computes (base^exp) % mod
long long mod_pow(long long base, long long exp, long long mod) {
    long long result = 1;
    base = base % mod;
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;
        base = (base * base) % mod;
        exp = exp / 2;
    }
    return result;
}

// Function to demonstrate Euler's Theorem
long long euler_theorem(int a, int n) {
    // Handle edge cases
    if (n <= 0) return -1;  // Invalid modulus
    if (a <= 0) return -2;  // Invalid base
    if (gcd(a, n) != 1) return -3;  // a and n not coprime
    
    // Compute phi(n)
    int phi = euler_totient(n);
    
    // Compute a^phi(n) mod n
    return mod_pow(a, phi, n);
}

int main() {
    int a, n;
    string result[4] = {"invalid: modulus must be positive", 
                        "invalid: base must be positive", 
                        "invalid: a and n must be coprime", 
                        "1 (Euler's Theorem holds)"};

    cout << string(45, '=') << endl;
    cout << string(5, ' ') << "Euler's Theorem Demonstration Program" << endl;
    cout << string(45, '=') << endl;

    cout << "Enter the base (a): ";
    cin >> a;

    cout << "Enter the modulus (n): ";
    cin >> n;

    long long computation = euler_theorem(a, n);
    int index = 3;  // Default: theorem holds
    index = (computation == -1) * 0 + (computation != -1) * index;
    index = (computation == -2) * 1 + (computation != -2) * index;
    index = (computation == -3) * 2 + (computation != -3) * index;
    
    cout << "\nResult for a = " << a << ", n = " << n << ": ";
    cout << result[index] << endl;
    if (computation >= 0) {
        cout << "Computed value: " << a << "^phi(" << n << ") mod " << n << " = " << computation << endl;
    }
    cout << "Note: Euler's Theorem applies only if a and n are coprime." << endl;

    return 0;
}