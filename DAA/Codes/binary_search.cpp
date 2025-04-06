#include<iostream>
using namespace std;

// Function to perform Binary Search and show the process
int binarySearch(int arr[], int n, int target) {
    int step = 1; // Initialize step counter
    int left = 0, right = n - 1;
    
    while (left <= right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        cout << "Step " << step << ": Search range [" << left << ", " << right << "], Mid: " << mid 
             << ", Value at mid: " << arr[mid] << endl;
        
        // Print comparison
        cout << "Comparing " << arr[mid] << " with target " << target << endl;
        
        if (arr[mid] == target) {
            cout << "Target " << target << " found at index " << mid << endl;
            return mid;
        }
        else if (arr[mid] > target) {
            cout << "Value " << arr[mid] << " is greater than target, searching left half" << endl;
            right = mid - 1;
        }
        else {
            cout << "Value " << arr[mid] << " is less than target, searching right half" << endl;
            left = mid + 1;
        }
        
        // Print array with current search range
        cout << "Array after step " << step << ": ";
        for (int i = 0; i < n; i++) {
            if (i >= left && i <= right)
                cout << arr[i] << " "; // Highlight current range
            else
                cout << "_ ";          // Indicate out-of-range elements
        }
        cout << endl;
        step++; // Increment step counter
    }
    
    cout << "Target " << target << " not found in the array" << endl;
    return -1;
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n, target;
    cout << "Enter the number of elements (array must be sorted): ";
    cin >> n;
    
    int arr[n];
    cout << "Enter the sorted elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Print the array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    cout << "Enter the target value to search: ";
    cin >> target;
    
    // Perform Binary Search
    int result = binarySearch(arr, n, target);
    
    if (result != -1)
        cout << "Final result: Target found at index " << result << endl;
    else
        cout << "Final result: Target not found" << endl;
    
    return 0;
}