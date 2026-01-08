#include "fgetline.h"
#include <stdlib.h>

char *fgetline(FILE *stream, long *memory)
{
    long buffer_size = 128;
    char *buffer = malloc(buffer_size * sizeof(char));
    if (!buffer) 
    {
        if (memory) *memory = 0;
        return NULL;
    }
    int line_size = 0, ch;
    while ((ch = fgetc(stream)) != EOF)
    {
        // Ensure there is enough space for the next character and '\0'
        if (line_size + 2 > buffer_size) 
        {
            char *tmp = realloc(buffer, buffer_size * 2);
            if (!tmp)
            {
                ungetc(ch, stream);
                if (memory) *memory = buffer_size;
                if (line_size + 1 <= buffer_size) buffer[line_size] = '\0';
                else buffer[line_size - 1] = '\0';
                return buffer;
            }
            buffer = tmp;
            buffer_size *= 2;
        }
        buffer[line_size++] = ch;
        if (ch == '\n') break;
    }
    // If there's nothing in the buffer, free the memory and return NULL
    if (line_size == 0 && ch == EOF)
    {
        free(buffer);
        if (memory) *memory = 0;
        return NULL;
    }
    // Ensure that every line ends with a newline character
    if (buffer[line_size - 1] != '\n')
    {
        if (line_size + 2 > buffer_size)
        {
            char *tmp = realloc(buffer, line_size + 2);
            if (!tmp)
            {
                if (memory) *memory = buffer_size;
                buffer[line_size++] = '\0';
                return buffer;
            }
            buffer = tmp;
            buffer_size = line_size + 2;
        }
        buffer[line_size++] = '\n';
    }
    buffer[line_size] = '\0';
    if (memory) *memory = buffer_size;
    return buffer;
}