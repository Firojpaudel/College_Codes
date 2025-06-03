#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to implement the ElGamal cryptographic system

Theory:
    ElGamal is an asymmetric encryption algorithm based on the Diffie-Hellman key exchange.
    It uses a public key (p, g, h) for encryption and a private key a for decryption. The security
    relies on the difficulty of the discrete logarithm problem. A prime p and primitive root g are
    chosen, and the public key h is computed as g^a mod p. Encryption produces a ciphertext pair
    (c1, c2), and decryption recovers the original message.

    Parameters:
        - p: A large prime number
        - g: A primitive root modulo p
        - a: Private key (1 <= a <= p-2)
        - m: Message to encrypt (0 <= m < p)
        - k: Random integer for encryption (1 <= k <= p-2)
        - Returns: Ciphertext (c1, c2) and decrypted message
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

// Function to check if g is a primitive root modulo p
bool is_primitive_root(long long g, long long p) {
    if (p <= 1 || !is_prime(p)) return false;
    if (gcd(g, p) != 1) return false;
    long long phi = p - 1;
    for (long long i = 1; i < phi; i++) {
        if (mod_pow(g, i, p) == 1) return false;
    }
    return mod_pow(g, phi, p) == 1;
}

// Function to compute modular multiplicative inverse using Extended Euclidean Algorithm
long long mod_inverse(long long a, long long m) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    if (m == 1) return 0;
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
    }
    if (x1 < 0) x1 += m0;
    return x1;
}

// Function to perform ElGamal encryption and decryption
void elgamal(long long p, long long g, long long a, long long m, long long k) {
    // Validate inputs
    if (!is_prime(p)) {
        cout << "Invalid: p must be prime\n";
        return;
    }
    if (!is_primitive_root(g, p)) {
        cout << "Invalid: g must be a primitive root of p\n";
        return;
    }
    if (a < 1 || a > p - 2) {
        cout << "Invalid: private key a must be in range [1, p-2]\n";
        return;
    }
    if (m < 0 || m >= p) {
        cout << "Invalid: message m must be in range [0, p)\n";
        return;
    }
    if (k < 1 || k > p - 2) {
        cout << "Invalid: random k must be in range [1, p-2]\n";
        return;
    }

    // Compute public key h = g^a mod p
    long long h = mod_pow(g, a, p);

    // Encryption: c1 = g^k mod p, c2 = m * h^k mod p
    long long c1 = mod_pow(g, k, p);
    long long h_k = mod_pow(h, k, p);
    long long c2 = (m * h_k) % p;

    // Decryption: s = c1^a mod p, m' = c2 * s^(-1) mod p
    long long s = mod_pow(c1, a, p);
    long long s_inv = mod_inverse(s, p);
    if (s_inv == -1) {
        cout << "Invalid: modular inverse for s does not exist\n";
        return;
    }
    long long decrypted_m = (c2 * s_inv) % p;

    // Output results
    cout << string(40, '=') << endl;
    cout << "     ElGamal Encryption and Decryption\n";
    cout << string(40, '=') << endl;
    cout << "Prime p: " << p << "\n";
    cout << "Primitive root g: " << g << "\n";
    cout << "Private key a: " << a << "\n";
    cout << "Public key h (g^a mod p): " << h << "\n";
    cout << "Random k: " << k << "\n";
    cout << "Original message m: " << m << "\n";
    cout << "Ciphertext (c1, c2): (" << c1 << ", " << c2 << ")\n";
    cout << "Decrypted message: " << decrypted_m << "\n";

    // Verify decryption
    if (decrypted_m == m) {
        cout << "Success: Decrypted message matches original\n";
    } else {
        cout << "Error: Decryption failed\n";
    }
}

int main() {
    long long p, g, a, m, k;

    cout << string(40, '=') << endl;
    cout << "     ElGamal Cryptographic System\n";
    cout << string(40, '=') << endl;

    cout << "Enter prime number (p): ";
    cin >> p;

    cout << "Enter primitive root (g): ";
    cin >> g;

    cout << "Enter private key (a): ";
    cin >> a;

    cout << "Enter message to encrypt (m): ";
    cin >> m;

    cout << "Enter random integer (k): ";
    cin >> k;

    elgamal(p, g, a, m, k);

    return 0;
}