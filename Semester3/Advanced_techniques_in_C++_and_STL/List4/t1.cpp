#include <iostream>

using namespace std;

template <typename T>
using fun = T(*)(T);

template <typename T>
void transf(T tab[], int n, fun<T> f)
{
    for (int i = 0; i < n; i++) tab[i] = f(tab[i]);
}

double divide_by_two(double x)
{
    return x / 2;
}

int cube(int x)
{
    return x * x * x;
}

int main()
{
    double tab1[] = {2.0, 4.0, 6.0};
    int tab2[] = {6, 7, 8};

    transf(tab1, 3, divide_by_two);
    transf(tab2, 3, cube);

    for (int i = 0; i < 3; i++)
        cout << tab1[i] << " ";
    cout << '\n';
    for (int i = 0; i < 3; i++)
        cout << tab2[i] << " ";
    cout << '\n';
    return 0;
}
