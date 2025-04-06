/*Program that calculates the GCD of given N numbers*/
#include<iostream>
using namespace std;

// Function to calculate GCD of two numbers
int gcd(int a, int b) {
    if (b == 0)
        return a;
    return gcd(b, a % b);
}

// Function to calculate GCD of an array of numbers
int findGCD(int arr[], int n) {
    int result = arr[0];
    for (int i = 1; i < n; i++) {
        result = gcd(result, arr[i]);
        if(result == 1) {
           return 1;
        }
    }
    return result;
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
    cout << "GCD of the given numbers is: " << findGCD(arr, n) << endl;
    return 0;
}