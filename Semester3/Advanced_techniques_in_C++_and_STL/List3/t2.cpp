#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "min (+): " << numeric_limits<long double>::min() << '\n';

    cout << "max (+): " << numeric_limits<long double>::max() << '\n';

    cout << "has_inifinity: " << numeric_limits<long double>::has_infinity << '\n';
    
    cout << "difference between 1 and the smallest value greater than 1: " << 
        numeric_limits<long double>::epsilon() << '\n';
    return 0;
}