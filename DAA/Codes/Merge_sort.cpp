/*Program that performs Merge Sort on an array with detailed step-by-step output*/
#include<iostream>
using namespace std;

// Function to merge two sub-arrays and show the process
void merge(int arr[], int left, int mid, int right, int& step) {
    int n1 = mid - left + 1; // Size of left sub-array
    int n2 = right - mid;    // Size of right sub-array
    int L[n1], R[n2];        // Temporary arrays
    
    // Copy data to temporary arrays
    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];
    
    cout << "Step " << step << ": Merging sub-arrays: ";
    for (int i = 0; i < n1; i++) cout << L[i] << " ";
    cout << "and ";
    for (int j = 0; j < n2; j++) cout << R[j] << " ";
    cout << endl;
    
    int i = 0, j = 0, k = left; // Indices for L, R, and main array
    while (i < n1 && j < n2) {
        cout << "Comparing " << L[i] << " and " << R[j] << endl;
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            cout << "Adding " << L[i] << " from left sub-array" << endl;
            i++;
        } else {
            arr[k] = R[j];
            cout << "Adding " << R[j] << " from right sub-array" << endl;
            j++;
        }
        k++;
    }
    
    // Copy remaining elements of L[] if any
    while (i < n1) {
        arr[k] = L[i];
        cout << "Adding remaining " << L[i] << " from left sub-array" << endl;
        i++;
        k++;
    }
    
    // Copy remaining elements of R[] if any
    while (j < n2) {
        arr[k] = R[j];
        cout << "Adding remaining " << R[j] << " from right sub-array" << endl;
        j++;
        k++;
    }
    
    // Print array after merging
    cout << "Array after step " << step << ": ";
    for (int x = left; x <= right; x++)
        cout << arr[x] << " ";
    cout << endl;
    step++; // Increment step counter
}

// Function to perform Merge Sort and show the process
void mergeSort(int arr[], int left, int right, int& step) {
    if (left < right) {
        int mid = left + (right - left) / 2; // Avoid overflow
        mergeSort(arr, left, mid, step);
        mergeSort(arr, mid + 1, right, step);
        merge(arr, left, mid, right, step);
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
    
    // Perform Merge Sort
    int step = 1; // Initialize step counter
    mergeSort(arr, 0, n-1, step);
    
    // Print sorted array
    cout << "Sorted array: ";
    printArray(arr, n);
    
    return 0;
}