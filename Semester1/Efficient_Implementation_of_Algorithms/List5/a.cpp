// https://codeforces.com/problemset/problem/1620/A

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
        string s;
        cin >> s;
        int cnt = 0;
        for (int i = 0; i < s.size(); i++)
        {
            if (s[i] == 'N') cnt++;
        }
        if (cnt == 1) cout << "NO\n";
        else cout << "YES\n";
    }
    return 0;
}