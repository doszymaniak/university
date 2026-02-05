// https://codeforces.com/problemset/problem/510/C

#include <bits/stdc++.h>

using namespace std;

vector<string> words;
vector<int> g[26], ans;
// 0 - not visited, 1 - currently visiting, 2 - done
vector<int> vis(26);
bool cycle;

void dfs(int v)
{
    vis[v] = 1;
    for (int i = 0; i < g[v].size(); i++)
    {
        if (vis[g[v][i]] == 0) dfs(g[v][i]);
        else if (vis[g[v][i]] == 1) cycle = true;
    }
    vis[v] = 2;
    ans.push_back(v);
}

void topo_sort()
{
    for (int i = 0; i < 26; i++)
    {
        if (!vis[i]) dfs(i);
    }
    reverse(ans.begin(), ans.end());
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        string a;
        cin >> a;
        words.push_back(a);
    }
    for (int i = 0; i < n - 1; i++)
    {
        string a = words[i];
        string b = words[i + 1];
        int min_len = min(a.size(), b.size());
        if (a.substr(0, min_len) == b.substr(0, min_len) && a.size() > b.size())
        {
            cout << "Impossible\n";
            return 0;
        }
        for (int j = 0; j < min_len; j++)
        {
            if (a[j] == b[j]) continue;
            g[a[j] - 'a'].push_back(b[j] - 'a');
            break;
        }
    }
    topo_sort();
    if (cycle)
    {
        cout << "Impossible\n";
        return 0;
    }
    for (int i = 0; i < ans.size(); i++) cout << char(ans[i] + 'a');
    cout << '\n';
}