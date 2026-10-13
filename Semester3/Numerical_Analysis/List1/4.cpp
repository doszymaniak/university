#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double fun[55];

void compute_fun()
{
    double first = 1.0;
    double second = -1.0 / 11.0;
    fun[0] = 1.0;
    fun[1] = -1.0 / 11.0;
    for (int i = 2; i <= 50; i++)
    {
        double current = ((142.0 / 11.0) * second) + ((13.0 / 11.0) * first);
        fun[i] = current;
        first = second;
        second = current;
    }
}

double better_fun(int n)
{
    return pow((-1.0 / 11.0), n);
}

int main()
{
    compute_fun();
    for (int i = 2; i <= 50; i++)
    {
        cout << "fun(" << i << "): " << setprecision(6) << fixed << fun[i] << '\n';
        cout << "better_fun(" << i << "): " << setprecision(6) << fixed <<  better_fun(i) << '\n';
        cout << '\n';
    }
    return 0;
}