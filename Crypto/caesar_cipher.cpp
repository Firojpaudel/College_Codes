#include <iostream>
#include <string>

using namespace std;

/*
Program to perform Caesar Cipher using a numeric key

Theory part:
    Encryption: c = (p + k) mod 26
    Decryption: p = (c - k) mod 26

    Where:
        - p is the position of the plaintext letter,
        - k is the shift value (numeric key),
        - c is the resulting ciphertext letter.
*/

// Encrypt function using numeric key
string caesar_encrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a'; // Determining the base character ('A' for uppercase, 'a' for lowercase)
            result += char(int(base + (c - base + shift) % 26));
        } else {
            result += c;
        }
    }
    return result;
}

// Decrypt function using numeric key
string caesar_decrypt(string text, int shift) {
    string result = "";

    for (char c : text) {
        if (isalpha(c)) {
            char base = isupper(c) ? 'A' : 'a';
            result += char(int(base + (c - base - shift + 26) % 26)); // Reversing the shift and adding 26 to avoid negative results
        } else {
            result += c; // Non-alphabetical characters remain unchanged
        }
    }
    return result;
}

int main() {
    string text;
    int shift, choice;

    cout << string(30, '=') << endl;
    cout << string(5, ' ') << "Caesar Cipher Program" << endl;
    cout << string(30, '=') << endl;

    cout << "Enter the text: ";
    cin >> text;

    cout << "Enter the shift value (numeric key): ";
    cin >> shift;

    cout << "\nChoose an option:\n1. Encrypt\n2. Decrypt\n";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = caesar_encrypt(text, shift);
        cout << "\nEncrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = caesar_decrypt(text, shift);
        cout << "\nDecrypted Text: " << decryptedText << endl;
    } else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}
