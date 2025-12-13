#include <stdio.h>
#define N 16
#define M 8000000

int idx[N], cycle[N], perm[N], z[N];
unsigned char c[M];
int max_p;

void set_c(int idx, int v)
{
    int c_idx = idx / 4, which = (idx % 4) * 2;
    unsigned char curr_val = c[c_idx];
    curr_val = curr_val & ~(3 << which);
    curr_val = curr_val | ((v & 3) << which);
    c[c_idx] = curr_val;
}

int get_c(int idx)
{
    int c_idx = idx / 4, which = (idx % 4) * 2;
    unsigned char curr_val = c[c_idx];
    return (curr_val >> which) & 3;
}

int main()
{
    for (int i = 0; i < N; i++) 
    {
        scanf("%d", &idx[i]);
        if (idx[i] > max_p) max_p = idx[i];
    }
    for (int i = 0; i < N; i++) 
    {
        int v;
        scanf("%d", &v);
        set_c(i, v);
    }
    for (int i = 0; i < N; i++) scanf("%d", &cycle[i]);
    for (int i = 0; i < N; i++)
    {
        int from = cycle[i];
        int to = cycle[(i + 1) % N];
        perm[from] = to;
    }
    z[0] = 0;
    for (int i = 1; i < N; i++) z[i] = perm[z[i - 1]];

    int k = 1, next_limit = 255, pos = 0, q, r, s, pow = 1;
    for (int p = 16; p <= max_p; p++)
    {
        q = 0;
        r = 0;
        s = 0;
        int curr_pow = pow;
        for (int i = 0; i < k; i++)
        {
            q += (curr_pow * z[pos % N]);
            pos++;
            curr_pow /= 16;
        }
        curr_pow = pow;
        for (int i = 0; i < k; i++)
        {
            r += (curr_pow * z[pos % N]);
            pos++;
            curr_pow /= 16;
        }
        curr_pow = pow;
        for (int i = 0; i < k; i++)
        {
            s += (curr_pow * z[pos % N]);
            pos++;
            curr_pow /= 16;
        }
        int c_q = get_c(q);
        int c_r = get_c(r);
        int c_s = get_c(s);
        int c_p = (c_q * c_r + c_s) % 4;
        set_c(p, c_p);
        if (p == next_limit)
        {
            pow *= 16;
            k++;
            next_limit *= 16;
            next_limit += 15;
        }
    }
    for (int i = 0; i < N; i++) printf("%d ", get_c(idx[i]));
    printf("\n");
    return 0;
}