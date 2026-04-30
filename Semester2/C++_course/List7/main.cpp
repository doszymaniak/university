#include "rational.hpp"
#include <iostream>

using namespace std;
using namespace calculations;

void print_rational(const Rational &r)
{
    cout << "num: " << r.get_num() << '\n';
    cout << "denom: " << r.get_denom() << '\n';
    cout << "num / denom: " << r << "\n";
}

int main()
{
    Rational r1;
    cout << "r1 - default constructor:\n";
    print_rational(r1);

    Rational r2(5, 3);
    cout << "\n\nr2 - constructor with num and denom (5 / 3):\n";
    print_rational(r2);

    Rational r3(6);
    cout << "\n\nr3 - constructor with only one argument given (6 / 1):\n";
    print_rational(r3);

    Rational r4(r3);
    cout << "\n\nr4 - copied from r3 (6 / 1):\n";
    print_rational(r4);

    r4 = r2;
    cout << "\n\nCopy assignment - r4 is now a copy of r2 (5 / 3):\n";
    print_rational(r4);

    cout << "\n\nAn attempt to create a rational with 0 in denom:\n";
    try 
    {
        Rational exc(4, 0);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    cout << "\n\nAn attempt to create a rational with a negative number in denom:\n";
    try
    {
        Rational exc(6, -5);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    Rational r5(36, 12);
    cout << "\n\nr5 is being simplified (36 / 12):\n";
    print_rational(r5);

    Rational r6(2, 3);
    cout << "\n\nr6 (2 / 3):\n";
    print_rational(r6);

    Rational r7(4, 3);
    cout << "\n\nr7 (4 / 3):\n";
    print_rational(r7);
    
    Rational add = r6 + r7;
    cout << "\n\nr6 + r7 (6 / 3):\n";
    print_rational(add);

    Rational sub = r6 - r7;
    cout << "\n\nr6 - r7 (-2 / 3):\n";
    print_rational(sub);

    Rational mult = r6 * r7;
    cout << "\n\nr6 * r7 (8 / 9):\n";
    print_rational(mult);

    Rational div = r6 / r7;
    cout << "\n\nr6 / r7 (6 / 12):\n";
    print_rational(div);

    Rational change_sign = -r6;
    cout << "\n\n-r6 (-2 / 3):\n";
    print_rational(change_sign);

    Rational reciprocal = !r7;
    cout << "\n\n!r7 (3 / 4):\n";
    print_rational(reciprocal);

    Rational r8(2359348, 99900);
    cout << "\n\nr8 (2359348 / 99900):\n";
    print_rational(r8);
    return 0;
}