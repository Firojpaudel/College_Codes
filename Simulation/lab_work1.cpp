#include <iostream>
#include <iomanip>
using namespace std;

int main()
{
    float Y_1, Y, I, T;
    float C[5];
    float G[5] = {20, 25, 30, 35, 40};

    cout << "Enter initial value of lagged variable Y_1: ";
    cin >> Y_1;

    cout << "\nThe growth in consumption is given following table:\n";
    cout << "\nYear \t\tConsumption\n";
    cout << "---------------------------\n";

    for (int i = 0; i < 5; ++i)
    {
        I = 2 + 0.1f * Y_1;
        Y = 45.45f + 2.27f * (I + G[i]);
        T = 0.2f * Y;
        C[i] = 20 + 0.7f * (Y - T);

        cout << setw(4) << i + 1 << "\t\t" << fixed << setprecision(2) << C[i] << endl;

        Y_1 = Y;
    }

    return 0;
}