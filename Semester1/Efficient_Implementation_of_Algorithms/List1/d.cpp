// https://codeforces.com/problemset/problem/1982/E

#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int MOD = 1e9 + 7;
const ll INV = 5e8 + 4;

unordered_map<ll, unordered_map<int, ll>> mapa;

ll mod_mult_div2(ll a, ll b)
{
    ll res = (a % MOD) * (b % MOD) % MOD;
    res = (res * INV) % MOD;
    return res;
}

ll f(ll n, int k)
{
    if (k < 0) return 0;
    if (mapa[n].count(k)) return mapa[n][k];
    int x = 0;
    ll res = 0;
    while ((1LL << (x + 1)) < n) x++;
    if (x == k && n == (1LL << (x + 1))) res = mod_mult_div2(n, n - 1);
    else if (x <= k) res = mod_mult_div2(n, n + 1);
    else res = (f(1LL << x, k) + f(n - (1LL << x), k - 1)) % MOD;
    return mapa[n][k] = res;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int t;
    cin >> t;
    while (t--)
    {
        ll n;
        int k;
        cin >> n >> k;
        cout << f(n, k) << '\n';
    }
    return 0;
}