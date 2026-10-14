#include <iostream>
#include <set>

using namespace std;

using SSet = set<string>;

int main()
{
    SSet cities = {"Wroclaw", "Cracow", "Warsaw", "Gdansk", "Poznan"};
    for (auto &city : cities)
        cout << city << '\n';
    return 0;
}