#include<iostream>
using namespace std;

// Function to partition the array and show the process
int partition(int arr[], int low, int high, int& step) {
    int pivot = arr[high]; // Choose last element as pivot
    int i = low - 1;       // Index of smaller element
    for (int j = low; j < high; j++) {
        // Print the elements being compared
        cout << "Comparing " << arr[j] << " and " << pivot << endl;
        if (arr[j] <= pivot) {
            i++;
            int temp = arr[i];
            arr[i] = arr[j];
            arr[j] = temp;
        }
        // Print array after each comparison
        cout << "Step " << step << ": ";
        for (int k = low; k <= high; k++)
            cout << arr[k] << " ";
        cout << endl;
        step++; // Increment step counter
    }
    int temp = arr[i + 1];
    arr[i + 1] = arr[high];
    arr[high] = temp;
    // Print array after placing pivot
    cout << "Step " << step << " (Pivot " << pivot << " placed): ";
    for (int k = low; k <= high; k++)
        cout << arr[k] << " ";
    cout << endl;
    step++;
    return i + 1;
}

// Function to perform Quick Sort and show the process
void quickSort(int arr[], int low, int high, int& step) {
    if (low < high) {
        int pi = partition(arr, low, high, step);
        quickSort(arr, low, pi - 1, step);
        quickSort(arr, pi + 1, high, step);
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
    
    // Perform Quick Sort
    int step = 1; // Initialize step counter
    quickSort(arr, 0, n-1, step);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}