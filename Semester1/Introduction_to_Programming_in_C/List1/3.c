#include <stdio.h>
#include <stdbool.h>
#include <math.h>

#define N 1000003

bool sieve[N];
int prime_cnt[N];

void generate_sieve()
{
    sieve[0] = sieve[1] = false;
    for (int i = 2; i < N; i++) sieve[i] = true;
    for (int i = 2; i * i < N; i++)
    {
        if (sieve[i] == false) continue;
        for (int j = i * i; j < N; j += i) sieve[j] = false;
    }
}

void count_primes()
{
    int curr_cnt = 0;
    for (int i = 0; i < N; i++)
    {
        if (sieve[i]) curr_cnt++;
        prime_cnt[i] = curr_cnt;
    }
}

int main()
{
    int q;
    scanf("%d", &q);
    generate_sieve();
    count_primes();
    while (q--)
    {
        int a, b;
        scanf("%d %d", &a, &b);
        printf("%d\n", prime_cnt[b] - prime_cnt[a - 1]);
    }
    return 0;
}