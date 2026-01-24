#include "fgetline.h"
#include <stdlib.h>

char *fgetline(FILE *f, int *line_len, int *line_size, char *line, int *line_status)
{
    *line_len = 0;
    long start_pos = ftell(f);
    if (start_pos == -1) 
    {
        *line_status = 4;
        return NULL;
    }
    int ch;
    while ((ch = fgetc(f)) != EOF)
    {
        (*line_len)++;
        if (ch == '\n') break;
    }
    if (ch == EOF && ferror(f))
    {
        *line_status = 4;
        return NULL;
    }
    if (*line_len == 0 && ch == EOF) 
    {
        *line_status = 0;
        return NULL;
    }
    if (fseek(f, start_pos, SEEK_SET) != 0)
    {
        *line_status = 4;
        return NULL;
    }
    if (*line_len + 2 > *line_size)
    {
        int new_size = (*line_len + 2) * 2;
        char *tmp = realloc(line, new_size * sizeof(char));
        if (!tmp) 
        {
            *line_len = 0;
            *line_status = 3;
            return NULL;
        }
        line = tmp;
        *line_size = new_size;
    }
    for (int i = 0; i < *line_len; i++)
    {
        ch = fgetc(f);
        if (ch == EOF)
        {
            *line_status = 4;
            return NULL;
        }
        line[i] = ch;
    }
    if (*line_len == 0 || line[*line_len - 1] != '\n') 
    {
        line[*line_len] = '\n';
        (*line_len)++;
    }
    line[*line_len] = '\0';
    *line_status = 0;
    return line;
}