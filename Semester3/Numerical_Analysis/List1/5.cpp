#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double integrals[50];

int main()
{
    integrals[0] = log(2027.0 / 2026.0);
    for (int i = 1; i <= 20; i++)
        integrals[i] = (1.0 / i) - (2026 * integrals[i - 1]);

    for (int i = 0; i <= 20; i++)
    {
        cout << "integrals[" << i << "]: " << setprecision(6) << fixed << integrals[i] << '\n';
    }
    return 0;
}