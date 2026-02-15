// https://codeforces.com/problemset/problem/1624/C

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
        int n;
        cin >> n;
        vector<int> a;
        for (int i = 0; i < n; i++)
        {
            int tmp;
            cin >> tmp;
            a.push_back(tmp);
        }
        sort(a.begin(), a.end(), greater<int>());
        vector<bool> perm(n, 0);
        bool ok = true;
        for (int i = 0; i < n; i++)
        {
            int curr = a[i];
            while (curr > n || perm[curr]) curr /= 2;
            if (curr > 0) perm[curr] = true;
            else 
            {
                ok = false;
                break;
            }
        }
        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
}