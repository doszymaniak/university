// https://codeforces.com/problemset/problem/2171/C2

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
        int a[n], b[n];
        int xor_all = 0;
        for (int i = 0; i < n; i++) 
        {
            cin >> a[i];
            xor_all ^= a[i];
        }
        for (int i = 0; i < n; i++) 
        {
            cin >> b[i];
            xor_all ^= b[i];
        }
        if (!xor_all)
        {
            cout << "Tie\n";
            continue;
        }
        int highest_bit = 0;
        for (int i = 23; i >= 0; i--)
        {
            if ((1 << i) & xor_all)
            {
                highest_bit = i;
                break;
            }
        }
        // Check who controls the most significant bit
        int idx = 0;
        for (int i = 0; i < n; i++)
        {
            if ((1 << highest_bit) & (a[i] ^ b[i])) idx = i;
        }
        if (idx % 2 == 0) cout << "Ajisai\n";
        else cout << "Mai\n";
    }
}