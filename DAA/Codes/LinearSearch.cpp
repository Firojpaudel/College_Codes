/*Program that performs linear search on an array*/
#include<iostream>
using namespace std;

// Function to perform linear search
int linearSearch(int arr[], int n, int target) {
    for (int i = 0; i < n; i++) {
        if (arr[i] == target)
            return i; // Return index if target is found
    }
    return -1; // Return -1 if target is not found
}

int main() {
    int n, target;
    cout << "Enter the number of elements: ";
    cin >> n;
    int arr[n];
    cout << "Enter the elements: ";
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    cout << "Enter the target value to search: ";
    cin >> target;
    int result = linearSearch(arr, n, target);
    if (result == -1) {
        cout << "Target " << target << " not found in the array." << endl;
    } else {
        cout << "Target " << target << " found at index: " << result << endl;
    }
    return 0;
}