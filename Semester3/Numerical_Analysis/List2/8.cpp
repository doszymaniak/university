#include <iostream>
#include <cmath>
#include <iomanip>
#include <vector>

using namespace std;

double f(double x) 
{
    double power_15 = pow(x, 15);
    return (sqrt(8104 * power_15 + 4) - 2) / power_15;
}

double better_f(double x)
{
    double power_15 = pow(x, 15);
    return 8104 / (sqrt(8104 * power_15 + 4) + 2);
}

int main() 
{
    vector<double> test_values = {0.5, 0.1, 0.05, 0.02, 0.01, 0.005};

    cout << left << setw(12) << "x" << setw(24) << "f(x)" 
        << setw(24) << "better_f(x)" << "Blad wzgledny" << "\n";
    cout << string(75, '-') << "\n";

    for (double x : test_values) 
    {
        double res_naive = f(x);
        double res_better = better_f(x);
        
        double rel_error = (res_better != 0) ? abs((res_naive - res_better) / res_better) : 0;

        cout << scientific << setprecision(2) << setw(12) << x
             << fixed << setprecision(10)
             << setw(24) << res_naive
             << setw(24) << res_better
             << scientific << setprecision(3) << rel_error << "\n";
    }
    return 0;
}