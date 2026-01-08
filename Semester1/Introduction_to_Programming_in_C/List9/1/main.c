#include <stdio.h>
#include "fgetline.h"
#include <stdbool.h>
#include "parser.h"
#include <string.h>
#include <stdlib.h>

struct line_struct {
    char *line;
    int len;
};

void print_line(char *line)
{
    if (!line) return;
    while (*line) putchar(*line++);
}

void free_lines(struct line_struct *lines, int lines_n)
{
    for (int i = 0; i < lines_n; i++) free(lines[i].line);
    free(lines);
}

bool contains_pattern(char *line, char *pattern)
{
    int line_len = strlen(line);
    int pattern_len = strlen(pattern);
    for (int i = 0; i <= line_len - pattern_len; i++)
    {
        int j;
        for (j = 0; j < pattern_len; j++)
        {
            if (line[i + j] != pattern[j]) break;
        }
        if (j == pattern_len) return 1;
    }
    return 0;
}

int comp(const void *a, const void *b)
{
    const struct line_struct *a_s = a;
    const struct line_struct *b_s = b;
    return a_s->len - b_s->len;
}

int main(int argc, char **argv)
{
    bool reverse = 0, sorted = 0;
    char *contains = NULL;
    int head = -1, tail = -1;
    int status = parse_args(argv, argc, &reverse, &sorted, &contains, &head, &tail);
    if (status) return 1;
    if (!contains && !reverse && !sorted && head == -1 && tail == -1)
    {
        while (1)
        {
            long memory = 0;
            char *line = fgetline(stdin, &memory);
            if (!line) break;
            print_line(line);
            free(line);
        }
        return 0;
    }
    if (!reverse && !sorted && tail == -1)
    {
        int line_cnt = 0;
        while (1)
        {
            long memory = 0;
            char *line = fgetline(stdin, &memory);
            if (!line) break;
            if (contains != NULL)
            {
                if (contains_pattern(line, contains)) 
                {
                    line_cnt++;
                    print_line(line);
                    free(line);
                    if (line_cnt == head) break;
                    else continue;
                }
            }
            else if (head != -1)
            {
                if (line_cnt < head)
                {
                    line_cnt++;
                    print_line(line);
                    free(line);
                    if (line_cnt == head) break;
                }
            }
        }
        return 0;
    }
    int lines_n = 0;
    int lines_size = 16;
    struct line_struct *lines = malloc(sizeof(struct line_struct) * lines_size);
    if (!lines) return 1;
    while (1)
    {
        long memory = 0;
        char *line = fgetline(stdin, &memory);
        if (!line) break;
        if (contains != NULL)
        {
            if (!contains_pattern(line, contains)) continue;
        }
        if (lines_n == lines_size)
        {
            struct line_struct *tmp = realloc(lines, sizeof(struct line_struct) * lines_size * 2);
            if (!tmp) break;
            lines = tmp;
            lines_size *= 2;
        }
        lines[lines_n].line = line;
        lines[lines_n].len = strlen(line);
        lines_n++;
    }
    if (sorted) qsort(lines, lines_n, sizeof(lines[0]), comp);
    if (reverse)
    {
        if (head != -1)
        {
            for (int i = lines_n - 1; i >= 0 && lines_n - 1 - i < head; i--) print_line(lines[i].line);
        }
        else if (tail != -1)
        {
            for (int i = tail - 1; i >= 0; i--) print_line(lines[i].line);
        }
        else
        {
            for (int i = lines_n - 1; i >= 0; i--) print_line(lines[i].line);
        }
        free_lines(lines, lines_n);
        return 0;
    }
    if (head != -1)
    {
        int end = head;
        if (head > lines_n) head = lines_n;
        for (int i = 0; i < end; i++) print_line(lines[i].line);
        free_lines(lines, lines_n);
        return 0;
    }
    if (tail != -1)
    {
        int start = lines_n - tail;
        if (start < 0) start = 0;
        for (int i = start; i < lines_n; i++) print_line(lines[i].line);
        free_lines(lines, lines_n);
        return 0;
    }
    for (int i = 0; i < lines_n; i++) print_line(lines[i].line); 
    free_lines(lines, lines_n);
    return 0;
}