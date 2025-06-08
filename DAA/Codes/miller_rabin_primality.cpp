#include<iostream>
#include<cstdlib>
#include<ctime>
using namespace std;

// Function for modular exponentiation (base^exp mod n)
long long modPow(long long base, long long exp, long long n) {
    long long result = 1;
    base = base % n;
    cout << "    Computing " << base << "^" << exp << " mod " << n << ": ";
    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % n;
        base = (base * base) % n;
        exp = exp / 2;
    }
    cout << result << endl;
    return result;
}

// Function for Miller-Rabin test for one base
bool millerTest(long long n, long long d, int& step) {
    // Pick a random base a from 2 to n-2
    long long a = 2 + rand() % (n - 3);
    cout << "  Testing base a = " << a << endl;
    
    // Compute a^d mod n
    long long x = modPow(a, d, n);
    cout << "    Step " << step++ << ": Initial x = a^d mod n = " << x << endl;
    
    if (x == 1 || x == n - 1)
        return true;
    
    // Repeatedly square x and check
    while (d != n - 1) {
        x = (x * x) % n;
        d *= 2;
        cout << "    Step " << step++ << ": Square x, now x = " << x << endl;
        if (x == 1)
            return false;  // Composite
        if (x == n - 1)
            return true;  // Likely prime
    }
    return false;  // Composite
}

// Function to perform Miller-Rabin Primality Test
bool millerRabin(long long n, int k) {
    int step = 1;
    
    // Step 1: Handle base cases
    cout << "Step " << step++ << ": Checking base cases" << endl;
    if (n <= 1) {
        cout << "  n <= 1, composite" << endl;
        return false;
    }
    if (n == 2 || n == 3) {
        cout << "  n = " << n << ", probably prime" << endl;
        return true;
    }
    if (n % 2 == 0) {
        cout << "  n is even and > 2, composite" << endl;
        return false;
    }
    
    // Step 2: Decompose n-1 = d * 2^s
    cout << "Step " << step++ << ": Decomposing n-1 = d * 2^s" << endl;
    long long d = n - 1;
    int s = 0;
    while (d % 2 == 0) {
        d /= 2;
        s++;
    }
    cout << "  d = " << d << ", s = " << s << endl;
    
    // Step 3: Perform k iterations
    cout << "Step " << step++ << ": Performing " << k << " iterations" << endl;
    for (int i = 1; i <= k; i++) {
        cout << "Iteration " << i << ":" << endl;
        if (!millerTest(n, d, step)) {
            cout << "Step " << step++ << ": Number is composite" << endl;
            return false;
        }
    }
    
    // Step 4: Final result
    cout << "Step " << step++ << ": Final result" << endl;
    cout << "Number " << n << " is probably prime after " << k << " iterations" << endl;
    return true;
}

int main() {
    long long n;
    int k;
    cout << "Enter the number to test (n): ";
    cin >> n;
    cout << "Enter the number of iterations (k): ";
    cin >> k;
    
    // Seed random number generator
    srand(time(0));
    
    cout << "Testing primality of " << n << " with " << k << " iterations" << endl;
    
    // Perform Miller-Rabin Primality Test
    if (millerRabin(n, k)) {
        cout << "Result: " << n << " is probably prime" << endl;
    } else {
        cout << "Result: " << n << " is composite" << endl;
    }
    
    return 0;
}