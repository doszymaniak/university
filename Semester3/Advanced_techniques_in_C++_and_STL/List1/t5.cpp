#include <iostream>
#include <math.h>

using namespace std;

int main()
{
    double a, b, c;
    cin >> a >> b >> c;

    if (a == 0)
        cout << "This is not a quadratic equation" << '\n';
    else if (const double delta = b * b - (4 * a * c); delta > 0)
    {
        double x1 = (-b - sqrt(delta)) / (2 * a);
        double x2 = (-b + sqrt(delta)) / (2 * a);

        cout << "x1 = " << x1 << ", x2 = " << x2 << '\n';
    }
    else if (delta == 0)
    {
        double x = -b / (2 * a);
        cout << "x = " << x << '\n';
    }
    else
        cout << "No real roots\n";
    return 0;
}

// 1, -5, 6 -> x1 = 2, x2 = 3
// 1, -4, 4 -> x = 2
// 1 2 5 -> no roots