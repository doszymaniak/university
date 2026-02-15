// https://codeforces.com/problemset/problem/978/D

#include <bits/stdc++.h>

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    int seq[n];
    for (int i = 0; i < n; i++) cin >> seq[i];
    if (n <= 2)
    {
        cout << 0 << '\n';
        return 0;
    }
    int cnt = INT_MAX;
    for (int first_change = -1; first_change <= 1; first_change++)
    {
        for (int second_change = -1; second_change <= 1; second_change++)
        {
            bool ok = true;
            int curr_cnt = 0;
            int a = seq[0] + first_change;
            int b = seq[1] + second_change;
            curr_cnt = abs(first_change) + abs(second_change);
            for (int i = 2; i < n; i++)
            {
                int curr = a + i * (b - a);
                if (abs(curr - seq[i]) > 1)
                {
                    ok = false;
                    break;
                }
                else if (curr != seq[i]) curr_cnt++;
            }
            if (ok) cnt = min(cnt, curr_cnt);
        }
    }
    if (cnt == INT_MAX) cout << -1 << '\n';
    else cout << cnt << '\n';
    return 0;
}