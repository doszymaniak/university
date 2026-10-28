#include <iostream>
#include <type_traits>
#include <stdexcept>

using namespace std;

template <typename T1, typename T2>
void move_impl(T1 &val, T2 &dest, true_type, true_type)
{
    dest = *val;
}

template <typename T1, typename T2>
void move_impl(T1 &val, T2 &dest, true_type, false_type)
{
    throw invalid_argument("The first type is not convertible to the second type");
}

template <typename T1, typename T2>
void move_impl(T1 &val, T2 &dest, false_type, true_type)
{
    dest = val;
}

template <typename T1, typename T2>
void move_impl(T1 &val, T2 &dest, false_type, false_type)
{
    throw invalid_argument("The first type is not convertible to the second type");
}

template <typename T1, typename T2>
void move_val(T1 &src, T2 &dest)
{
    using second_type = typename conditional<is_pointer<T1>::value,
        typename remove_pointer<T1>::type, T1>::type;
    move_impl(src, dest, is_pointer<T1>(), is_convertible<second_type, T2>());
}

int main()
{
    int a = 10;
    int b = 0;
    move_val(a, b);
    cout << "b = " << b << endl;

    int *p = &a;
    move_val(p, b);
    cout << "b = " << b << endl;

    double c = 3.14;
    move_val(c, b);
    cout << "b = " << b << endl;

    return 0;
}