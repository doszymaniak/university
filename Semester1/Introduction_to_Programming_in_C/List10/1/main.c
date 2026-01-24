// Compile with the array structure:
// fgetline.h, fgetline.c, structure.h, array.c, main.c

// Compile with the linked list structure:
// fgetline.h, fgetline.c, structure.h, list.c, main.c

// The program exits with one of the following codes:
// 0 - success
// 1 - invalid arguments (no file names provided)
// 2 - file opening error
// 3 - memory allocation error
// 4 - file operation error

#include <stdio.h>
#include "fgetline.h"
#include "structure.h"
#include <stdlib.h>

void print_line(char *line)
{
    if (!line) return;
    while (*line) putchar(*line++);
}

int main(int argc, char *argv[])
{
    if (argc <= 1) 
    {
        fprintf(stderr, "No file names provided!\n");
        return 1;
    }
    Structure *s = structure_init();
    if (s == NULL)
    {
        fprintf(stderr, "Memory allocation error!\n");
        return 3;
    }
    int line_status = 0;
    for (int i = 1; i < argc; i++)
    {
        FILE *f = fopen(argv[i], "r");
        if (f == NULL)
        {
            fprintf(stderr, "Failed to open file!\n");
            structure_destroy(s);
            return 2;
        }
        struct item *elem = malloc(sizeof(struct item));
        if (!elem)
        {
            fprintf(stderr, "Memory allocation error!\n");
            structure_destroy(s);
            return 3;
        }
        int line_size = 100, line_len = 0;
        elem->line = malloc(line_size * sizeof(char));
        if (!elem->line)
        {
            fprintf(stderr, "Memory allocation error!\n");
            structure_destroy(s);
            if (fclose(f) != 0) fprintf(stderr, "Failed to close file!\n");
            free(elem);
            return 3;
        }
        char *buffer = fgetline(f, &line_len, &line_size, elem->line, &line_status);
        if (!buffer)
        {
            if (line_status == 0)
            {
                if (fclose(f) != 0) fprintf(stderr, "Failed to close file!\n");
                free(elem);
                continue;
            }
            if (line_status == 3) fprintf(stderr, "Memory allocation error!\n");
            if (line_status == 4) fprintf(stderr, "File operation error!\n");
            structure_destroy(s);
            if (fclose(f) != 0) fprintf(stderr, "Failed to close file!\n");
            free(elem);
            return line_status;
        }
        elem->line = buffer;
        elem->f = f;
        elem->line_len = line_len;
        elem->line_size = line_size;
        int status = insert(s, elem);
        if (status == 3) 
        {
            fprintf(stderr, "Memory allocation error!\n");
            structure_destroy(s);
            return 3;
        }
    }
    while (!is_empty(s))
    {
        struct item *curr = find_and_delete(s);
        print_line(curr->line);
        int line_len = 0, line_size = curr->line_size;
        char *buffer = fgetline(curr->f, &line_len, &line_size, curr->line, &line_status);
        if (!buffer)
        {
            if (line_status == 0)
            {
                if (fclose(curr->f) != 0) fprintf(stderr, "Failed to close file!\n");
                free(curr);
                continue;
            }
            if (line_status == 3) fprintf(stderr, "Memory allocation error!\n");
            if (line_status == 4) fprintf(stderr, "File operation error!\n");
            structure_destroy(s);
            free(curr);
            return line_status;
        }
        curr->line = buffer;
        curr->line_len = line_len;
        curr->line_size = line_size;
        int status = insert(s, curr);
        if (status)
        {
            fprintf(stderr, "Memory allocation error!\n");
            structure_destroy(s);
            return 3;
        }
    }
    return 0;
}