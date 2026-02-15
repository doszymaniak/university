#ifndef QUADTREE_H
#define QUADTREE_H

#include <stdbool.h>
#include <stdio.h>

#define uc unsigned char

struct node {
    int img_size;
    int width;
    int height;

    uc red, green, blue;

    // 0 - internal node
    // 1 - leaf inside image
    // 2 - leaf outside image
    uc state;

    struct node *child1;
    struct node *child2;
    struct node *child3;
    struct node *child4;
};

void free_tree(struct node *tree);
bool is_valid_tree(struct node *tree);
void print_tree(FILE *f, struct node *tree, int depth);
struct node *create_internal(int img_size, int width, int height);
struct node *create_leaf_inside_image(int img_size, int width, int height, uc red, uc green, uc blue);
struct node *create_leaf_outside_image(int img_size);
struct node *load_tree_from_file(FILE *f);

#endif