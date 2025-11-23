// https://codeforces.com/contest/1553/problem/B

#include <bits/stdc++.h>

using namespace std;

string s, t;

bool solve()
{
    if (string(s.rbegin(), s.rend()) == t) return true;
    // Loop over the starting positions
    for (int i = 0; i < s.length(); i++)
    {
        // Move right
        string str = "";
        str += s[i];
        if (str == t) return true;
        for (int j = i + 1; j < s.length(); j++)
        {
            string right = s.substr(i, j - i + 1);
            string final = right;
            if (final == t || string(final.rbegin(), final.rend()) == t) return true;
            // Move left
            for (int k = j - 1; k >= 0; k--)
            {
                final += s[k];
                if (final == t) return true;
                if (final.length() > t.length()) break;
            }
        }
    }
    return false;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while (q--)
    {
        cin >> s >> t;
        if (solve()) cout << "YES" << '\n';
        else cout << "NO" << '\n';
    }
    return 0;
}