#include <iostream>

using namespace std;

template <typename T, typename F>
class Sequence {
private:
    T f;
    F g;

public:
    Sequence(T f1, F f2) : f(f1), g(f2) {}

    template <typename X>
    auto operator () (X x) const
    {
        f(x);
        return g(x);
    }
};

template <typename T, typename F>
auto sequence(T f, F g)
{
    return Sequence(f, g);
}

int multiply_by_2(int x)
{
    return x * 2;
}

void print_num(int x)
{
    cout << "x: " << x << '\n';
}

int main()
{
    cout << sequence(print_num, multiply_by_2)(2) << '\n';
    return 0;
}