// https://codeforces.com/problemset/problem/1359/C

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int hot, cold, temp;
        cin >> hot >> cold >> temp;
        if (temp * 2 <= hot + cold) 
        {
            cout << 2 << '\n';
            continue;
        }
        long long start = 0, end = 1e6, mid;
        while (start <= end)
        {
            mid = (start + end) / 2;
            long long hot_temp = (mid + 1) * hot;
            long long cold_temp = mid * cold;
            long long all_cups = 2 * mid + 1;
            if ((hot_temp + cold_temp) < temp * all_cups) end = mid - 1;
            else start = mid + 1;
        }
        long long k = end;
        long long left_num = hot * (k + 1) + cold * k - temp * (2 * k + 1);
        long long left_den = 2 * k + 1;
        long long right_num = temp * (2 * k + 3) - hot * (k + 2) - cold * (k + 1);
        long long right_den = 2 * k + 3;
        if (left_num * right_den <= right_num * left_den) cout << 2 * k + 1 << '\n';
        else cout << 2 * k + 3 << '\n';
    }
}