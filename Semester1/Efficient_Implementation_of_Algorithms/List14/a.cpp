// https://codeforces.com/problemset/problem/900/A

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int x, y;
    int cnt_pos = 0, cnt_neg = 0;
    for (int i = 0; i < n; i++)
    {
        cin >> x >> y;
        if (x > 0) cnt_pos++;
        else cnt_neg++;
    }
    if ((cnt_pos <= 1 && cnt_neg >= 1) || cnt_pos >= 1 && cnt_neg <= 1) cout << "Yes\n";
    else cout << "No\n";
    return 0;
}