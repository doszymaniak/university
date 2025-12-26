// https://codeforces.com/problemset/problem/1613/C

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
        int n;
        long long h;
        cin >> n >> h;
        long long a[n];
        for (int i = 0; i < n; i++) cin >> a[i];
        long long start = 1, end = h, current_h = 0, k;
        while (start <= end)
        {
            k = (start + end) / 2;
            current_h = 0;
            for (int i = 0; i < n - 1; i++)
                current_h += min(k, a[i + 1] - a[i]);
            current_h += k;
            if (current_h < h) start = k + 1;
            else end = k - 1;
        }
        cout << end + 1 << '\n';
    }
    return 0;
}