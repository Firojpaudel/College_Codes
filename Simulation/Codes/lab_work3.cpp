#include <iostream>
#include <iomanip>
#include <string>
#include <cmath>

using namespace std;

void printLine(int width) {
    cout << string(width, '=') << endl;
}

int main() {
    float arrival_rate, service_time, time_to_seat, time_before_game;

    // Input section with header
    printLine(50);
    cout << "|          Stadium Ticket Queue Calculator        |" << endl;
    printLine(50);
    cout << "Enter arrival rate (customers per minute): ";
    cin >> arrival_rate;
    cout << "Enter average service time (seconds): ";
    cin >> service_time;
    cout << "Enter time to reach seat (minutes): ";
    cin >> time_to_seat;
    cout << "Enter time before game starts (minutes): ";
    cin >> time_before_game;

    // Input validation
    if (arrival_rate <= 0 || service_time <= 0 || time_to_seat < 0 || time_before_game < 0) {
        printLine(50);
        cout << "| Error: Inputs must be positive (or non-negative for times). |" << endl;
        printLine(50);
        return 1;
    }

    // Convert service time to minutes and calculate service rate
    float service_time_min = service_time / 60.0;
    float mu = 1.0 / service_time_min;

    // Check for queue stability
    if (mu <= arrival_rate) {
        printLine(50);
        cout << "| Error: Service rate must exceed arrival rate. |" << endl;
        printLine(50);
        return 1;
    }

    // M/M/1 queue calculations
    float W = 1.0 / (mu - arrival_rate);              // Expected time in system (minutes)
    float total_time = W + time_to_seat;              // Total time to be seated
    float prob_on_time = 1.0 - exp(-(mu - arrival_rate) * (time_before_game - time_to_seat)); // P(T <= time_before_game)

    // Output section
    printLine(50);
    cout << "|          Queue Analysis Results                |" << endl;
    printLine(50);
    cout << fixed << setprecision(4);
    cout << " Arrival rate (lambda): " << setw(16) << arrival_rate << " cust/min  " << endl;
    cout << " Service rate (mu): " << setw(19) << mu << " cust/min  " << endl;
    cout << " Expected time in queue system: " << setw(11) << W << " min " << endl;
    cout << " Total time to be seated: " << setw(13) << total_time << " min " << endl;
    printLine(50);
    cout << " Probability of being seated by kick-off: " << setw(7) << prob_on_time * 100 << "% " << endl;
    cout << " Can fan expect to be seated? " << setw(15) << (total_time <= time_before_game ? "Yes" : "No") << endl;
    printLine(50);

    return 0;
}