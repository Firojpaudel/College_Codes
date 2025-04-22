#include <iostream>
#include <string>
#include <cctype>
#include <vector>

using namespace std;

/*
Program to perform Playfair Cipher

Theory part:
    Encryption: Pairs of letters (digraphs) are encrypted using a 5x5 key matrix:
        - Same row: Replace each letter with the letter to its right (wrap around).
        - Same column: Replace each letter with the letter below (wrap around).
        - Rectangle: Replace each letter with the letter in its row but the other letter's column.
    Decryption: Reverse the encryption process (shift left/up instead of right/down).

    Where:
        - The key matrix is a 5x5 grid built from a keyword (划掉 duplicates removed, I/J combined).
        - Digraphs are formed from plaintext, with 'X' as a filler for identical letters or odd length.

    Note:
        - Only alphabetical characters are encrypted; others remain unchanged.
        - Filler letter 'X' is used for identical letters or odd-length text.
        - I and J are treated as the same letter in the matrix.
*/

// Generate 5x5 Playfair matrix from keyword
vector<vector<char>> generate_matrix(const string& key) {
    vector<vector<char>> matrix(5, vector<char>(5));
    vector<bool> used(26, false);
    string key_clean = "";
    
    // Process keyword: remove duplicates, convert to lowercase, combine I/J
    for (char c : key) {
        c = tolower(c);
        if (isalpha(c)) {
            if (c == 'j') c = 'i'; // Treat J as I
            if (!used[c - 'a']) {
                key_clean += c;
                used[c - 'a'] = true;
            }
        }
    }
    
    // Add remaining letters (excluding J)
    for (char c = 'a'; c <= 'z'; c++) {
        if (c == 'j') continue;
        if (!used[c - 'a']) {
            key_clean += c;
            used[c - 'a'] = true;
        }
    }
    
    // Fill 5x5 matrix
    int k = 0;
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            matrix[i][j] = key_clean[k++];
        }
    }
    
    return matrix;
}

// Find position of a letter in the matrix
pair<int, int> find_position(char c, const vector<vector<char>>& matrix) {
    c = tolower(c);
    if (c == 'j') c = 'i';
    for (int i = 0; i < 5; i++) {
        for (int j = 0; j < 5; j++) {
            if (matrix[i][j] == c) {
                return {i, j};
            }
        }
    }
    return {-1, -1}; // Should not happen
}

// Process digraphs (encrypt or decrypt)
string process_digraphs(const string& text, const vector<vector<char>>& matrix, bool encrypt) {
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
    
    // Form digraphs, adding 'X' as needed
    string digraphs = "";
    for (size_t i = 0; i < alpha_text.length(); i++) {
        digraphs += alpha_text[i];
        if (i + 1 < alpha_text.length() && alpha_text[i] == alpha_text[i + 1]) {
            digraphs += 'x'; // Add filler for identical letters
        } else if (i + 1 == alpha_text.length()) {
            digraphs += 'x'; // Add filler for odd length
        } else {
            digraphs += alpha_text[++i];
        }
    }
    
    // Process each digraph
    for (size_t i = 0; i < digraphs.length(); i += 2) {
        char a = digraphs[i], b = digraphs[i + 1];
        pair<int, int> pos1 = find_position(a, matrix);
        int r1 = pos1.first, c1 = pos1.second;
        pair<int, int> pos2 = find_position(b, matrix);
        int r2 = pos2.first, c2 = pos2.second;
        
        char c1_new, c2_new;
        if (r1 == r2) { // Same row
            int shift = encrypt ? 1 : -1;
            c1_new = matrix[r1][(c1 + shift + 5) % 5];
            c2_new = matrix[r2][(c2 + shift + 5) % 5];
        } else if (c1 == c2) { // Same column
            int shift = encrypt ? 1 : -1;
            c1_new = matrix[(r1 + shift + 5) % 5][c1];
            c2_new = matrix[(r2 + shift + 5) % 5][c2];
        } else { // Rectangle
            c1_new = matrix[r1][c2];
            c2_new = matrix[r2][c1];
        }
        
        // Add to result, preserving case
        size_t pos = result.find_first_not_of("abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ", i / 2);
        if (pos == string::npos) pos = result.length();
        result.insert(pos, 1, is_upper[i] ? toupper(c1_new) : c1_new);
        result.insert(pos + 1, 1, is_upper[i + 1] ? toupper(c2_new) : c2_new);
    }
    
    return result;
}

// Encrypt text using Playfair cipher
string playfair_encrypt(const string& text, const string& key) {
    vector<vector<char>> matrix = generate_matrix(key);
    return process_digraphs(text, matrix, true);
}

// Decrypt text using Playfair cipher
string playfair_decrypt(const string& text, const string& key) {
    vector<vector<char>> matrix = generate_matrix(key);
    return process_digraphs(text, matrix, false);
}

int main() {
    string text, key;
    int choice;

    cout << string(25, '=') << endl;
    cout << string(7, ' ') << "Playfair Cipher" << endl;
    cout << string(25, '=') << endl;

    cout << "Enter the text: ";
    getline(cin, text); // Read full line with spaces

    cout << "Enter the key (text): ";
    cin >> key;

    cout << "\nChoose an option:\n1. Encrypt\n2. Decrypt\n";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = playfair_encrypt(text, key);
        cout << "\nEncrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = playfair_decrypt(text, key);
        cout << "\nDecrypted Text: " << decryptedText << endl;
    } else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}