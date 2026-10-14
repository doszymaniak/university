#include <iostream>
#include <cstdint>

using namespace std;

auto lucas_number(uint64_t n)
{
    if (n == 0)
        return uint64_t{2};
    if (n == 1)
        return uint64_t{1};
    return lucas_number(n - 1) + lucas_number(n - 2);
}

int main()
{
    for (int i = 0; i <= 20; i++)
        cout << "lucas_number(" << i << "): " << lucas_number(i) << '\n';
    return 0;
}