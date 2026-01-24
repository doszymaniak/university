#include "structure.h"
#include <stdlib.h>
#include <string.h>

struct structure {
    struct item **array;
    int array_n;
    int array_size;
};

Structure *structure_init()
{
    Structure *s = malloc(sizeof(struct structure));
    if (!s) return NULL;
    s->array = malloc(10 * sizeof(struct item *));
    if (!s->array) 
    {
        free(s);
        return NULL;
    }
    s->array_size = 10;
    s->array_n = 0;
    return s;
}

int insert(Structure *s, struct item *elem)
{
    int start = 0, end = s->array_n - 1;
    while (start <= end)
    {
        int mid = (start + end) / 2;
        if (strcmp(s->array[mid]->line, elem->line) <= 0) start = mid + 1;
        else end = mid - 1;
    }
    int pos = start;
    if (s->array_n + 1 > s->array_size)
    {
        int new_array_size = (s->array_size == 0 ? 2 : s->array_size * 2);
        struct item **tmp = realloc(s->array, sizeof(struct item *) * new_array_size);
        if (!tmp) return 3;
        s->array = tmp;
        s->array_size = new_array_size;
    }
    for (int i = s->array_n; i > pos; i--) s->array[i] = s->array[i - 1];
    s->array[pos] = elem;
    s->array_n++;
    return 0;
}

struct item *find_and_delete(Structure *s)
{
    if (s->array_n == 0) return NULL;
    struct item *result = s->array[0];
    for (int i = 0; i < s->array_n - 1; i++) 
        s->array[i] = s->array[i + 1];
    s->array_n--;
    return result;
}

void structure_destroy(Structure *s)
{
    if (!s) return;
    for (int i = 0; i < s->array_n; i++)
    {
        if (fclose(s->array[i]->f) != 0) fprintf(stderr, "Failed to close file!\n");
        free(s->array[i]->line);
        free(s->array[i]);
    }
    free(s->array);
    free(s);
}

int is_empty(Structure *s)
{
    if (s->array_n) return 0;
    return 1;
}