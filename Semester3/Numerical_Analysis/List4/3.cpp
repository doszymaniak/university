#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

double f(double x)
{
    return x - 0.49;
}

int main()
{
    double a = 0.0, b = 1.0;
    double a0 = a, b0 = b;
    double alpha = 0.49;

    cout << fixed << setprecision(8);
    cout << "n    m_(n+1)       |e_n|         estimate\n";

    for (int n = 1; n <= 5; n++)
    {
        double m = (a + b) / 2.0;

        double en = abs(alpha - m);
        double estimate = (b0 - a0) / pow(2, n);

        cout << n << "    " << m << "    " << en << "    " << estimate << '\n';

        if (f(a) * f(m) < 0)
            b = m; 
        else
            a = m; 
    }
    return 0;
}