#include<iostream>
using namespace std;

// Function to find modular multiplicative inverse using Extended Euclidean Algorithm
long long modInverse(long long a, long long m, int& step) {
    long long m0 = m, t, q;
    long long x0 = 0, x1 = 1;
    cout << "    Step " << step++ << ": Finding inverse of " << a << " mod " << m << endl;
    
    if (m == 1) {
        cout << "    Step " << step++ << ": Modulus is 1, inverse = 0" << endl;
        return 0;
    }
    
    while (a > 1) {
        q = a / m;
        t = m;
        m = a % m;
        a = t;
        t = x0;
        x0 = x1 - q * x0;
        x1 = t;
        cout << "      Quotient = " << q << ", a = " << a << ", m = " << m << ", x1 = " << x1 << endl;
    }
    
    if (x1 < 0)
        x1 += m0;
    cout << "    Step " << step++ << ": Inverse = " << x1 << endl;
    return x1;
}

// Function to solve system of congruences using Chinese Remainder Theorem
long long chineseRemainder(int a[], int m[], int n) {
    int step = 1;
    
    // Step 1: Compute product of all moduli
    cout << "Step " << step++ << ": Computing product of moduli" << endl;
    long long M = 1;
    for (int i = 0; i < n; i++) {
        M *= m[i];
        cout << "  Multiply by m[" << i << "] = " << m[i] << ", M = " << M << endl;
    }
    
    // Step 2: Compute partial products and their inverses
    cout << "Step " << step++ << ": Computing partial products and inverses" << endl;
    long long x = 0;
    for (int i = 0; i < n; i++) {
        long long Mi = M / m[i];
        cout << "  For i = " << i << ", M" << i << " = M / m[" << i << "] = " << Mi << endl;
        long long yi = modInverse(Mi, m[i], step);
        x += a[i] * Mi * yi;
        cout << "  Step " << step++ << ": Add a[" << i << "] * M" << i << " * y" << i 
             << " = " << a[i] << " * " << Mi << " * " << yi << " = " << a[i] * Mi * yi << ", x = " << x << endl;
    }
    
    // Step 3: Compute final result modulo M
    cout << "Step " << step++ << ": Computing final result" << endl;
    x = x % M;
    if (x < 0)
        x += M;
    cout << "  x mod M = " << x << " mod " << M << " = " << x << endl;
    
    // Step 4: Return solution
    cout << "Step " << step++ << ": Final solution" << endl;
    cout << "Solution x = " << x << " (mod " << M << ")" << endl;
    return x;
}

int main() {
    int n;
    cout << "Enter the number of congruences: ";
    cin >> n;
    int a[100], m[100];  // Arrays for remainders and moduli
    
    cout << "Enter the remainders (a[i]):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "a[" << i << "]: ";
        cin >> a[i];
    }
    cout << "Enter the moduli (m[i], must be pairwise coprime):" << endl;
    for (int i = 0; i < n; i++) {
        cout << "m[" << i << "]: ";
        cin >> m[i];
    }
    
    cout << "System of congruences:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x == " << a[i] << " (mod " << m[i] << ")" << endl;
    }
    
    // Solve using Chinese Remainder Theorem
    long long result = chineseRemainder(a, m, n);
    cout << "Result: x = " << result << endl;
    
    return 0;
}