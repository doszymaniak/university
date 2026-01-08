#include <stdio.h>

long long get_tree_variant(int y, int x, int n)
{
    if (x == 0 && y == 0) return 0;
    if (x == 1 && y == 0) return 3;
    if (x == 0 && y == 1) return 2;
    if (x == 1 && y == 1) return 1;
    long long half = (1 << (n - 1));
    long long to_add = 0;
    if (x >= half && y < half) to_add = 3 * half * half;
    else if (x < half && y >= half) to_add = 2 * (half * half);
    else if (x >= half && y >= half) to_add = half * half;
    int new_y = (y - half < 0 ? y : y - half);
    int new_x = (x - half < 0 ? x : x - half);
    return get_tree_variant(new_y, new_x, n - 1) + to_add;
}

struct coordinates {
    int x;
    int y;
};

struct coordinates get_tree_coordinates(int n, long long tree)
{
    if (tree == 0)
    {
        struct coordinates c = {0, 0};
        return c;
    }
    if (tree == 1)
    {
        struct coordinates c = {1, 1};
        return c;
    }
    if (tree == 2)
    {
        struct coordinates c = {1, 0};
        return c;
    }
    if (tree == 3)
    {
        struct coordinates c = {0, 1};
        return c;
    }
    long long half = (1 << (n - 1));
    long long quarter = half * half;
    if (tree < quarter) return get_tree_coordinates(n - 1, tree);
    if (tree < 2 * quarter)
    {
        struct coordinates c = get_tree_coordinates(n - 1, tree - quarter);
        c.x += half;
        c.y += half;
        return c;
    }
    if (tree < 3 * quarter)
    {
        struct coordinates c = get_tree_coordinates(n - 1, tree - (2 * quarter));
        c.x += half;
        return c;
    }
    struct coordinates c = get_tree_coordinates(n - 1, tree - (3 * quarter));
    c.y += half;
    return c;
}

int main()
{
    int n, q;
    scanf("%d%d", &n, &q);
    while (q--)
    {
        char c;
        scanf(" %c", &c);
        if (c == 'x')
        {
            int y, x;
            scanf("%d%d", &y, &x);
            printf("%lld\n", get_tree_variant(y, x, n));
        }
        else if (c == 'o')
        {
            long long tree;
            scanf("%lld", &tree);
            struct coordinates res = get_tree_coordinates(n, tree);
            printf("%d %d\n", res.x, res.y);
        }
    } 
    return 0;
}