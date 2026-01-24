#ifndef STRUCTURE_H
#define STRUCTURE_H

#include <stdio.h>

struct item {
    char *line;
    int line_len;
    int line_size;
    FILE *f;
    struct item *next;
};

typedef struct structure Structure;

Structure *structure_init();
void structure_destroy(Structure *s);
int insert(Structure *s, struct item *elem);
struct item *find_and_delete(Structure *s);
int is_empty(Structure *s);

#endif