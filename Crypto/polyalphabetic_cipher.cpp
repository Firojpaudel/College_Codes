#include <iostream>
#include <string>
#include <cctype>

using namespace std;

/*
Program to perform Polyalphabetic Cipher (Vigenère Cipher)

Theory part:
    Encryption: cᵢ = (pᵢ + kᵢ) mod 26
    Decryption: pᵢ = (cᵢ - kᵢ + 26) mod 26

    Where:
        - pᵢ is the i-th letter of plaintext
        - cᵢ is the i-th letter of ciphertext
        - kᵢ is the i-th letter of the repeated key

    Note:
        - Key is repeated to match the length of the plaintext.
        - Only alphabetical characters are encrypted; others remain unchanged.
*/

// Convert character to 0-25 range (a=0, b=1, ..., z=25)
int char_to_int(char c) {
    return tolower(c) - 'a';
}

// Extend key to match text length, ignoring non-alphabetic characters
string extend_key(const string& text, const string& key) {
    string extended = "";
    int key_len = key.length();
    int key_index = 0;

    for (char c : text) {
        if (isalpha(c)) {
            extended += key[key_index % key_len];
            key_index++;
        } else {
            extended += c; // Non-alphabetic characters are unchanged
        }
    }
    return extended;
}

// Encrypt text using Vigenère cipher
string vigenere_encrypt(const string& text, const string& key) {
    string result = "";
    string extended_key = extend_key(text, key);

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int p = text[i] - base; // Plaintext letter position (0-25)
            int k = char_to_int(extended_key[i]); // Key letter position (0-25)
            result += char(base + (p + k) % 26); // Ciphertext letter
        } else {
            result += text[i]; // Keep non-alphabetic characters
        }
    }
    return result;
}

// Decrypt text using Vigenère cipher
string vigenere_decrypt(const string& text, const string& key) {
    string result = "";
    string extended_key = extend_key(text, key);

    for (int i = 0; i < text.length(); i++) {
        if (isalpha(text[i])) {
            char base = isupper(text[i]) ? 'A' : 'a';
            int c = text[i] - base; // Ciphertext letter position (0-25)
            int k = char_to_int(extended_key[i]); // Key letter position (0-25)
            result += char(base + (c - k + 26) % 26); // Plaintext letter
        } else {
            result += text[i]; // Keep non-alphabetic characters
        }
    }
    return result;
}

int main() {
    string text, key;
    int choice;

    cout << string(30, '=') << endl;
    cout << string(7, ' ') << "Polyalphabetic Cipher" << endl;
    cout << string(30, '=') << endl;

    cout << "Enter the text: ";
    getline(cin, text); // Read full line with spaces
    
    cout << "Enter the key (text): ";
    cin >> key;

    cout << "\nChoose an option:\n1. Encrypt\n2. Decrypt\n";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = vigenere_encrypt(text, key);
        cout << "\nEncrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = vigenere_decrypt(text, key);
        cout << "\nDecrypted Text: " << decryptedText << endl;
    } else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}