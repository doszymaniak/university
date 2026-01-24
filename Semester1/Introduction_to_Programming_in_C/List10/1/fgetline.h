#ifndef FGETLINE_H
#define FGETLINE_H

#include <stdio.h>

char *fgetline(FILE *file, int *line_len, int *line_size, char *buffer, int *line_status);

#endif