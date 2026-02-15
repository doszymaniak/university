// https://codeforces.com/problemset/problem/1797/A

#include <bits/stdc++.h>

using namespace std;

int n, m;

int to_block(int x, int y)
{
    if ((x == 1 && y == 1) || (x == n && y == 1) || (x == 1 && y == m) || (x == n && y == m))
        return 2;
    if (x == 1 || x == n || y == 1 || y == m) return 3;
    return 4;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        cin >> n >> m;
        int x1, y1, x2, y2;
        cin >> x1 >> y1 >> x2 >> y2;
        cout << min(to_block(x1, y1), to_block(x2, y2)) << '\n';
    }
}