// This program reads a sample quadtree from "file.txt"
// and prints the result in a newly created file
#include <stdio.h>
#include "quadtree.h"

int main()
{
    FILE *f = fopen("file.txt", "r");
    if (!f)
    {
        printf("Failed to open file!\n");
        return 1;
    }
    FILE *res = fopen("res.txt", "w");
    if (!res)
    {
        printf("Failed to create result file!\n");
        fclose(f);
        return 1;
    }
    struct node *tree = load_tree_from_file(f);
    if (!tree)
    {
        free_tree(tree);
        fclose(f);
        fclose(res);
        return 1;
    }
    printf("%d\n", is_valid_tree(tree) ? 1 : 0);
    print_tree(res, tree, 0);
    free_tree(tree);
    fclose(f);
    fclose(res);
    return 0;
}