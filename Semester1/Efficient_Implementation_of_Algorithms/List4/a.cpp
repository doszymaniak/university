// https://codeforces.com/problemset/problem/2064/A

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
        int n, moves = 0;
        string s;
        cin >> n >> s;
        for (int i = 1; i < n; i++)
        {
            if (s[i] != s[i - 1]) moves++;
        }
        if (s[0] == '1') moves++;
        cout << moves << '\n';
    }
    return 0;
}