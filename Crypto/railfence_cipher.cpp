#include <iostream>
#include <string>
#include <vector>
#include <iomanip>

using namespace std;

/*
Program to perform Rail Fence Cipher

Theory part:
    Encryption: Text is written in a zigzag pattern across a fixed number of rails (rows),
                then read row by row to form the ciphertext.
    Decryption: Reconstruct the zigzag pattern and read column by column to recover the plaintext.

    Where:
        - The number of rails (key) determines the depth of the zigzag pattern.
        - The pattern repeats every 2 * (rails - 1) positions.

    Note:
        - All characters (including spaces and punctuation) are processed to preserve text structure.
        - Case is preserved in the output.
        - A minimum of 2 rails is required for meaningful encryption.
*/

// Print the fence (grid) showing character placement
void print_fence(const vector<string>& fence, const string& label) {
    cout << "\n" << label << ":\n";
    for (size_t i = 0; i < fence.size(); i++) {
        cout << "Rail " << i + 1 << ": ";
        for (char c : fence[i]) {
            cout << (c == ' ' ? "  " : string(1, c) + " ") << ' ';
        }
        cout << endl;
    }
    cout << endl;
}

// Print visually appealing zigzag pattern
void print_zigzag(const vector<string>& fence, int rails, int len) {
    cout << "\nZigzag Pattern:\n";
    vector<vector<char>> visual(rails * 2 - 1, vector<char>(len * 2, ' '));
    vector<pair<int, int>> positions;
    int pos = 0, row = 0, dir = 1;
    
    // Place characters and track positions
    for (int i = 0; i < len; i++) {
        visual[row * 2][pos * 2] = fence[row][pos];
        positions.push_back({row * 2, pos * 2});
        pos++;
        row += dir;
        if (row == rails - 1 || row == 0) dir = -dir;
    }
    
    // Add diagonal connections
    for (size_t i = 0; i < positions.size() - 1; i++) {
        int r1 = positions[i].first, p1 = positions[i].second;
        int r2 = positions[i + 1].first, p2 = positions[i + 1].second;
        if (r2 > r1) {
            visual[r1 + 1][p1 + 1] = '\\';
        } else if (r2 < r1) {
            visual[r1 - 1][p1 + 1] = '/';
        }
    }
    
    // Print the pattern
    for (int r = 0; r < rails * 2 - 1; r++) {
        if (r % 2 == 0) {
            cout << "Rail " << (r / 2 + 1) << ": ";
        } else {
            cout << "       ";
        }
        for (int p = 0; p < len * 2; p++) {
            cout << visual[r][p];
        }
        cout << endl;
    }
    cout << endl;
}

// Encrypt text using Rail Fence cipher
string rail_fence_encrypt(const string& text, int rails) {
    if (rails < 2 || text.empty()) return text; // No encryption for 1 rail or empty text
    vector<string> fence(rails, string(text.length(), ' '));
    int pos = 0;
    int row = 0;
    int dir = 1; // 1 for down, -1 for up
    
    // Fill the fence in zigzag pattern
    for (char c : text) {
        fence[row][pos] = c;
        pos++;
        row += dir;
        if (row == rails - 1 || row == 0) dir = -dir; // Change direction at top/bottom
    }
    
    // Print fence and zigzag pattern
    print_fence(fence, "Encryption Fence");
    print_zigzag(fence, rails, text.length());
    
    // Read off by rails
    string result = "";
    for (const auto& rail : fence) {
        for (char c : rail) {
            if (c != ' ') result += c;
        }
    }
    return result;
}

// Decrypt text using Rail Fence cipher
string rail_fence_decrypt(const string& text, int rails) {
    if (rails < 2 || text.empty()) return text; // No decryption for 1 rail or empty text
    int len = text.length();
    
    // Calculate positions in the zigzag pattern
    vector<vector<int>> positions(rails);
    int pos = 0;
    int row = 0;
    int dir = 1;
    for (int i = 0; i < len; i++) {
        positions[row].push_back(i);
        pos++;
        row += dir;
        if (row == rails - 1 || row == 0) dir = -dir;
    }
    
    // Create fence for decryption
    vector<string> fence(rails, string(len, ' '));
    int text_index = 0;
    for (int r = 0; r < rails && text_index < len; r++) {
        for (int p : positions[r]) {
            if (text_index < len) {
                fence[r][p] = text[text_index++];
            }
        }
    }
    
    // Print fence and zigzag pattern
    print_fence(fence, "Decryption Fence");
    print_zigzag(fence, rails, len);
    
    // Read column by column
    string result(len, ' ');
    pos = 0;
    row = 0;
    dir = 1;
    for (int i = 0; i < len; i++) {
        if (fence[row][pos] != ' ') {
            result[i] = fence[row][pos];
        }
        pos++;
        row += dir;
        if (row == rails - 1 || row == 0) dir = -dir;
    }
    
    return result;
}

int main() {
    string text;
    int rails, choice;

    cout << string(25, '=') << endl;
    cout << string(7, ' ') << "Rail Fence Cipher" << endl;
    cout << string(25, '=') << endl;

    cout << "Enter the text: ";
    getline(cin, text); // Read full line with spaces

    cout << "Enter the number of rails: ";
    cin >> rails;

    // Validate rails
    if (rails < 1) {
        cout << "\nInvalid number of rails! Must be at least 1.\n";
        return 1;
    }

    cout << "\nChoose an option:\n1. Encrypt\n2. Decrypt\n";
    cin >> choice;

    if (choice == 1) {
        string encryptedText = rail_fence_encrypt(text, rails);
        cout << "\nEncrypted Text: " << encryptedText << endl;
    } else if (choice == 2) {
        string decryptedText = rail_fence_decrypt(text, rails);
        cout << "\nDecrypted Text: " << decryptedText << endl;
    } else {
        cout << "\nInvalid choice!" << endl;
    }

    return 0;
}