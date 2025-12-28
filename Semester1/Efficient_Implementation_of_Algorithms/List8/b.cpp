// https://codeforces.com/problemset/problem/2171/B

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
            if (tmp == -1 && (i == 0 || i == n - 1)) a.push_back(tmp);
            else if (tmp == -1) a.push_back(0);
            else a.push_back(tmp);
        }
        if (a[0] == -1 && a[n - 1] == -1)
        {
            a[0] = 0;
            a[n - 1] = 0;
        }
        else if (a[0] == -1) a[0] = a[n - 1];
        else if (a[n - 1] == -1) a[n - 1] = a[0];
        cout << abs(a[n - 1] - a[0]) << '\n';
        for (int i = 0; i < n; i++) cout << a[i] << " ";
        cout << '\n';
    }
}