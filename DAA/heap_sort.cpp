#include<iostream>
using namespace std;

// Function to heapify a subtree rooted at index i
void heapify(int arr[], int n, int i, int& step) {
    int largest = i;        // Initialize largest as root
    int left = 2 * i + 1;   // Left child
    int right = 2 * i + 2;  // Right child
    
    cout << "Step " << step << ": Heapifying at index " << i << ", Value = " << arr[i] << endl;
    
    // Compare with left child
    if (left < n) {
        cout << "Comparing " << arr[i] << " with left child " << arr[left] << endl;
        if (arr[left] > arr[largest]) {
            largest = left;
            cout << "Left child " << arr[left] << " is larger" << endl;
        }
    }
    
    // Compare with right child
    if (right < n) {
        cout << "Comparing " << arr[largest] << " with right child " << arr[right] << endl;
        if (arr[right] > arr[largest]) {
            largest = right;
            cout << "Right child " << arr[right] << " is larger" << endl;
        }
    }
    
    // If largest is not root
    if (largest != i) {
        swap(arr[i], arr[largest]);
        cout << "Swapped " << arr[i] << " with " << arr[largest] << endl;
        
        // Print array after swap
        cout << "Array after step " << step << ": ";
        for (int k = 0; k < n; k++)
            cout << arr[k] << " ";
        cout << endl;
        step++;
        
        // Recursively heapify the affected subtree
        heapify(arr, n, largest, step);
    } else {
        cout << "No swap needed" << endl;
        cout << "Array after step " << step << ": ";
        for (int k = 0; k < n; k++)
            cout << arr[k] << " ";
        cout << endl;
        step++;
    }
}

// Function to perform Heap Sort and show the process
void heapSort(int arr[], int n) {
    int step = 1; // Initialize step counter
    
    // Step 1: Build max-heap
    cout << "Building max-heap:" << endl;
    for (int i = n / 2 - 1; i >= 0; i--) {
        heapify(arr, n, i, step);
    }
    
    // Step 2: Extract elements from heap
    cout << "Extracting elements to sort:" << endl;
    for (int i = n - 1; i > 0; i--) {
        cout << "Step " << step << ": Moving max " << arr[0] << " to position " << i << endl;
        swap(arr[0], arr[i]);
        
        // Print array after swap
        cout << "Array after step " << step << ": ";
        for (int k = 0; k < n; k++)
            cout << arr[k] << " ";
        cout << endl;
        step++;
        
        // Heapify the reduced heap
        heapify(arr, i, 0, step);
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
    
    // Perform Heap Sort
    heapSort(arr, n);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}