#include<iostream>
using namespace std;

// Function to perform Min-Max Sort and show the process
void minMaxSort(int arr[], int n) {
    int step = 1; // Initialize step counter
    // Traverse through half the array since we sort from both ends
    for (int i = 0; i < n/2; i++) {
        int min_idx = i, max_idx = i;
        cout << "Step " << step << ": Initial minimum: " << arr[min_idx] << ", Initial maximum: " << arr[max_idx] << endl;
        
        // Find min and max in the unsorted portion
        for (int j = i; j < n-i; j++) {
            cout << "Comparing " << arr[j] << " with current min " << arr[min_idx] << endl;
            if (arr[j] < arr[min_idx]) {
                min_idx = j;
                cout << "New minimum found: " << arr[min_idx] << endl;
            }
            cout << "Comparing " << arr[j] << " with current max " << arr[max_idx] << endl;
            if (arr[j] > arr[max_idx]) {
                max_idx = j;
                cout << "New maximum found: " << arr[max_idx] << endl;
            }
        }
        
        // Swap minimum to the left end
        if (min_idx != i) {
            int temp = arr[i];
            arr[i] = arr[min_idx];
            arr[min_idx] = temp;
            cout << "Swapped " << arr[i] << " to position " << i << endl;
        }
        
        // Adjust max_idx if it was affected by the min swap
        if (max_idx == i) max_idx = min_idx;
        
        // Swap maximum to the right end
        if (max_idx != n-1-i) {
            int temp = arr[n-1-i];
            arr[n-1-i] = arr[max_idx];
            arr[max_idx] = temp;
            cout << "Swapped " << arr[n-1-i] << " to position " << n-1-i << endl;
        }
        
        // Print array after each pass
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
    
    // Perform Min-Max Sort
    minMaxSort(arr, n);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}