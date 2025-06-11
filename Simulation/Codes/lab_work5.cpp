#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void printLine(int width) {
    cout << string(width, '=') << endl;
}

// Function to validate transition matrix (rows sum to 1)
bool isValidTransitionMatrix(float mat[2][2]) {
    const float epsilon = 1e-6; // Tolerance for floating-point comparison
    for (int i = 0; i < 2; i++) {
        float rowSum = mat[i][0] + mat[i][1];
        if (abs(rowSum - 1.0) > epsilon) {
            return false;
        }
    }
    return true;
}

int main() {
    // Initialize transition matrix and initial state vector
    float transMat[2][2] = {{0.9, 0.1}, {0.5, 0.5}}; // [sunny->sunny, sunny->rainy; rainy->sunny, rainy->rainy]
    float initialState[2] = {1.0, 0.0}; // 100% sunny, 0% rainy
    float result[2] = {0.0, 0.0}; // Result for Day 1

    // Validate transition matrix
    if (!isValidTransitionMatrix(transMat)) {
        printLine(50);
        cout << "| Error: Transition matrix rows must sum to 1. |\n";
        printLine(50);
        return 1;
    }

    // Matrix multiplication: result = initialState * transMat
    for (int j = 0; j < 2; j++) {
        for (int k = 0; k < 2; k++) {
            result[j] += initialState[k] * transMat[k][j];
        }
    }

    // Output 
    printLine(50);
    cout << "|       Markov Chain Weather Prediction          |\n";
    printLine(50);
    cout << "| Day 0 (Initial): Sunny = 100%, Rainy = 0%      |\n";
    printLine(50);
    cout << "| Day 1 Probabilities:                           |\n";
    cout << "| " << setw(12) << "Sunny" << " | " << setw(12) << fixed << setprecision(2) << result[0] * 100 << "%"<< setw(21)<< " |\n";
    cout << "| " << setw(12) << "Rainy" << " | " << setw(12) << result[1] * 100 << "%"<< setw(21)<< " |\n";
    printLine(50);

    return 0;
}