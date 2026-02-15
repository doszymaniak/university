// https://codeforces.com/problemset/problem/526/A

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    string a;
    cin >> a;
    for (int i = 0; i < n; i++)
    {
        if (a[i] != '*') continue;
        for (int jump = 1; i + 4 * jump < n; jump++)
        {
            if (a[i + jump] == '*' && a[i + 2 * jump] == '*' &&
                a[i + 3 * jump] == '*' && a[i + 4 * jump] == '*')
            {
                cout << "YES\n";
                return 0;
            }
        }
    }
    cout << "NO\n";
    return 0;
}