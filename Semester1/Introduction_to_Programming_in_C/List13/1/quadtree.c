#include "quadtree.h"
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

void free_tree(struct node *tree)
{
    if (tree == NULL) return;
    if (tree->child1 != NULL) free_tree(tree->child1);
    if (tree->child2 != NULL) free_tree(tree->child2);
    if (tree->child3 != NULL) free_tree(tree->child3);
    if (tree->child4 != NULL) free_tree(tree->child4);
    free(tree);
}

bool is_valid_tree(struct node *tree) 
{
    if (!tree) return false;
    if (tree->state == 1 || tree->state == 2)
    {
        if (tree->child1 || tree->child2 || tree->child3 || tree->child4) return false;
        if (tree->state == 1)
        {
            if (tree->width > tree->img_size || tree->height > tree->img_size) return false;
            if (tree->width == 0 || tree->height == 0) return false;
            return true;
        }
        if (tree->width != 0 || tree->height != 0) return false;
        return true;
    }
    else if (tree->state == 0)
    {
        int half = tree->img_size / 2;
        if (!tree->child1 || !tree->child2 || !tree->child3 || !tree->child4) return false;
        if (tree->child1->img_size != half || tree->child2->img_size != half) return false;
        if (tree->child3->img_size != half || tree->child4->img_size != half) return false;
        int top_width = tree->child1->width + tree->child2->width;
        int bottom_width = tree->child3->width + tree->child4->width;
        if (top_width != tree->width) return false;
        if (bottom_width > top_width) return false;
        int left_height = tree->child1->height + tree->child3->height;
        int right_height = tree->child2->height + tree->child4->height;
        if (left_height != tree->height) return false;
        if (right_height > left_height) return false;
        if (!is_valid_tree(tree->child1)) return false;
        if (!is_valid_tree(tree->child2)) return false;
        if (!is_valid_tree(tree->child3)) return false;
        if (!is_valid_tree(tree->child4)) return false;
        return true;
    }
    else return false;
}

void print_blank(FILE *f, int depth)
{
    for (int i = 0; i < depth; i++) fprintf(f, "    ");
}

void print_tree(FILE *f, struct node *tree, int depth)
{
    if (!tree) return;
    if (depth == 0) fprintf(f, "%d %d %d\n", tree->img_size, tree->width, tree->height);
    if (tree->state == 1 || tree->state == 2)
    {
        print_blank(f, depth);
        if (tree->state == 2) fprintf(f, "-\n");
        else fprintf(f, "%02X%02X%02X\n", tree->red, tree->green, tree->blue);
        return;
    }
    print_blank(f, depth);
    fprintf(f, "{\n");
    print_tree(f, tree->child1, depth + 1);
    print_tree(f, tree->child2, depth + 1);
    print_tree(f, tree->child3, depth + 1);
    print_tree(f, tree->child4, depth + 1);
    print_blank(f, depth);
    fprintf(f, "}\n");
}

struct node *create_internal(int img_size, int width, int height)
{
    struct node *n = malloc(sizeof(struct node));
    if (!n) return NULL;
    n->img_size = img_size;
    n->width = width;
    n->height = height;
    n->state = 0;
    n->child1 = NULL;
    n->child2 = NULL;
    n->child3 = NULL;
    n->child4 = NULL;
    return n;
}

struct node *create_leaf_inside_image(int img_size, int width, int height, uc red, uc green, uc blue)
{
    struct node *n = malloc(sizeof(struct node));
    if (!n) return NULL;
    n->img_size = img_size;
    n->width = width;
    n->height = height;
    n->state = 1;
    n->child1 = NULL;
    n->child2 = NULL;
    n->child3 = NULL;
    n->child4 = NULL;
    n->red = red;
    n->green = green;
    n->blue = blue;
    return n;
}

struct node *create_leaf_outside_image(int img_size)
{
    struct node *n = malloc(sizeof(struct node));
    if (!n) return NULL;
    n->img_size = img_size;
    n->width = 0;
    n->height = 0;
    n->state = 2;
    n->red = 0;
    n->green = 0;
    n->blue = 0;
    n->child1 = NULL;
    n->child2 = NULL;
    n->child3 = NULL;
    n->child4 = NULL;
    return n;
}

char *get_line(FILE *f)
{
    int ch;
    int line_size = 20, line_len = 0;
    char *line = malloc(sizeof(char) * line_size);
    if (!line) return NULL;
    while ((ch = fgetc(f)) != EOF && ch != '\n')
    {
        if (isspace(ch)) continue;
        if (line_len + 2 > line_size)
        {
            int new_size = line_size * 2;
            char *tmp = realloc(line, new_size * sizeof(char));
            if (!tmp)
            {
                free(line);
                line_len = 0;
                return NULL;
            }
            line = tmp;
            line_size = new_size;
        }
        line[line_len] = ch;
        line_len++;
    }
    if (line_len == 0 && ch == EOF)
    {
        free(line);
        return NULL;
    }
    line[line_len] = '\0';
    return line;
}

struct node *load_tree(FILE *f, int img_size, int width, int height)
{
    char *line = get_line(f);
    if (line == NULL) return NULL;
    if (strcmp(line, "{") == 0)
    {
        struct node *n = create_internal(img_size, width, height);
        if (!n)
        {
            free(line);
            return NULL;
        }
        int half = img_size / 2;
        int w1 = (width > half) ? half : width;
        int w2 = (width > half) ? width - half : 0;
        int h1 = (height > half) ? half : height;
        int h2 = (height > half) ? height - half : 0;
        n->child1 = load_tree(f, half, w1, h1);
        n->child2 = load_tree(f, half, w2, h1);
        n->child3 = load_tree(f, half, w1, h2);
        n->child4 = load_tree(f, half, w2, h2);
        if (!n->child1 || !n->child2 || !n->child3 || !n->child4)
        {
            free_tree(n);
            free(line);
            return NULL;
        }
        free(line);
        char *end = get_line(f);
        if (!end || strcmp(end, "}") != 0)
        {
            free(end);
            free_tree(n);
            return NULL;
        }
        free(end);
        return n;
    }
    else if (strcmp(line, "-") == 0)
    {
        free(line);
        return create_leaf_outside_image(img_size);
    }
    unsigned int red, green, blue;
    if (strlen(line) == 6 && sscanf(line, "%02x%02x%02x", &red, &green, &blue) == 3)
    {
        struct node *n = create_leaf_inside_image(img_size, width, height, (uc)red, (uc)green, (uc)blue);
        free(line);
        return n;
    }
    free(line);
    return NULL;
}

struct node *load_tree_from_file(FILE *f)
{
    int img_size, width, height;
    if ((fscanf(f, " %d %d %d", &img_size, &width, &height) != 3)) return NULL;
    int ch;
    while ((ch = fgetc(f)) != '\n' && ch != EOF);
    struct node *n = load_tree(f, img_size, width, height);
    return n;
}