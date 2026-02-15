#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX_COLOR 100007

struct sock {
    int left;
    int right;
    int prize;
    int distance;
    bool sold;
};

struct sock **colors[MAX_COLOR];
int colors_size[MAX_COLOR];
int colors_n[MAX_COLOR];
int first_not_sold[MAX_COLOR];
int n;

void add_to_color(struct sock *curr, int color)
{
    if (colors_n[color] + 1 > colors_size[color])
    {
        int new_size = 0;
        if (colors_size[color] == 0) new_size = 10;
        else new_size = colors_size[color] * 2;
        struct sock **tmp = realloc(colors[color], new_size * sizeof(struct sock *));
        if (!tmp) return;
        colors_size[color] = new_size;
        colors[color] = tmp;
    }
    colors[color][colors_n[color]] = curr;
    colors_n[color]++;
}

int comp(const void *a, const void *b)
{
    struct sock *sock1 = *(struct sock **)a;
    struct sock *sock2 = *(struct sock **)b;
    if (sock1->prize < sock2->prize) return -1;
    if (sock1->prize > sock2->prize) return 1;
    if (sock1->distance < sock2->distance) return -1;
    return 1;
}

void sort_colors()
{
    for (int i = 0; i < MAX_COLOR; i++)
    {
        if (colors_n[i] == 0) continue;
        qsort(colors[i], colors_n[i], sizeof(struct sock *), comp);
    }
}

int main()
{
    scanf("%d", &n);
    for (int i = 0; i < n; i++)
    {
        struct sock *curr = malloc(sizeof(struct sock));
        if (!curr) return 1;
        int prize, left, right;
        scanf("%d %d %d", &prize, &left, &right);
        curr->prize = prize;
        curr->left = left;
        curr->right = right;
        curr->distance = i + 1;
        curr->sold = 0;
        add_to_color(curr, left);
        if (left == right) continue;
        add_to_color(curr, right);
    }
    sort_colors();
    int q;
    scanf("%d", &q);
    while (q--)
    {
        int color;
        scanf("%d", &color);
        int idx = first_not_sold[color];
        while (idx < colors_n[color] && colors[color][idx]->sold) idx++;
        first_not_sold[color] = idx;
        if (idx < colors_n[color])
        {
            printf("%d ", colors[color][idx]->prize);
            colors[color][idx]->sold = 1;
            first_not_sold[color] = idx + 1;
        }
        else printf("%d ", -1);
    }
    printf("\n");
    return 0;
}