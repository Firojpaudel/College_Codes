#include<iostream>
#include<algorithm> // For sort
using namespace std;

// Structure to represent an item
struct Item {
    int value, weight;
    double ratio; // Value-to-weight ratio
};

// Function to compare items by ratio for sorting
bool compare(Item a, Item b) {
    return a.ratio > b.ratio; // Descending order
}

// Function to solve Fractional Knapsack and show the process
double fractionalKnapsack(Item arr[], int n, int capacity) {
    int step = 1; // Initialize step counter
    double total_value = 0.0;
    int current_weight = 0;
    
    // Step 1: Compute value-to-weight ratios
    cout << "Step " << step << ": Computing value-to-weight ratios" << endl;
    for (int i = 0; i < n; i++) {
        arr[i].ratio = (double)arr[i].value / arr[i].weight;
        cout << "Item " << i << ": Value = " << arr[i].value << ", Weight = " << arr[i].weight 
             << ", Ratio = " << arr[i].ratio << endl;
    }
    step++;
    
    // Step 2: Sort items by ratio
    cout << "Step " << step << ": Sorting items by ratio (descending)" << endl;
    sort(arr, arr + n, compare);
    for (int i = 0; i < n; i++) {
        cout << "Item " << i << ": Value = " << arr[i].value << ", Weight = " << arr[i].weight 
             << ", Ratio = " << arr[i].ratio << endl;
    }
    step++;
    
    // Step 3: Fill the knapsack
    cout << "Step " << step << ": Filling knapsack (capacity = " << capacity << ")" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Considering item " << i << ": Value = " << arr[i].value << ", Weight = " << arr[i].weight 
             << ", Ratio = " << arr[i].ratio << endl;
        cout << "Current weight = " << current_weight << ", Remaining capacity = " << capacity - current_weight << endl;
        
        if (current_weight + arr[i].weight <= capacity) {
            current_weight += arr[i].weight;
            total_value += arr[i].value;
            cout << "Fully adding item: Value = " << arr[i].value << ", Weight = " << arr[i].weight << endl;
        } else {
            double fraction = (double)(capacity - current_weight) / arr[i].weight;
            total_value += arr[i].value * fraction;
            current_weight = capacity; // Knapsack is full
            cout << "Adding fraction " << fraction << " of item: Value = " << arr[i].value * fraction 
                 << ", Weight = " << capacity - current_weight + arr[i].weight * fraction << endl;
            break; // No more capacity
        }
        
        cout << "Knapsack after step " << step << ": Total Value = " << total_value 
             << ", Total Weight = " << current_weight << endl;
        step++;
    }
    
    return total_value;
}

int main() {
    int n, capacity;
    cout << "Enter the number of items: ";
    cin >> n;
    
    Item arr[n];
    cout << "Enter value and weight for each item:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Item " << i << " - Value: ";
        cin >> arr[i].value;
        cout << "Item " << i << " - Weight: ";
        cin >> arr[i].weight;
    }
    
    cout << "Enter the knapsack capacity: ";
    cin >> capacity;
    
    // Perform Fractional Knapsack
    double max_value = fractionalKnapsack(arr, n, capacity);
    
    // Print final result
    cout << "Maximum value achievable: " << max_value << endl;
    
    return 0;
}