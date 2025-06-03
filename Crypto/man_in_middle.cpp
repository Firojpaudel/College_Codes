#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to demonstrate a Man-in-the-Middle (MitM) attack on Diffie-Hellman Key Exchange

Theory:
    In a Man-in-the-Middle attack on Diffie-Hellman, an attacker (Eve) intercepts the public keys
    exchanged between Alice and Bob, replacing them with her own public keys. This allows Eve to
    establish separate shared secrets with Alice and Bob, enabling her to intercept and potentially
    modify their communications while both parties believe they are communicating directly.

    Parameters:
        - p: A prime number (modulus)
        - g: A primitive root of p
        - a: Alice's private key
        - b: Bob's private key
        - e1: Eve's private key for communication with Bob
        - e2: Eve's private key for communication with Alice
        - Returns: Shared secrets computed by Alice, Bob, and Eve
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

// Function to simulate Diffie-Hellman Key Exchange with a Man-in-the-Middle attack
void diffie_hellman_mitm(long long p, long long g, long long a, long long b, long long e1, long long e2) {
    // Validate inputs
    if (p <= 1 || !is_prime(p)) {
        cout << "Invalid: p must be prime" << endl;
        return;
    }
    if (!is_primitive_root(g, p)) {
        cout << "Invalid: g must be a primitive root of p" << endl;
        return;
    }
    if (a <= 0 || b <= 0 || e1 <= 0 || e2 <= 0) {
        cout << "Invalid: private keys a, b, e1, and e2 must be positive" << endl;
        return;
    }

    // Compute Alice's public key: A = g^a mod p
    long long A = mod_pow(g, a, p);
    
    // Compute Bob's public key: B = g^b mod p
    long long B = mod_pow(g, b, p);
    
    // Compute Eve's public keys: E1 = g^e1 mod p (sent to Bob), E2 = g^e2 mod p (sent to Alice)
    long long E1 = mod_pow(g, e1, p);
    long long E2 = mod_pow(g, e2, p);
    
    // Alice computes shared secret with Eve: S1 = E2^a mod p
    long long S1 = mod_pow(E2, a, p);
    
    // Bob computes shared secret with Eve: S2 = E1^b mod p
    long long S2 = mod_pow(E1, b, p);
    
    // Eve computes shared secrets with Alice and Bob
    long long S_eve_alice = mod_pow(A, e2, p); // Same as S1
    long long S_eve_bob = mod_pow(B, e1, p);   // Same as S2
    
    // Output results
    cout << string(50, '=') << endl;
    cout << string(5, ' ') << "Diffie-Hellman with Man-in-the-Middle Attack" << endl;
    cout << string(50, '=') << endl;
    cout << "Public Prime (p): " << p << endl;
    cout << "Public Primitive Root (g): " << g << endl;
    cout << "Alice's Private Key (a): " << a << endl;
    cout << "Bob's Private Key (b): " << b << endl;
    cout << "Eve's Private Key for Bob (e1): " << e1 << endl;
    cout << "Eve's Private Key for Alice (e2): " << e2 << endl;
    cout << "Alice's Public Key (A = g^a mod p): " << A << endl;
    cout << "Bob's Public Key (B = g^b mod p): " << B << endl;
    cout << "Eve's Public Key for Bob (E1 = g^e1 mod p): " << E1 << endl;
    cout << "Eve's Public Key for Alice (E2 = g^e2 mod p): " << E2 << endl;
    cout << "Shared Secret (Alice with Eve, E2^a mod p): " << S1 << endl;
    cout << "Shared Secret (Bob with Eve, E1^b mod p): " << S2 << endl;
    cout << "Eve's Shared Secret with Alice (A^e2 mod p): " << S_eve_alice << endl;
    cout << "Eve's Shared Secret with Bob (B^e1 mod p): " << S_eve_bob << endl;
    
    // Verify that Eve's shared secrets match Alice's and Bob's
    if (S1 == S_eve_alice && S2 == S_eve_bob) {
        cout << "Success: Eve has established shared secrets with both Alice and Bob" << endl;
    } else {
        cout << "Error: Shared secrets do not match" << endl;
    }
}

int main() {
    long long p, g, a, b, e1, e2;
    
    cout << string(50, '=') << endl;
    cout << string(5, ' ') << "Diffie-Hellman Men In Middle Attack Program" << endl;
    cout << string(50, '=') << endl;
    
    cout << "Enter the prime number (p): ";
    cin >> p;
    
    cout << "Enter the primitive root (g): ";
    cin >> g;
    
    cout << "Enter Alice's private key (a): ";
    cin >> a;
    
    cout << "Enter Bob's private key (b): ";
    cin >> b;
    
    cout << "Enter Eve's private key for Bob (e1): ";
    cin >> e1;
    
    cout << "Enter Eve's private key for Alice (e2): ";
    cin >> e2;
    
    diffie_hellman_mitm(p, g, a, b, e1, e2);
    
    return 0;
}