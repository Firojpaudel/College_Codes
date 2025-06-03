#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to implement the Diffie-Hellman Key Exchange algorithm

Theory:
    The Diffie-Hellman Key Exchange allows two parties (Alice and Bob) to establish a shared
    secret key over an insecure channel. It uses a public prime number p and a primitive root g.
    Each party selects a private key, computes a public key, and exchanges public keys. The shared
    secret is computed using the received public key and their own private key, relying on the
    difficulty of the discrete logarithm problem.

    Parameters:
        - p: A prime number (modulus)
        - g: A primitive root of p
        - a: Alice's private key
        - b: Bob's private key
        - Returns: Shared secret key computed by both parties
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

// Function to check if 'g' is a primitive root of prime 'p'
bool is_primitive_root(long long g, long long p) {
    if (p <= 1 || !is_prime(p)) return false;
    if (gcd(g, p) != 1) return false;
    
    // For g to be a primitive root, g^i mod p != 1 for i = 1 to p-2,
    // and g^(p-1) mod p = 1
    for (long long i = 1; i < p - 1; i = i + 1) {
        if (mod_pow(g, i, p) == 1) return false;
    }
    return mod_pow(g, p - 1, p) == 1;
}

// Function to perform Diffie-Hellman Key Exchange
void diffie_hellman(long long p, long long g, long long a, long long b) {
    // Validate inputs
    if (p <= 1 || !is_prime(p)) {
        cout << "Invalid: p must be prime" << endl;
        return;
    }
    if (!is_primitive_root(g, p)) {
        cout << "Invalid: g must be a primitive root of p" << endl;
        return;
    }
    if (a <= 0 || b <= 0) {
        cout << "Invalid: private keys a and b must be positive" << endl;
        return;
    }

    // Compute Alice's public key: A = g^a mod p
    long long A = mod_pow(g, a, p);
    
    // Compute Bob's public key: B = g^b mod p
    long long B = mod_pow(g, b, p);
    
    // Compute shared secret for Alice: S = B^a mod p
    long long S_alice = mod_pow(B, a, p);
    
    // Compute shared secret for Bob: S = A^b mod p
    long long S_bob = mod_pow(A, b, p);
    
    // Output results
    cout << string(40, '=') << endl;
    cout << string(5, ' ') << "Diffie-Hellman Key Exchange" << endl;
    cout << string(40, '=') << endl;
    cout << "Public Prime (p): " << p << endl;
    cout << "Public Primitive Root (g): " << g << endl;
    cout << "Alice's Private Key (a): " << a << endl;
    cout << "Bob's Private Key (b): " << b << endl;
    cout << "Alice's Public Key (A = g^a mod p): " << A << endl;
    cout << "Bob's Public Key (B = g^b mod p): " << B << endl;
    cout << "Shared Secret (Alice, B^a mod p): " << S_alice << endl;
    cout << "Shared Secret (Bob, A^b mod p): " << S_bob << endl;
    
    // Verify that both shared secrets match
    if (S_alice == S_bob) {
        cout << "Success: Shared secret key is " << S_alice << endl;
    } else {
        cout << "Error: Shared secrets do not match" << endl;
    }
}

int main() {
    long long p, g, a, b;
    
    cout << string(45, '=') << endl;
    cout << string(5, ' ') << "Diffie-Hellman Key Exchange Program" << endl;
    cout << string(45, '=') << endl;
    
    cout << "Enter the prime number (p): ";
    cin >> p;
    
    cout << "Enter the primitive root (g): ";
    cin >> g;
    
    cout << "Enter Alice's private key (a): ";
    cin >> a;
    
    cout << "Enter Bob's private key (b): ";
    cin >> b;
    
    diffie_hellman(p, g, a, b);
    
    return 0;
}