#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

/*
Program to perform Hill Cipher

Theory part:
    Encryption: C = (K * P) mod 26
    Decryption: P = (K⁻¹ * C) mod 26

    Where:
        - P is the plaintext vector (letter positions, 0-25)
        - C is the ciphertext vector
        - K is the key matrix (e.g., 2x2)
        - K⁻¹ is the inverse key matrix modulo 26

    Note:
        - Text is processed in blocks (e.g., pairs for a 2x2 matrix).
        - Only alphabetical characters are encrypted; others remain unchanged.
        - Padding (e.g., 'x') is added if needed.
*/

// Convert character to position (0-25) or vice versa
int char_to_int(char c) {
    return tolower(c) - 'a';
}

char int_to_char(int n, bool is_upper) {
    n = (n % 26 + 26) % 26; // Ensure n is in 0-25
    char base = is_upper ? 'A' : 'a';
    return char(base + n);
}

// Compute GCD for checking matrix invertibility
int gcd(int a, int b) {
    while (b) {
        a %= b;
        swap(a, b);
    }
    return a;
}

// Find modular multiplicative inverse of a modulo m
int mod_inverse(int a, int m) {
    a = a % m;
    for (int x = 1; x < m; x++) {
        if ((a * x) % m == 1) {
            return x;
        }
    }
    return -1; // No inverse exists
}

// Check if 2x2 key matrix is valid (invertible modulo 26)
bool is_valid_key(const vector<vector<int>>& key) {
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    det = (det + 26) % 26; // Ensure non-negative
    return gcd(det, 26) == 1; // Determinant must be coprime with 26
}

// Compute inverse of 2x2 key matrix modulo 26
vector<vector<int>> get_inverse_key(const vector<vector<int>>& key) {
    vector<vector<int>> inv(2, vector<int>(2));
    int det = (key[0][0] * key[1][1] - key[0][1] * key[1][0]) % 26;
    det = (det + 26) % 26; // Ensure non-negative
    int det_inv = mod_inverse(det, 26);

    inv[0][0] = (key[1][1] * det_inv) % 26;
    inv[0][1] = ((-key[0][1]) * det_inv) % 26;
    inv[1][0] = ((-key[1][0]) * det_inv) % 26;
    inv[1][1] = (key[0][0] * det_inv) % 26;

    // Ensure all elements are non-negative
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            inv[i][j] = (inv[i][j] + 26) % 26;
        }
    }
    return inv;
}

// Encrypt text using Hill cipher (2x2 matrix)
string hill_encrypt(const string& text, const vector<vector<int>>& key) {
    string result = "";
    string alpha_text = "";
    vector<bool> is_upper;

    // Extract alphabetic characters and track case
    for (char c : text) {
        if (isalpha(c)) {
            alpha_text += tolower(c);
            is_upper.push_back(isupper(c));
        } else {
            result += c; // Preserve non-alphabetic characters
        }
    }

    // Pad with 'x' if needed
    if (alpha_text.length() % 2 != 0) {
        alpha_text += 'x';
        is_upper.push_back(false);
    }

    // Process in pairs
    for (size_t i = 0; i < alpha_text.length(); i += 2) {
        int p1 = char_to_int(alpha_text[i]);
        int p2 = char_to_int(alpha_text[i + 1]);

        // Matrix multiplication: C = K * P mod 26
        int c1 = (key[0][0] * p1 + key[0][1] * p2) % 26;
        int c2 = (key[1][0] * p1 + key[1][1] * p2) % 26;

        // Add to result, preserving case
        size_t pos = result.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", i / 2);
        if (pos == string::npos) pos = result.length();
        result.insert(pos, 1, int_to_char(c1, is_upper[i]));
        result.insert(pos + 1, 1, int_to_char(c2, is_upper[i + 1]));
    }

    return result;
}

// Decrypt text using Hill cipher (2x2 matrix)
string hill_decrypt(const string& text, const vector<vector<int>>& key) {
    // Get inverse key
    vector<vector<int>> inv_key = get_inverse_key(key);
    return hill_encrypt(text, inv_key); // Decryption is encryption with inverse key
}

int main() {
    string text;
    vector<vector<int>> key(2, vector<int>(2));
    int choice;

    cout << string(25, '=') << endl;
    cout << string(7, ' ') << "Hill Cipher" << endl;
    cout << string(25, '=') << endl;

    cout << "Enter the text: ";
    getline(cin, text); // Read full line with spaces

    cout << "Enter the 2x2 key matrix (4 numbers, row-wise):\n";
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            cin >> key[i][j];
        }
    }

    // Validate key
    if (!is_valid_key(key)) {
        cout << "\nInvalid key! Determinant must be coprime with 26.\n";
        return 1;
    }

    cout << "\nChoose an option:\n1. Encrypt\n2. Decrypt\n";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = hill_encrypt(text, key);
        cout << "\nEncrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = hill_decrypt(text, key);
        cout << "\nDecrypted Text: " << decryptedText << endl;
    } else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}