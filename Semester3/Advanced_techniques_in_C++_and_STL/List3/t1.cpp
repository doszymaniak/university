#include <iostream>
#include <limits>

using namespace std;

int main()
{
    cout << "min: " << numeric_limits<long long int>::min() << '\n';
    
    cout << "max: " << numeric_limits<long long int>::max() << '\n';
    
    cout << "is_signed: " << numeric_limits<long long int>::is_signed << '\n';

    cout << "bits: " << sizeof(long long int) * 8 << '\n';

    cout << "digits10: " << numeric_limits<long long int>::digits10 << '\n';
    return 0;
}