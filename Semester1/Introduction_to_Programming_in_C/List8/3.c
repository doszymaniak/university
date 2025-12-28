#include <stdio.h>
#include <stdlib.h>

#define N 1007
unsigned char *sets[N];
int m[N];
int n, q;

void set_bit(unsigned char *set, int bit)
{
    int index = bit / 8, which = bit % 8;
    set[index] |= (1 << which);
}

void clear_bit(unsigned char *set, int bit)
{
    int index = bit / 8, which = bit % 8;
    set[index] &= ~(1 << which);
}

int get_bit(unsigned char *set, int bit)
{
    int index = bit / 8, which = bit % 8;
    if (set[index] & (1 << which)) return 1;
    return 0;
}

int main()
{
    scanf("%d %d", &n, &q);
    for (int i = 0; i < n; i++)
    {
        scanf("%d", &m[i]);
        sets[i] = calloc((m[i] + 7) / 8, sizeof(unsigned char));
    }
    while (q--)
    {
        char ch;
        int n_i, d;
        scanf(" %c %d %d", &ch, &n_i, &d);
        unsigned char *curr_set = sets[n_i];
        if (ch == '+')
        {
            if (d >= m[n_i]) continue;
            for (int i = 0; i < m[n_i]; i += d) set_bit(curr_set, i);
        }
        else if (ch == '-')
        {
            if (d >= m[n_i]) continue;
            for (int i = 0; i < m[n_i]; i += d) clear_bit(curr_set, i);
        }
        else
        {
            if (get_bit(curr_set, d)) printf("TAK\n");
            else printf("NIE\n");
        }
    }
    for (int i = 0; i < n; i++) free(sets[i]);
    return 0;
}