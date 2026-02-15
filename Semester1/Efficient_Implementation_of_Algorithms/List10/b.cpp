// https://codeforces.com/problemset/problem/1612/C

#include <bits/stdc++.h>

using namespace std;

long long how_many(int n)
{
    return 1LL * n * (n + 1) / 2;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int k = 0;
        long long x = 0;
        cin >> k >> x;
        long long start = 1, end = 2 * k - 1;
        long long res = 2 * k - 1;
        while (start <= end)
        {
            int mid = (start + end) / 2;
            long long curr = 0;
            if (mid >= k) curr = how_many(k) + how_many(k - 1) - how_many(2 * k - 1 - mid);
            else curr = how_many(mid);
            if (curr >= x)
            {
                res = mid;
                end = mid - 1;
            }
            else start = mid + 1;
        }
        cout << res << '\n';
    }
}