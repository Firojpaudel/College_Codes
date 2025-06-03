#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to compute the discrete logarithm of a number

Theory:
    For a primitive root 'a' of a prime number 'p', and an integer 'b', the discrete
    logarithm is the unique exponent 'i' such that b ≡ a^i mod p. This exponent 'i'
    is denoted as dlog_{a,p}(b) = i, where 0 ≤ i < p.
    
    Parameters:
        - a: Base, a primitive root of prime p
        - b: Number to find the discrete logarithm for
        - p: A prime number (modulus)
        - Returns: The discrete logarithm i, or -1 if not found or inputs are invalid
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

// Function to check if a number is prime
bool is_prime(long long n) {
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i = i + 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Function to check if 'a' is a primitive root of prime 'p'
bool is_primitive_root(long long a, long long p) {
    if (p <= 1 || !is_prime(p)) return false;
    if (gcd(a, p) != 1) return false;
    
    // For a to be a primitive root, a^i mod p != 1 for i = 1 to p-2,
    // and a^(p-1) mod p = 1
    for (long long i = 1; i < p - 1; i = i + 1) {
        if (mod_pow(a, i, p) == 1) return false;
    }
    return mod_pow(a, p - 1, p) == 1;
}

// Function to compute the discrete logarithm dlog_{a,p}(b)
long long discrete_log(long long a, long long b, long long p) {
    // Handle edge cases
    if (p <= 1 || !is_prime(p)) return -1;  // p must be prime
    if (a <= 0 || b <= 0) return -1;  // a and b must be positive
    if (!is_primitive_root(a, p)) return -2;  // a must be a primitive root
    if (b % p == 0) return -1;  // b must not be congruent to 0 mod p
    
    // Brute force: try i from 0 to p-1 to find a^i mod p = b
    for (long long i = 0; i < p; i = i + 1) {
        if (mod_pow(a, i, p) == b % p) {
            return i;
        }
    }
    return -1;  // No solution found (unexpected for valid inputs)
}

int main() {
    long long a, b, p;
    string result[3] = {"invalid: p must be prime, a and b must be positive",
                        "invalid: a must be a primitive root of p",
                        "computed discrete logarithm"};

    cout << string(30, '=') << endl;
    cout << string(5, ' ') << "Discrete Logarithm Calculator Program" << endl;
    cout << string(30, '=') << endl;

    cout << "Enter the base (a, a primitive root): ";
    cin >> a;

    cout << "Enter the number (b): ";
    cin >> b;

    cout << "Enter the prime modulus (p): ";
    cin >> p;

    long long log_value = discrete_log(a, b, p);
    int index = 2;  // Default: valid result
    index = (log_value == -1) * 0 + (log_value != -1) * index;
    index = (log_value == -2) * 1 + (log_value != -2) * index;
    
    cout << "\nResult for a = " << a << ", b = " << b << ", p = " << p << ": ";
    cout << result[index] << endl;
    if (log_value >= 0) {
        cout << "dlog_" << a << "," << p << "(" << b << ") = " << log_value << endl;
        cout << "Verification: " << a << "^" << log_value << " mod " << p << " = " << mod_pow(a, log_value, p) << endl;
    }
    cout << "Note: b = a^i mod p, where i is the discrete logarithm." << endl;

    return 0;
}