#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define N 1000

void print_partition(int partition[], int n, int subset_cnt)
{
    for (int i = 1; i <= subset_cnt; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            if (partition[j] == i) printf("%d ", j);
        }
        if (i != subset_cnt) printf("| ");
    }
    printf("\n");
}

void generate_partitions(int partition[], int n, int curr_el, int subset_cnt)
{
    if (curr_el > n)
    {
        print_partition(partition, n, subset_cnt);
        return;
    }
    // Add the current element to each existing subset 
    for (int i = 1; i <= subset_cnt; i++)
    {
        partition[curr_el] = i;
        generate_partitions(partition, n, curr_el + 1, subset_cnt);
    }
    // Create a new subset containing only the current element
    partition[curr_el] = subset_cnt + 1;
    generate_partitions(partition, n, curr_el + 1, subset_cnt + 1);
}

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("INVALID NUMBER OF ARGUMENTS!\n");
        return 1;
    }
    for (int i = 0; argv[1][i] != '\0'; i++)
    {
        if (!isdigit(argv[1][i]))
        {
            printf("THE ARGUMENT MUST BE A POSITIVE INTEGER!\n");
            return 1;
        }
    }
    int n = atoi(argv[1]);
    if (n == 0)
    {
        printf("THE ARGUMENT MUST BE POSITIVE!\n");
        return 1;
    }
    int partition[n + 1];
    partition[1] = 1;
    generate_partitions(partition, n, 2, 1);
    return 0;
}