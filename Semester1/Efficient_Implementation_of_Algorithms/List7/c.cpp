// https://codeforces.com/problemset/problem/2132/E

#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        int n, m, q;
        cin >> n >> m >> q;
        int a[n], b[m];
        long long pref_a[n + 1], pref_b[m + 1];
        pref_a[0] = pref_b[0] = 0;
        for (int i = 0; i < n; i++) cin >> a[i];
        for (int i = 0; i < m; i++) cin >> b[i];
        sort(a, a + n, greater<int>());
        sort(b, b + m, greater<int>());
        for (int i = 1; i <= n; i++) pref_a[i] = pref_a[i - 1] + a[i - 1];
        for (int i = 1; i <= m; i++) pref_b[i] = pref_b[i - 1] + b[i - 1];
        int a_cards = 0, b_cards = 0;
        vector<pair<int, int>> cnt(n + m + 1);
        for (int x = 1; x <= n + m; x++)
        {
            if (a_cards == n) b_cards++;
            else if (b_cards == m) a_cards++;
            else 
            {
                if (a[a_cards] > b[b_cards]) a_cards++;
                else b_cards++;
            }
            cnt[x] = {a_cards, b_cards};
        }
        while (q--)
        {
            int x, y, z;
            cin >> x >> y >> z;
            int a_ans = cnt[z].f;
            int b_ans = cnt[z].s;
            if (a_ans > x) cout << pref_a[x] + pref_b[z - x] << '\n';
            else if (b_ans > y) cout << pref_b[y] + pref_a[z - y] << '\n';
            else cout << pref_a[a_ans] + pref_b[b_ans] << '\n';
        }
    }
    return 0;
}