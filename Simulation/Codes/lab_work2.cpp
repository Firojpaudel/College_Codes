#include <iostream>
#include <iomanip>
#include <string>

using namespace std;

// Function to print a horizontal line for UI
void printLine(int width) {
    cout << string(width, '=') << endl;
}

int main() {
    float inter_arrival_time, service_time;

    // Input section with header
    printLine(50);
    cout << "|          M/M/1 Queue Calculator                 |" << endl;
    printLine(50);
    cout << "Enter inter-arrival time (minutes): ";
    cin >> inter_arrival_time;
    cout << "Enter average service time (minutes): ";
    cin >> service_time;

    // Input validation
    if (inter_arrival_time <= 0 || service_time <= 0) {
        printLine(50);
        cout << "| Error: Times must be positive.             |" << endl;
        printLine(50);
        return 1;
    }

    // Calculate rates (customers per minute)
    float lambda = 1.0 / inter_arrival_time;
    float mu = 1.0 / service_time;

    // Check for queue stability
    if (mu <= lambda) {
        printLine(50);
        cout << " Error: Service rate must exceed arrival rate. " << endl;
        printLine(50);
        return 1;
    }

    // M/M/1 queue calculations
    float p0 = 1.0 - (lambda / mu);              // Probability of no waiting
    float L = lambda / (mu - lambda);            // Expected number in system
    float W = 1.0 / (mu - lambda);              // Expected time in system (minutes)

    // Output section with enhanced UI
    printLine(50);
    cout << "|          Queue Analysis Results                 |" << endl;
    printLine(50);
    cout << fixed << setprecision(4);
    cout << "  Arrival rate (lambda): " << setw(16) << lambda << " cust/min  " << endl;
    cout << "  Service rate (mu): " << setw(19) << mu << " cust/min  " << endl;
    printLine(50);
    cout << " I.  Probability of no waiting: " << setw(12) << p0 << endl;
    cout << " II. Expected customers in bank: " << setw(11) << L << endl;
    cout << " III. Expected time in bank: " << setw(11) << W << " min " << endl;
    printLine(50);

    return 0;
}