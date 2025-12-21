// https://codeforces.com/problemset/problem/566/D

#include <bits/stdc++.h>

using namespace std;

vector<int> parent, next_el;

int find(int i)
{
    if (parent[i] == i) return i;
    return parent[i] = find(parent[i]);
}

void unite(int i, int j)
{
    int rep_i = find(i);
    int rep_j = find(j);
    if (rep_i == rep_j) return;
    parent[rep_j] = rep_i;
}

void range_unite(int i, int j)
{
    int curr = i + 1;
    while (curr <= j)
    {
        if (curr <= j) unite(curr - 1, curr);
        int next_curr = next_el[curr];
        next_el[curr] = max(j + 1, next_el[curr]);
        curr = next_curr;
    }
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, q;
    cin >> n >> q;
    for (int i = 0; i < n; i++) 
    {
        parent.push_back(i);
        next_el.push_back(i + 1);
    }
    int t, a, b;
    while (q--)
    {
        cin >> t >> a >> b;
        a--;
        b--;
        if (t == 3)
        {
            if (find(a) == find(b)) cout << "YES\n";
            else cout << "NO\n";
            continue;
        }
        if (t == 1)
        {
            unite(a, b);
            continue;
        }
        range_unite(a, b);
    }
    return 0;
}