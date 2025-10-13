// https://codeforces.com/contest/1974/problem/E

#include <bits/stdc++.h>

#define ll long long
#define MAX_M 50

using namespace std;

const int N = 1e5 + 7;
ll dp[MAX_M + 1][N];
int c[MAX_M + 1], h[MAX_M + 1];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int months, salary, max_happiness = 0;
        cin >> months >> salary;
        for (int i = 1; i <= months; i++) 
        {
            cin >> c[i] >> h[i];
            max_happiness += h[i];
        }
        for (int i = 0; i <= months; i++)
            for (int j = 0; j <= max_happiness; j++) dp[i][j] = (j == 0 ? 0 : LLONG_MAX);

        for (int i = 1; i <= months; i++)
        {
            for (int j = 0; j <= max_happiness; j++)
            {
                dp[i][j] = dp[i - 1][j];
                ll money_available = 1LL * (i - 1) * salary;
                if (j - h[i] >= 0 && dp[i - 1][j - h[i]] != LLONG_MAX && dp[i - 1][j - h[i]] + c[i] <= money_available) 
                    dp[i][j] = min(dp[i][j], dp[i - 1][j - h[i]] + c[i]);
            }
        }

        for (int i = max_happiness; i >= 0; i--)
        {
            if (dp[months][i] != LLONG_MAX)
            {
                cout << i << '\n';
                break;
            }
        }
    }
}