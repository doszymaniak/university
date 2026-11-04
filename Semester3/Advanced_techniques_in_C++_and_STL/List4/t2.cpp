#include <iostream>

using namespace std;

template <typename T, typename F>
class Compose {
private:
    T f;
    F g;

public:
    Compose(T f1, F f2) : f(f1), g(f2) {}

    template <typename X>
    auto operator () (X x) const { return f(g(x)); }
};

template <typename T, typename F>
auto compose(T f, F g)
{
    return Compose(f, g);
}

int add_3(int x)
{
    return x + 3;
}

int multiply_by_2(int x)
{
    return x * 2;
}

int main()
{
    cout << compose(add_3, multiply_by_2)(2) << '\n';
    cout << compose(add_3, compose(add_3, multiply_by_2))(3) << '\n';
    return 0;
}