// https://codeforces.com/problemset/problem/1138/A

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n, prev = -1, curr, idx = 0, curr_cnt = 0;
    cin >> n;
    int seg[n];
    for (int i = 0; i < n; i++)
    {
        cin >> curr;
        if (curr != prev && prev != -1)
        {
            seg[idx] = curr_cnt;
            idx++;
            curr_cnt = 1;
            prev = curr;
        }
        else 
        {
            curr_cnt++;
            prev = curr;
        }
    }
    if (curr_cnt > 0) seg[idx] = curr_cnt;
    int res = 0;
    for (int i = 0; i < idx; i++)
    {
        int first = seg[i], second = seg[i + 1];
        int curr_len = min(first, second) * 2;
        res = max(res, curr_len);
    }
    cout << res << '\n';
    return 0;
}