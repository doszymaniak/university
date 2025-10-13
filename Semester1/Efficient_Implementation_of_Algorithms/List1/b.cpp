// https://codeforces.com/contest/2136/problem/C

#include <bits/stdc++.h>

using namespace std;

const int N = 2e5 + 7;
vector<int> positions[N];
int dp[N];

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
        for (int i = 1; i <= n; i++)
        {
            int curr;
            cin >> curr;
            positions[curr].push_back(i);
            if (positions[curr].size() < curr)
            {
                dp[i] = dp[i - 1];
                continue;
            }
            int last_idx = positions[curr][positions[curr].size() - curr];
            dp[i] = max(dp[i - 1], curr + dp[last_idx - 1]);
        }
        cout << dp[n] << '\n';
        for (int i = 0; i <= n; i++)
        {
            positions[i].clear();
            dp[i] = 0;
        }
    }
}