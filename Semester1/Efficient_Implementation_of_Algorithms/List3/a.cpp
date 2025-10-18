// https://codeforces.com/problemset/problem/1674/C

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while (q--)
    {
        string s, t;
        cin >> s >> t;
        int a_in_s = s.length(), a_in_t = 0;
        for (int i = 0; i < t.length(); i++) if (t[i] == 'a') a_in_t++;
        if (a_in_t == 0)
        {
            cout << (1ll << a_in_s) << '\n';
            continue;
        }
        if (a_in_t == 1 && t.length() == 1)
        {
            cout << 1 << '\n';
            continue;
        }
        cout << -1 << '\n';
    }
    return 0;
}