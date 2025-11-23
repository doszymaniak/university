// https://codeforces.com/contest/245/problem/H

#include <bits/stdc++.h>

using namespace std;

const int N = 5e3 + 7;
int dp[N][N];
bool is_pal[N][N];
string s;
int n;

void solve()
{
    for (int i = 1; i <= n; i++)
    {
        dp[i][i] = 1;
        is_pal[i][i] = 1;
        is_pal[i + 1][i] = 1;
    }
    for (int len = 2; len <= n; len++)
    {
        for (int i = 1; i + len - 1 <= n; i++)
        {
            int j = i + len - 1;
            is_pal[i][j] = (s[i - 1] == s[j - 1]) && is_pal[i + 1][j - 1];
            dp[i][j] = dp[i + 1][j] + dp[i][j - 1] + is_pal[i][j] - dp[i + 1][j - 1];
        }
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> s >> q;
    n = s.length();
    solve();
    while (q--)
    {
        int i, j;
        cin >> i >> j;
        cout << dp[i][j] << '\n';
    }
    return 0;
}