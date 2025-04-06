#include<iostream>
using namespace std;

// Function to perform Insertion Sort and show the process
void insertionSort(int arr[], int n) {
    int step = 1; // Initialize step counter
    // Traverse through all array elements starting from the second element
    for (int i = 1; i < n; i++) {
        int key = arr[i]; // Element to insert
        int j = i - 1;    // Last index of sorted portion
        cout << "Step " << step << ": Inserting key: " << key << endl;
        
        // Shift elements that are greater than key
        while (j >= 0 && arr[j] > key) {
            cout << "Comparing " << arr[j] << " and " << key << endl;
            cout << "Shifting " << arr[j] << " to the right" << endl;
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = key; // Place key in its correct position
        
        // Print array after each insertion
        cout << "Array after step " << step << ": ";
        for (int k = 0; k < n; k++)
            cout << arr[k] << " ";
        cout << endl;
        step++; // Increment step counter
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
    
    // Perform Insertion Sort
    insertionSort(arr, n);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}