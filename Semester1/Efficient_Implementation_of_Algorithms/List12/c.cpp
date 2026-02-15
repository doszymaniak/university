// https://codeforces.com/problemset/problem/1530/D

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
        int wishes[n];
        vector<int> gifted(n, -1);
        vector<int> a(n, -1);
        for (int i = 0; i < n; i++) 
        {
            cin >> wishes[i];
            wishes[i]--;
        }
        for (int i = 0; i < n; i++)
        {
            if (gifted[wishes[i]] == -1)
            {
                a[i] = wishes[i];
                gifted[wishes[i]] = i;
            }
        }
        vector<int> not_gifted;
        for (int i = 0; i < n; i++)
        {
            if (gifted[i] == -1) not_gifted.push_back(i);
        }
        int last = not_gifted.size() - 1;
        for (int i = 0; i < n; i++)
        {
            if (a[i] != -1) continue;
            if (not_gifted[last] == i) swap(not_gifted[0], not_gifted[last]);
            if (not_gifted[last] == i)
            {
                int idx = gifted[wishes[i]];
                a[idx] = i;
                a[i] = wishes[i];
                last--;
            }
            else
            {
                a[i] = not_gifted[last];
                last--;
                gifted[a[i]] = i;
            }
        }
        int res = 0;
        for (int i = 0; i < n; i++)
            if (a[i] == wishes[i]) res++;
        cout << res << '\n';
        for (int i = 0; i < n; i++) cout << a[i] + 1 << " ";
        cout << '\n';
    }
}