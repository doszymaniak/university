#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

double f_double(double x)
{
    double x_5 = 5 * x;
    double sinus_5_x = sin(x_5);
    double denom = 125 * (x * x * x);
    double num = 12156 * (x_5 - sinus_5_x);
    return num / denom;
}

float f_single(float x)
{
    float x_5 = 5 * x;
    float sinus_5_x = sin(x_5);
    float denom = 125 * (x * x * x);
    float num = 12156 * (x_5 - sinus_5_x);
    return num / denom;
}

double f_better(double x)
{
    return 2026.0 - 2532.5 * x * x;
}

int main()
{
    cout << scientific << setprecision(6);
    
    cout << left << setw(12) << "i" << setw(24) << "float" 
        << setw(24) << "double" << "f_better" << "\n";
    cout << string(75, '-') << "\n";

    for (int i = 11; i <= 20; i++) {
        double x_double = pow(10.0, -i);
        float x_float = static_cast<float>(x_double);

        float res_float = f_single(x_float);
        double res_double = f_double(x_double);
        double res_taylor = f_better(x_double);

        cout << setw(2) << i << " | " << setw(20) << res_float << " | "
            << setw(21) << res_double << " | " << setw(17) << res_taylor << "\n";
    }

    return 0;
}