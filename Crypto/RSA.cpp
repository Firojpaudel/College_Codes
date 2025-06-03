#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to implement the RSA encryption and decryption algorithm

Theory:
    RSA (Rivest–Shamir–Adleman) is an asymmetric cryptographic algorithm that uses a public key (e, n)
    for encryption and a private key (d, n) for decryption. It relies on the computational difficulty
    of factoring the product of two large prime numbers. The algorithm involves selecting primes p and q,
    computing modulus n and totient phi, choosing public exponent e, and computing private exponent d.

    Parameters:
        - p, q: Two large prime numbers
        - e: Public exponent, coprime with phi(n)
        - m: Message to encrypt
        - Returns: Encrypted ciphertext and decrypted message
*/

// Function to compute GCD of two numbers using Euclidean algorithm
long long gcd(long long a, long long b) {
    while (b != 0) {
        long long temp = b;
        b = a % b;
        a = temp;
    }
    return a;
}

// Function to check if a number is prime
bool is_prime(long long n) {
    if (n <= 1) return false;
    if (n == 2) return true;
    if (n % 2 == 0) return false;
    for (long long i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Modular exponentiation: (base^exp) % mod
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

// Modular inverse using Extended Euclidean Algorithm
long long mod_inverse(long long e, long long phi) {
    long long t = 0, new_t = 1;
    long long r = phi, new_r = e;

    while (new_r != 0) {
        long long quotient = r / new_r;

        long long temp_t = t;
        t = new_t;
        new_t = temp_t - quotient * new_t;

        long long temp_r = r;
        r = new_r;
        new_r = temp_r - quotient * new_r;
    }

    if (r > 1) return -1; // no inverse exists
    if (t < 0) t += phi;

    return t;
}

// RSA algorithm
void rsa(long long p, long long q, long long e, long long m) {
    if (!is_prime(p) || !is_prime(q)) {
        cout << "Invalid: p and q must be prime\n";
        return;
    }
    if (p <= 1 || q <= 1) {
        cout << "Invalid: p and q must be greater than 1\n";
        return;
    }

    long long n = p * q;
    long long phi = (p - 1) * (q - 1);

    if (e <= 1 || e >= phi) {
        cout << "Invalid: e must satisfy 1 < e < phi(n)\n";
        return;
    }
    if (gcd(e, phi) != 1) {
        cout << "Invalid: e must be coprime with phi(n)\n";
        return;
    }
    if (m < 0 || m >= n) {
        cout << "Invalid: message m must be in range [0, n)\n";
        return;
    }

    long long d = mod_inverse(e, phi);
    if (d == -1) {
        cout << "Invalid: modular inverse for e does not exist\n";
        return;
    }

    long long c = mod_pow(m, e, n);
    long long decrypted_m = mod_pow(c, d, n);

    cout << string(30, '=') << endl;
    cout << "     RSA Encryption and Decryption\n";
    cout << string(30, '=') << endl;
    cout << "Prime p: " << p << "\n";
    cout << "Prime q: " << q << "\n";
    cout << "Modulus n: " << n << "\n";
    cout << "Totient phi(n): " << phi << "\n";
    cout << "Public exponent e: " << e << "\n";
    cout << "Private exponent d: " << d << "\n";
    cout << "Original message m: " << m << "\n";
    cout << "Encrypted ciphertext c: " << c << "\n";
    cout << "Decrypted message: " << decrypted_m << "\n";

    if (m == decrypted_m)
        cout << "Success: Decrypted message matches original\n";
    else
        cout << "Error: Decryption failed\n";
}

int main() {
    long long p, q, e, m;

    cout << string(30, '=') << endl;
    cout << "     RSA Algorithm Program\n";
    cout << string(30, '=') << endl;

    cout << "Enter first prime number (p): ";
    cin >> p;

    cout << "Enter second prime number (q): ";
    cin >> q;

    cout << "Enter public exponent (e): ";
    cin >> e;

    cout << "Enter message to encrypt (m): ";
    cin >> m;

    rsa(p, q, e, m);

    return 0;
}