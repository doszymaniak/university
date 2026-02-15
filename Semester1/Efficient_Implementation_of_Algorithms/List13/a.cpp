// https://codeforces.com/problemset/problem/914/A

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; i++) cin >> a[i];
    sort(a.begin(), a.end(), greater<int>());
    for (int i = 0; i < n; i++)
    {
        int sq = int(sqrt(a[i]));
        if (sq * sq == a[i]) continue;
        cout << a[i] << '\n';
        break;
    }
    return 0;
}