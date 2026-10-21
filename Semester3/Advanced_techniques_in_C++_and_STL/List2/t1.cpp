#include <iostream>
#include <cstdint>
#include <memory>
#include <cstdlib>

using namespace std;

class Counter {
private:
    uint64_t counter;
public:
    Counter() : counter(1) {};
    virtual ~Counter()
    {
        cerr << "Destructor with counter: " << counter << '\n';
    }
    const uint64_t get_counter() const { return counter; }
    void increase_counter_by_i(uint64_t i) { counter += i; }
};

unique_ptr<Counter[]> fun(unique_ptr<Counter[]> tab, int m, int n, int part)
{
    if (m == 0) return tab;
    int val = m;
    for (int i = 0; i < part; i++)
    {
        int rand_index = rand() % n;
        tab[rand_index].increase_counter_by_i(val);
    }
    return fun(move(tab), m - 1, n, part);
}

int main()
{
    srand(static_cast<unsigned int>(time(nullptr)));
    int n = 10, m = 10;
    unique_ptr<Counter[]> tab(new Counter[n]);
    // Unique pointers are not copyable so we are using move
    int part = n * 0.1;
    tab = fun(move(tab), m, n, part);
    for (int i = 0; i < n; i++) cout << "counter " << i << ": " << tab[i].get_counter() << '\n';
    return 0;
}