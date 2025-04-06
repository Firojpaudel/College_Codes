#include<iostream>
#include<algorithm> // For sort
using namespace std;

// Structure to represent a job
struct Job {
    int id, profit, deadline;
};

// Function to compare jobs by profit for sorting
bool compare(Job a, Job b) {
    return a.profit > b.profit; // Descending order
}

// Function to solve Job Sequencing and show the process
void jobSequencing(Job arr[], int n) {
    int step = 1; // Initialize step counter
    int total_profit = 0;
    
    // Step 1: Sort jobs by profit
    cout << "Step " << step << ": Sorting jobs by profit (descending)" << endl;
    sort(arr, arr + n, compare);
    for (int i = 0; i < n; i++) {
        cout << "Job " << arr[i].id << ": Profit = " << arr[i].profit 
             << ", Deadline = " << arr[i].deadline << endl;
    }
    step++;
    
    // Step 2: Find maximum deadline
    int max_deadline = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i].deadline > max_deadline)
            max_deadline = arr[i].deadline;
    }
    cout << "Step " << step << ": Maximum deadline = " << max_deadline << endl;
    step++;
    
    // Step 3: Initialize slots
    int slots[max_deadline];
    for (int i = 0; i < max_deadline; i++)
        slots[i] = -1; // -1 indicates empty slot
    
    // Step 4: Schedule jobs
    cout << "Step " << step << ": Scheduling jobs" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Considering Job " << arr[i].id << ": Profit = " << arr[i].profit 
             << ", Deadline = " << arr[i].deadline << endl;
        
        // Try to schedule job in the latest possible slot
        for (int j = min(max_deadline, arr[i].deadline) - 1; j >= 0; j--) {
            cout << "Checking slot " << j << ": ";
            if (slots[j] == -1) {
                slots[j] = arr[i].id;
                total_profit += arr[i].profit;
                cout << "Assigned to Job " << arr[i].id << endl;
                
                // Print current schedule
                cout << "Schedule after step " << step << ": ";
                for (int k = 0; k < max_deadline; k++) {
                    if (slots[k] == -1) cout << "_ ";
                    else cout << "J" << slots[k] << " ";
                }
                cout << "(Profit = " << total_profit << ")" << endl;
                step++;
                break;
            } else {
                cout << "Occupied by Job " << slots[j] << endl;
            }
        }
    }
    
    // Print final schedule
    cout << "Final Schedule: ";
    for (int i = 0; i < max_deadline; i++) {
        if (slots[i] != -1)
            cout << "J" << slots[i] << " ";
    }
    cout << endl << "Maximum profit achievable: " << total_profit << endl;
}

int main() {
    int n;
    cout << "Enter the number of jobs: ";
    cin >> n;
    
    Job arr[n];
    cout << "Enter job ID, profit, and deadline for each job:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "Job " << i << " - ID: ";
        cin >> arr[i].id;
        cout << "Job " << i << " - Profit: ";
        cin >> arr[i].profit;
        cout << "Job " << i << " - Deadline: ";
        cin >> arr[i].deadline;
    }
    
    // Perform Job Sequencing
    jobSequencing(arr, n);
    
    return 0;
}