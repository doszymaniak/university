// https://codeforces.com/problemset/problem/2125/C

// Calculate the count of numbers in a given range that are divisible by 2, 3, 5 or 7,
// then subtract this count from the total to get the number of "good" numbers
// Use bitmasks to iterate over every subset and apply the inclusion-exclusion principle

#include <bits/stdc++.h>

#define ll long long

using namespace std;

vector<int> primes = {2, 3, 5, 7};

int lcm_of_mask(int mask)
{
    int res = 1;
    for (int i = 0; i < 4; i++)
    {
        if (mask & (1 << i)) res = lcm(res, primes[i]);
    }
    return res;
}

ll how_many_bad(ll n)
{
    ll result = 0;
    for (int mask = 1; mask < (1 << 4); mask++)
    {
        int curr_lcm = lcm_of_mask(mask);
        int bits_in_mask = __builtin_popcount(mask);
        if (bits_in_mask % 2) result += (n / curr_lcm);
        else result -= (n / curr_lcm);
    }
    return result;
}


int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int q;
    cin >> q;
    while (q--)
    {
        ll l, r;
        cin >> l >> r;
        ll total = r - l + 1;
        cout << total - (how_many_bad(r) - how_many_bad(l - 1)) << '\n';
    }
}