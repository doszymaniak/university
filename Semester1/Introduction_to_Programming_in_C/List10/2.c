#include <stdio.h>
#include <stdlib.h>
#define MAX_N 100005

struct Node {
    int *children;
    int children_n;
    int children_size;
    int parent_idx;
    long long parent_edge;
};

struct Node *nodes;
int nodes_n = 0;

int add_nodes(int idx, int k)
{
    if (nodes[idx].children_n + k > nodes[idx].children_size)
    {
        int *tmp = realloc(nodes[idx].children, sizeof(int) * (nodes[idx].children_size + k));
        if (!tmp) return 1;
        nodes[idx].children = tmp;
        nodes[idx].children_size += k;
    }
    for (int i = 0; i < k; i++)
    {
        nodes[idx].children[nodes[idx].children_n] = nodes_n;
        nodes[idx].children_n++;
        nodes[nodes_n].children = NULL;
        nodes[nodes_n].children_n = 0;
        nodes[nodes_n].children_size = 0;
        nodes[nodes_n].parent_idx = idx;
        nodes[nodes_n].parent_edge = 0;
        nodes_n++;
    }
    return 0;
}

void delete_subtree(int idx)
{
    for (int i = 0; i < nodes[idx].children_n; i++) delete_subtree(nodes[idx].children[i]);
    free(nodes[idx].children);
    nodes[idx].children = NULL;
    nodes[idx].children_n = 0;
    nodes[idx].children_size = 0;
    nodes[idx].parent_edge = 0;
    nodes[idx].parent_idx = -1;
}

void remove_child(int parent_idx, int child_idx)
{
    for (int i = 0; i < nodes[parent_idx].children_n; i++)
    {
        if (nodes[parent_idx].children[i] == child_idx)
        {
            for (int j = i; j < nodes[parent_idx].children_n - 1; j++)
                nodes[parent_idx].children[j] = nodes[parent_idx].children[j + 1];
            nodes[parent_idx].children_n--;
            return;
        }
    }
}

void make_good(int idx)
{
    if (idx == 0) return;
    if (nodes[idx].children_n != 1) return;
    int parent = nodes[idx].parent_idx;
    if (parent == -1) return;
    int new_child = nodes[idx].children[0];
    remove_child(parent, idx);
    nodes[new_child].parent_idx = parent;
    nodes[new_child].parent_edge += nodes[idx].parent_edge;
    if (nodes[parent].children_n + 1 > nodes[parent].children_size)
    {
        int new_size = nodes[parent].children_size + 5;
        int *tmp = realloc(nodes[parent].children, new_size * sizeof(int));
        if (!tmp) return;
        nodes[parent].children = tmp;
        nodes[parent].children_size = new_size;
    }
    nodes[parent].children[nodes[parent].children_n] = new_child;
    nodes[parent].children_n++;
}

void initialize()
{
    nodes_n = 2;
    nodes[0].children = malloc(sizeof(int));
    nodes[0].children[0] = 1;
    nodes[0].children_n = 1;
    nodes[0].children_size = 1;
    nodes[0].parent_idx = -1;
    nodes[0].parent_edge = 0;

    nodes[1].children = NULL;
    nodes[1].children_n = 0;
    nodes[1].children_size = 0;
    nodes[1].parent_idx = 0;
    nodes[1].parent_edge = 0;
}

int comp(const void *a, const void *b)
{
    return *(int*)a - *(int*)b;
}

void dfs(int idx, long long distance)
{
    if (idx != 0) printf("%d %lld\n", idx, distance);
    if (nodes[idx].children_n > 0)
        qsort(nodes[idx].children, nodes[idx].children_n, sizeof(int), comp);
    for (int i = 0; i < nodes[idx].children_n; i++)
    {
        int child = nodes[idx].children[i];
        dfs(child, nodes[child].parent_edge + distance);
    }
}

int main()
{
    nodes = malloc(sizeof(struct Node) * MAX_N);
    if (!nodes) return 1;
    initialize();
    char op;
    while (scanf(" %c", &op) > 0)
    {
        if (op == 'f')
        {
            int idx, k;
            scanf("%d %d", &idx, &k);
            if (add_nodes(idx, k)) return 1;
        }
        else if (op == 'g')
        {
            int idx;
            long long x;
            scanf("%d %lld", &idx, &x);
            nodes[idx].parent_edge += x;
        }
        else
        {
            int idx;
            scanf("%d", &idx);
            int parent_idx = nodes[idx].parent_idx;
            remove_child(parent_idx, idx);
            delete_subtree(idx);
            make_good(parent_idx);
        }
    }
    dfs(0, 0);
    free(nodes);
    return 0;
}