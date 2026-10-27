#include <iostream>
#include <cmath>
#include <iomanip>
#include <numbers>

using namespace std;

const double e = exp(1.0);

double a(double x)
{
    double x_7 = pow(x, 7);
    double x_14 = pow(x, 14);
    double sq = sqrt(x_14 + 2026);
    return pow(x_7 + sq, -1);
}

double better_a(double x)
{
    double x_7 = pow(x, 7);
    double x_14 = pow(x, 14);
    double sq = sqrt(x_14 + 2026);
    return (sq - x_7) / 2026.0;
}

double b(double x)
{
    return pow(10, 8) * (pow(e, x) - pow(e, 2 * x));
}

double better_b(double x)
{
    double x_2 = pow(x, 2);
    double x_3 = pow(x, 3);
    return pow(10, 8) * (-x - (3 * x_2 / 2) - (7 * x_3 / 6));
}

double c(double x)
{
    double part = asin(x) - x;
    double x_3 = 6 * pow(x, -3);
    return x_3 * part;
}

double better_c(double x)
{
    double x_2 = pow(x, 2);
    double x_4 = pow(x, 4);
    return 1.0 + (9.0 / 20.0) * x_2 + (15.0 / 56.0) * x_4;
}

int main()
{
    cout << scientific << setprecision(8);

    cout << "\n========== PUNKT A ==========\n\n";

    cout << right
         << setw(15) << "x"
         << setw(24) << "a(-x)"
         << setw(24) << "better_a(-x)"
         << '\n';

    cout << string(87, '-') << '\n';

    for (double x = 1.0; x <= 1e6; x *= 10.0)
    {
        double original = a(-x);
        double improved = better_a(-x);

        cout << setw(15) << x
             << setw(24) << original
             << setw(24) << improved
             << '\n';
    }

    cout << "\n========== PUNKT B ==========\n\n";

    cout << right
         << setw(15) << "x"
         << setw(24) << "b(x)"
         << setw(24) << "better_b(x)"
         << '\n';

    cout << string(87, '-') << '\n';

    for (double x = 1e-2; x >= 1e-16; x /= 10.0)
    {
        double original = b(x);
        double improved = better_b(x);

        cout << setw(15) << x
             << setw(24) << original
             << setw(24) << improved
             << '\n';
    }

    cout << "\n========== PUNKT C ==========\n\n";

    cout << right
         << setw(15) << "x"
         << setw(24) << "c(x)"
         << setw(24) << "better_c(x)"
         << '\n';

    cout << string(87, '-') << '\n';

    for (double x = 1e-2; x >= 1e-16; x /= 10.0)
    {
        double original = c(x);
        double improved = better_c(x);

        cout << setw(15) << x
             << setw(24) << original
             << setw(24) << improved
             << '\n';
    }
    return 0;
}