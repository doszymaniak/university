// https://codeforces.com/problemset/problem/103/D

#include <bits/stdc++.h>
#define f first
#define s second

using namespace std;

const int N = 3e5 + 7;
int weights[N];
map<pair<int, int>, long long> results;

bool comp(pair<int, int> pair1, pair<int, int> pair2)
{
    return pair1.s < pair2.s;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int n;
    cin >> n;
    for (int i = 0; i < n; i++) cin >> weights[i];
    int q;
    cin >> q;
    vector<pair<int, int>> queries(q), queries_sorted(q);
    for (int i = 0; i < q; i++) 
    {
        cin >> queries[i].f >> queries[i].s;
        queries[i].f--;
        queries_sorted[i].f = queries[i].f;
        queries_sorted[i].s = queries[i].s;
    }
    sort(queries_sorted.begin(), queries_sorted.end(), comp);
    int c = sqrt(n) + 1;
    long long dp[n];
    int last_b = -1;
    for (int i = 0; i < q; i++)
    {
        int a = queries_sorted[i].f;
        int b = queries_sorted[i].s;
        if (b > c)
        {
            long long ans = 0;
            for (int j = a; j < n; j += b) ans += weights[j];
            results[{a, b}] = ans;
            continue;
        }
        if (b == last_b)
        {
            results[{a, b}] = dp[a];
            continue;
        }
        for (int j = n - 1; j >= 0; j--)
        {
            if (j + b >= n) dp[j] = weights[j];
            else dp[j] = dp[j + b] + weights[j];
        }
        last_b = b;
        results[{a, b}] = dp[a];
    }
    for (int i = 0; i < q; i++)
    {
        int a = queries[i].f, b = queries[i].s;
        cout << results[{a, b}] << '\n';
    }
    return 0;
}