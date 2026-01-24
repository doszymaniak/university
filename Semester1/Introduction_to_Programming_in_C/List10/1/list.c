#include "structure.h"
#include <string.h>
#include <stdlib.h>

struct structure {
    struct item *head;
};

Structure *structure_init()
{
    struct structure *s = malloc(sizeof(struct structure));
    if (!s) return NULL;
    s->head = NULL;
    return s;
}

int insert(Structure *s, struct item *elem)
{
    if (!s->head || strcmp(elem->line, s->head->line) <= 0)
    {
        elem->next = s->head;
        s->head = elem;
        return 0;
    }
    struct item *prev = s->head;
    struct item *curr = s->head->next;
    while (curr != NULL && strcmp(elem->line, curr->line) > 0)
    {
        prev = curr;
        curr = prev->next;
    }
    elem->next = curr;
    prev->next = elem;
    return 0;
}

struct item *find_and_delete(Structure *s)
{
    if (!s->head) return NULL;
    struct item *elem = s->head;
    s->head = elem->next;
    elem->next = NULL;
    return elem;
}

int is_empty(Structure *s)
{
    if (s->head != NULL) return 0;
    return 1;
}

void structure_destroy(Structure *s)
{
    if (s == NULL) return;
    struct item *curr = s->head;
    while (curr) 
    {
        struct item *next = curr->next;
        if (curr->line) free(curr->line);
        if (curr->f)
        {
            if (fclose(curr->f) != 0) fprintf(stderr, "Failed to close file!\n");
        }
        free(curr);
        curr = next;
    }
    free(s);
}