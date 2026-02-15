// https://codeforces.com/problemset/problem/1498/A

#include <bits/stdc++.h>

using namespace std;

long long gcd_sum(long long x)
{
    long long sum_digits = 0;
    long long tmp = x;
    while (tmp > 0)
    {
        sum_digits += (tmp % 10);
        tmp /= 10;
    }
    return gcd(sum_digits, x);
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        long long n;
        cin >> n;
        while (1)
        {
            if (gcd_sum(n) > 1)
            {
                cout << n << '\n';
                break;
            }
            n++;
        }
    }
    return 0;
}