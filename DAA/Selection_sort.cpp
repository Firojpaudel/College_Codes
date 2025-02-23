#include<iostream>
using namespace std;

// Function to perform selection sort and show the process
void selectionSort(int arr[], int n) {
    int step = 1; 
    // Traverse through all array elements
    for (int i = 0; i < n-1; i++) {
        // Find the minimum element in unsorted array
        int min_idx = i;
        cout << "Step " << step << ": Initial minimum: " << arr[min_idx] << endl;
        for (int j = i+1; j < n; j++) {
            // Print the elements being compared
            cout << "Comparing " << arr[min_idx] << " and " << arr[j] << endl;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
                cout << "New minimum found: " << arr[min_idx] << endl;
            }
        }
        // Swap the found minimum element with the first element
        int temp = arr[min_idx];
        arr[min_idx] = arr[i];
        arr[i] = temp;

        // Print array after each swap
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
    
    // Perform selection sort
    selectionSort(arr, n);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}