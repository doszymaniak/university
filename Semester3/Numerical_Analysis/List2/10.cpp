#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main()
{
    double power_2_unstable = 1;
    double x_k_unstable = 2;

    double power_2_stable = 1;
    double x_k_stable = 2;

    cout << setprecision(15) << fixed;
    cout << left 
         << setw(8)  << "k" 
         << setw(24) << "x_k" 
         << setw(24) << "better x_k" 
         << setw(24) << "error x_k" 
         << "error better x_k" << "\n";
    cout << string(94, '-') << "\n";

    for (int k = 1; k <= 40; k++)
    {
        power_2_unstable *= 2;
        double fract_u = (x_k_unstable / power_2_unstable) * (x_k_unstable / power_2_unstable);
        double sq1_u = sqrt(1 - fract_u);
        double sq2_u = sqrt(2 * (1 - sq1_u));
        x_k_unstable = power_2_unstable * sq2_u;

        power_2_stable *= 2;
        double fract_s = (x_k_stable / power_2_stable) * (x_k_stable / power_2_stable);
        double sq1_s = sqrt(1 - fract_s);
        x_k_stable = x_k_stable * sqrt(2.0 / (1.0 + sq1_s));

        cout << k << "\t" 
             << x_k_unstable << "\t" 
             << x_k_stable << "\t" 
             << abs(x_k_unstable - M_PI) << "\t" 
             << abs(x_k_stable - M_PI) << "\n";
    }
    return 0;
}