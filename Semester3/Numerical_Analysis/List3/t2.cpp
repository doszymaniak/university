#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double formula(double r, double q)
{
    double q_3 = pow(q, 3);
    double r_2 = pow(r, 2);
    double sq = sqrt(q_3 + r_2);
    double first = cbrt(r + sq);
    double second = cbrt(r - sq);
    return first + second;
}

double better_formula(double r, double q)
{
    double q_3 = pow(q, 3);
    double r_2 = pow(r, 2);
    double sq = sqrt(q_3 + r_2);
    double a = cbrt(r + sq);
    double numerator = r + r_2 / (sq + q * sqrt(q));
    double denominator = a * a + a * sqrt(q) + q;

    return (numerator * (a + sqrt(q))) / (denominator * a);
}

int main()
{
    cout << scientific << setprecision(15);

    cout << setw(12) << "r"
         << setw(25) << "formula(r, 1)"
         << setw(25) << "better_formula"
         << '\n';

    cout << string(62, '-') << '\n';

    for (double r : {1e-8, 1e-12, 1e-16, 1e-20})
    {
        cout << setw(12) << r
             << setw(25) << formula(r, 1.0)
             << setw(25) << better_formula(r, 1.0)
             << '\n';
    }

    return 0;
}