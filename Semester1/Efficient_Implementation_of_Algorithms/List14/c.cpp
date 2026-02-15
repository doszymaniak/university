// https://codeforces.com/problemset/problem/1486/B

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
        cin >> n;
        vector<int> x(n), y(n);
        for (int i = 0; i < n; i++) cin >> x[i] >> y[i];
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        int diff1 = x[n / 2] - x[(n - 1) / 2] + 1;
        int diff2 = y[n / 2] - y[(n - 1) / 2] + 1;
        cout << 1LL * diff1 * diff2 << '\n';
    }
    return 0;
}