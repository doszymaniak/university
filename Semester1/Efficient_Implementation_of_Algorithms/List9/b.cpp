// https://codeforces.com/problemset/problem/526/B

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int lights = (1 << (n + 1));
    vector<int> a(lights * 2, 0);
    for (int i = 2; i < lights; i++) cin >> a[i];
    int res = 0;
    for (int node = lights - 1; node >= 1; node--)
    {
        int to_add = abs(a[node * 2] - a[node * 2 + 1]);
        res += to_add;
        a[node] += max(a[node * 2], a[node * 2 + 1]);
    }
    cout << res << '\n';
}