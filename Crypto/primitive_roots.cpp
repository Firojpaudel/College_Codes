#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to find primitive roots of a prime number

Theory:
    An integer 'a' is a primitive root of a prime number 'p' if the powers
    a^1 mod p, a^2 mod p, ..., a^(p-1) mod p are all distinct and include all
    integers from 1 to p-1 in some order. This means the order of 'a' modulo p
    (the smallest positive k such that a^k ≡ 1 (mod p)) must be p-1.
    
    Parameters:
        - p: A prime number
        - Returns: Lists all primitive roots of p, or indicates if none exist
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

// Function to find primitive roots of a prime number p
void find_primitive_roots(long long p) {
    // Handle edge cases
    if (p <= 1) {
        cout << "Input must be a positive integer greater than 1." << endl;
        return;
    }
    if (!is_prime(p)) {
        cout << "Input " << p << " is not prime. Primitive roots exist only for prime numbers." << endl;
        return;
    }
    if (p == 2) {
        cout << "Primitive root of 2: 1" << endl;
        return;
    }
    
    // For a prime p, a is a primitive root if a^i mod p != 1 for i = 1 to p-2,
    // and a^(p-1) mod p = 1
    int found = 0;
    cout << "Primitive roots of " << p << ":" << endl;
    for (long long a = 1; a < p; a = a + 1) {
        int is_primitive = 1;
        for (long long i = 1; i < p - 1; i = i + 1) {
            if (mod_pow(a, i, p) == 1) {
                is_primitive = 0;
                break;
            }
        }
        if (is_primitive && mod_pow(a, p - 1, p) == 1) {
            cout << a << " ";
            found = found + 1;
        }
    }
    if (found == 0) {
        cout << "None found (unexpected for a prime number)." << endl;
    } else {
        cout << endl << "Total primitive roots: " << found << endl;
    }
}

int main() {
    long long p;

    cout << string(40, '=') << endl;
    cout << string(5, ' ') << "Primitive Roots Finder Program" << endl;
    cout << string(40, '=') << endl;

    cout << "Enter a prime number (p): ";
    cin >> p;

    find_primitive_roots(p);
    
    cout << "Note: A number a is a primitive root of p if a^1, a^2, ..., a^(p-1) mod p are distinct." << endl;

    return 0;
}