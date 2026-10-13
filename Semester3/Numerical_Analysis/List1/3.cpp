#include <iostream>
#include <cmath>
#include <iomanip>

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
    double x = 0.01;
    cout << setprecision(17) << f(x) << '\n';
    cout << fixed << setprecision(17) << better_f(x) << '\n';
    return 0;
}