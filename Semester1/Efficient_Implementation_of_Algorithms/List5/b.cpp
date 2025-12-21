// https://codeforces.com/problemset/problem/1726/C

#include <bits/stdc++.h>
#define f first
#define s second

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
        n *= 2;
        int levels = n / 2 + 7;
        vector<pair<int, int>> g[levels];
        stack<int> s;
        char bracket;
        for (int i = 0; i < n; i++)
        {
            cin >> bracket;
            if (bracket == '(') s.push(i);
            else
            {
                int start = s.top();
                g[s.size()].push_back({start, i});
                s.pop();
            }
        }
        int res = 0;
        for (int i = 0; i < levels; i++)
        {
            int merges = 0;
            for (int j = 0; j < g[i].size(); j++)
            {
                if (j == g[i].size() - 1) break;
                if (g[i][j].s + 1 == g[i][j + 1].f) merges++;
            }
            res += (g[i].size() - merges);
        }
        cout << res << '\n';
    }
    return 0;
}