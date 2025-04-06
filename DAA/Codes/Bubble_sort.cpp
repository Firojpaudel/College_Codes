#include<iostream>
using namespace std;

// Function to perform bubble sort and show the process
void bubbleSort(int arr[], int n) {
    int step = 1; // Initialize step counter
    // Traverse through all array elements
    for (int i = 0; i < n-1; i++) {
        // Last i elements are already in place
        for (int j = 0; j < n-i-1; j++) {
            // Print the elements being compared
            cout << "Comparing " << arr[j] << " and " << arr[j+1] << endl;
            // Swap if the element found is greater than the next element
            if (arr[j] > arr[j+1]) {
                int temp = arr[j];
                arr[j] = arr[j+1];
                arr[j+1] = temp;
            }
            // Print array after each swap
            cout << "Step " << step << ": ";
            for (int k = 0; k < n; k++)
                cout << arr[k] << " ";
            cout << endl;
            step++; // Increment step counter
        }
    }
}

// Function to print an array
void printArray(int arr[], int size) {
    for (int i = 0; i < size; i++)
        cout << arr[i] << " ";
    cout << endl;
}

int main() {
    int n;
    cout << "Enter the number of elements: ";
    cin >> n;
    
    int arr[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    // Print unsorted array
    cout << "Unsorted array: ";
    printArray(arr, n);
    
    // Perform bubble sort
    bubbleSort(arr, n);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}