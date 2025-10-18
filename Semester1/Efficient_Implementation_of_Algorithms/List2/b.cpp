// https://codeforces.com/problemset/problem/1606/C

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
        int n, k;
        cin >> n >> k;
        vector<int> money;
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            money.push_back(pow(10, a));
        }
        long long res = 0;
        int remaining = k + 1;
        for (int i = 0; i < n; i++)
        {
            int limit = i < n - 1 ? money[i + 1] / money[i] - 1 : remaining;
            if (limit < remaining)
            {
                res += (1LL * limit * money[i]);
                remaining -= limit;
            }
            else 
            {
                res += (1LL * remaining * money[i]);
                remaining = 0;
            }
            if (remaining == 0) break;
        }
        cout << res << '\n';
    }
    return 0;
}