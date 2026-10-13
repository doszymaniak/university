#include <iostream>
#include <cmath>

using namespace std;

double fast_log(double x, int k_max)
{
    if (x < 0.0 || isnan(x))
        return NAN;

    if (x == 0.0)
        return -INFINITY;

    if (isinf(x))
        return INFINITY;

    if (k_max <= 0)
        return 0.0; 

    const double e = 2.718281828459045;
    int n = 0;

    while (x > 1.5)
    {
        x /= e;
        n++;
    }

    while (x < 0.5)
    {
        x *= e;
        n--;
    }

    double x_minus_1 = x - 1.0;
    double sign = 1;
    double res = 0.0;
    double power = x_minus_1;
    for (int k = 1; k <= k_max; k++)
    {
        res += sign * (power / k);
        sign = -sign;
        power *= x_minus_1;
    }

    return static_cast<double>(n) + res;
}

int main()
{
    double x = 10.0;
    int k_max = 15;
    cout << "my log: ln(" << x << ") = " << fast_log(x, k_max) << "\n";
    cout << "std::log: ln(" << x << ") = " << log(x) << "\n";
    return 0;
}