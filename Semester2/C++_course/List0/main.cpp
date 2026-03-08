#include <iostream>

using namespace std;

bool is_prime(long long num)
{
    if (num <= 1) return false;
    for (long long i = 2; i * i <= num; i++)
    {
        if (num % i == 0) return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        cout << "No arguments! Please enter at least one number\n";
        return 1;
    }
    for (int i = 1; i < argc; i++)
    {
        long long num = 0;
        try
        {
            num = stoll(argv[i]);
        }
        catch (const invalid_argument &)
        {
            cout << "Invalid argument: " << argv[i] << '\n';
            continue;
        }
        catch (const out_of_range &)
        {
            cout << "Number out of range: " << argv[i] << '\n';
            continue;
        }
        if (is_prime(num)) cout << num << " ";
    }
    cout << '\n';
    return 0;
}