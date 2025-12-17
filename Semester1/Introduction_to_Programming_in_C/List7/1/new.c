#include <stdio.h>
#include "module.h"

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("NO ARGUMENTS PROVIDED!\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 0)
    {
        printf("THE NUMBER OF WORDS SHOULD BE GREATER THAN OR EQUAL TO ZERO!\n");
        return 1;
    }
    if (argc - 2 != n)
    {
        printf("THE NUMBER OF WORDS DOES NOT MATCH THE SPECIFIED VALUE!\n");
        return 1;
    }
    if (n == 0)
    {
        printf("NO WORDS TO ANALYZE\n");
        return 0;
    }
    int *cnt = calculate_stats(n, argv + 2, 1);
    print_stats(n, argv + 2, cnt, 1);
    cnt = calculate_stats(n, argv + 2, 2);
    print_stats(n, argv + 2, cnt, 2);
    return 0;
}