#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

int solve_if(uint32_t x, int i, int k)
{
    if ((1 << i) & x) x |= (1 << k);
    else x &= (~(1 << k));
    return x;
}

int solve(uint32_t x, int i, int k)
{
    int bit = ((1 << i) & x) >> i;
    x &= ~(1 << k);
    x |= (bit << k);
    return x;
}

void print_binary(uint32_t x)
{
    bool was_one = false;
    for (int i = 31; i >= 0; i--)
    {
        int bit = (x >> i) & 1;
        if (!was_one && !bit) continue;
        printf("%d ", bit);
        was_one = true;
    }
    if (!was_one) printf("%d", 0);
    printf("\n");
}

int main()
{
    uint32_t x;
    int k, i;
    scanf("%d %d %d", &x, &i, &k);
    print_binary(x);
    print_binary(solve_if(x, i, k));
    print_binary(solve(x, i, k));
    return 0;
}

/*
Examples:
1 0 1 1 1 0 0 1 - 185

Copy 7th bit to 6th:
1 1 1 1 1 0 0 1

Copy 2nd bit to 5th:
1 0 0 1 1 0 0 1
*/