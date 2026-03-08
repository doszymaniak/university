#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>

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
    scanf("%d", &x);
    print_binary(x);
    uint32_t xor1 = (x ^ x << 16) >> 16;
    uint32_t xor2 = (xor1 ^ xor1 << 8) >> 8;
    uint32_t xor3 = (xor2 ^ xor2 << 4) >> 4;
    uint32_t xor4 = (xor3 ^ xor3 << 2) >> 2;
    uint32_t xor5 = (xor4 ^ xor4 << 1) >> 1;
    if (xor5 & 1) printf("ODD\n");
    else printf("EVEN\n");
    return 0;
}