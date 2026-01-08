#ifndef PARSER_H
#define PARSER_H

#include <stdbool.h>

int parse_args(char **argv, int argc, bool *reverse, bool *sorted, char **contains, int *head, int *tail);

#endif