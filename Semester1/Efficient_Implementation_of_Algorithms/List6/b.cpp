// https://codeforces.com/problemset/problem/1277/B

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
        set<int, greater<int>> s;
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            if (a % 2) continue;
            s.insert(a);
        }
        set<int, greater<int>>::iterator it = s.begin();
        int res = 0;
        while (it != s.end())
        {
            int curr = *it;
            it++;
            while (curr % 2 == 0) 
            {
                curr /= 2;
                res++;
                auto same = s.find(curr);
                if (same != s.end()) break;
            }
        }
        cout << res << '\n';
    }
    return 0;
}