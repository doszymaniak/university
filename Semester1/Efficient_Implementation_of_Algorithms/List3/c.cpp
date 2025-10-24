// https://codeforces.com/contest/690/problem/D2

#include <bits/stdc++.h>

#define ll long long

using namespace std;

const int MOD = 1e6 + 3, N = 7e5 + 3;

int n, c;
int fact[N], inv_fact[N];

int fast_exp(int base, int pow)
{
    if (pow == 0) return 1;
    if (pow == 1) return base;
    ll half = fast_exp(base, pow / 2);
    if (pow % 2 == 0) return (half * half) % MOD;
    else return (((half * half) % MOD) * base) % MOD;
}

void precompute_factorials()
{
    ll curr_fact = 1;
    fact[0] = inv_fact[0] = 1;
    for (int i = 1; i <= n + c; i++)
    {
        curr_fact = (i * curr_fact) % MOD;
        fact[i] = curr_fact;
    }
    inv_fact[n + c] = fast_exp(fact[n + c], MOD - 2);
    for (int i = n + c - 1; i >= 1; i--) inv_fact[i] = (1LL * inv_fact[i + 1] * (i + 1)) % MOD;
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cin >> n >> c;
    precompute_factorials();
    int res = (1LL * fact[n + c] * inv_fact[c]) % MOD;
    res = ((1LL * res * inv_fact[n]) % MOD - 1 + MOD) % MOD;
    cout << res << '\n';
    return 0;
}