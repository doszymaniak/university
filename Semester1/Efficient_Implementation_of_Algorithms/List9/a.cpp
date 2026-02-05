// https://codeforces.com/problemset/problem/129/B

#include <bits/stdc++.h>

using namespace std;

const int N = 107;
vector<int> g[N];

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, m;
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        g[a].push_back(b);
        g[b].push_back(a);
    }
    set<int> kicked_out;
    vector<int> reprimanded;
    int res = 0;
    while (1)
    {
        for (int i = 1; i <= n; i++)
        {
            int tied = 0;
            if (kicked_out.count(i)) continue;
            for (int j = 0; j < g[i].size(); j++)
            {
                if (kicked_out.count(g[i][j])) continue;
                tied++;
            }
            if (tied == 1) reprimanded.push_back(i);
        }
        if (reprimanded.size() > 0) res++;
        else break;
        for (int i = 0; i < reprimanded.size(); i++) kicked_out.insert(reprimanded[i]);
        reprimanded.clear();
    }
    cout << res << '\n';
}