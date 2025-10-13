// https://codeforces.com/problemset/problem/1859/B

#include <bits/stdc++.h>

#define ii pair<int, int>
#define f first 
#define s second

using namespace std;

bool compare_pairs(ii &a, ii &b)
{
    return a.second < b.second;
}

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
        vector<ii> mins;
        for (int i = 0; i < n; i++)
        {
            int m;
            cin >> m;
            vector<int> curr;
            for (int j = 0; j < m; j++)
            {
                int a;
                cin >> a;
                curr.push_back(a);
            }
            sort(curr.begin(), curr.end());
            mins.push_back({curr[0], curr[1]});
        }
        sort(mins.begin(), mins.end(), compare_pairs);
        int curr_first_min = mins[0].f;
        long long res = 0;
        for (int i = 1; i < mins.size(); i++)
        {
            if (mins[i].f < curr_first_min)
                curr_first_min = mins[i].f;
            res += mins[i].s;
        }
        res += curr_first_min;
        cout << res << '\n';
    }
    return 0;
}