// https://codeforces.com/contest/996/problem/A

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, res = 0;
    cin >> n;
    int coins[] = {1, 5, 10, 20, 100};
    for (int i = 4; i >= 0; i--)
    {
        res += (n / coins[i]);
        n %= coins[i];
    }
    cout << res << '\n';
    return 0;
}