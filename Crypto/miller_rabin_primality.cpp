#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>

using namespace std;

/*
Program to perform Miller-Rabin Primality Test

Theory:
    The Miller-Rabin Primality Test is a probabilistic algorithm to determine if a number is prime.
    It uses the property: if n is prime, then for a base a (1 < a < n), either a^d ≡ 1 (mod n)
    or a^(d * 2^r) ≡ -1 (mod n) for some r, where n - 1 = d * 2^s and d is odd.
    
    Parameters:
        - n: Number to test for primality
        - k: Number of iterations (higher k increases accuracy)
        - Returns: True if n is likely prime, false if composite
*/

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

// Function for Miller-Rabin primality test
bool miller_rabin_test(long long n, int k) {
    long long d = n - 1;
    int s = 0;
    
    // Handle edge cases
    if (n == 2) return true;
    if (n < 2 || n % 2 == 0) return false;
    
    // Factor n - 1 into d * 2^s, where d is odd
    while (d % 2 == 0) {
        d = d / 2;
        s = s + 1;
    }
    
    // Perform k iterations of the test
    for (int i = 0; i < k; i = i + 1) {
        long long a = 2 + rand() % (n - 3);  // Random base a in [2, n-2]
        long long x = mod_pow(a, d, n);  // Compute a^d % n
        
        if (x == 1 || x == n - 1)
            continue;
        
        bool continueLoop = false;
        for (int r = 0; r < s - 1; r = r + 1) {
            x = (x * x) % n;
            if (x == n - 1) {
                continueLoop = true;
                break;
            }
        }
        if (continueLoop)
            continue;
        return false;  // Composite
    }
    return true;  // Probably prime
}

int main() {
    long long n;
    int k;
    string result[2] = {"composite", "prime"};

    cout << string(40, '=') << endl;
    cout << string(5, ' ') << "Miller-Rabin Primality Test Program" << endl;
    cout << string(40, '=') << endl;

    cout << "Enter the number to test for primality: ";
    cin >> n;

    cout << "Enter the number of iterations (e.g., 5 for good accuracy): ";
    cin >> k;

    // Seed the random number generator
    srand(time(0));
    
    bool is_prime = miller_rabin_test(n, k);
    
    cout << "\nNumber " << n << " is: " << result[is_prime] << endl;
    cout << "Note: This is a probabilistic test; more iterations increase accuracy." << endl;

    return 0;
}