#include <stdio.h>
#include <limits.h>

int n, res;

int dfs()
{
    int children;
    scanf("%d", &children);
    if (children == 0) 
    {
        if (n == 0) res++;
        return 0;
    }
    int smallest_distance = INT_MAX;
    for (int i = 0; i < children; i++)
    {
        int distance = 1 + dfs();
        if (distance < smallest_distance) smallest_distance = distance;
    }
    if (smallest_distance == n) res++;
    return smallest_distance;
}

int main()
{
    scanf("%d", &n);
    dfs();
    printf("%d\n", res);
    return 0;
}