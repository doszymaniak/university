// https://codeforces.com/problemset/problem/1496/C

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
        vector<int> x, y;
        for (int i = 0; i < 2 * n; i++)
        {
            int a, b;
            cin >> a >> b;
            if (a == 0) y.push_back(abs(b));
            else x.push_back(abs(a));
        }
        sort(x.begin(), x.end());
        sort(y.begin(), y.end());
        double res = 0.0;
        for (int i = 0; i < n; i++) res += sqrt(1.0 * x[i] * x[i] + 1.0 * y[i] * y[i]);
        cout << setprecision(10) << fixed << res << '\n';
    }
    return 0;
}