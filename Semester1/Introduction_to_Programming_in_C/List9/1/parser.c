#include "parser.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int parse_args(char **argv, int argc, bool *reverse, bool *sorted, char **contains, int *head, int *tail)
{
    for (int i = 1; i < argc; i++) 
    {
        char *current_flag = argv[i];
        if (*current_flag != '-') return 1;
        current_flag++;
        // Long option
        if (*current_flag == '-')
        {
            current_flag++;
            int flag_size = strlen(current_flag);
            if (!flag_size) return 1;
            if (strcmp(current_flag, "reverse") == 0)
            {
                if (*reverse) return 1;
                *reverse = 1;
            }
            else if (strcmp(current_flag, "sorted") == 0)
            {
                if (*sorted) return 1;
                *sorted = 1;
            }
            else if (strcmp(current_flag, "contains") == 0)
            {
                if (*contains != NULL) return 1;
                if (i + 1 >= argc) return 1;
                *contains = argv[i + 1];
                i++;
            }
            else if (strcmp(current_flag, "head") == 0 || strcmp(current_flag, "tail") == 0)
            {
                bool to_head = 0;
                if (strcmp(current_flag, "head") == 0) to_head = 1;
                if (*head != -1 || *tail != -1) return 1;
                if (i + 1 >= argc) return 1;
                i++;
                int len = strlen(argv[i]);
                for (int j = 0; j < len; j++)
                    if (!isdigit(argv[i][j])) return 1;
                if (to_head) *head = atoi(argv[i]);
                else *tail = atoi(argv[i]);
            }
            else return 1;
        }
        // Short option
        else
        {
            int flag_size = strlen(current_flag);
            if (!flag_size) return 1;
            for (int j = 0; j < flag_size; j++)
            {
                if (current_flag[j] == 'r')
                {
                    if (*reverse) return 1;
                    *reverse = 1;
                }
                else if (current_flag[j] == 's')
                {
                    if (*sorted) return 1;
                    *sorted = 1;
                }
                else if (current_flag[j] == 'c')
                {
                    if (*contains != NULL) return 1;
                    j++;
                    if (strlen(current_flag + j) == 0) return 1;
                    *contains = current_flag + j;
                    j = flag_size;
                }
                else if (current_flag[j] == 'h' || current_flag[j] == 't')
                {
                    bool to_head = 0;
                    if (current_flag[j] == 'h') to_head = 1;
                    if (*head != -1 || *tail != -1) return 1;
                    j++;
                    char num[10];
                    int num_idx = 0;
                    while (isdigit(current_flag[j])) num[num_idx++] = current_flag[j++];
                    j--;
                    num[num_idx] = '\0';
                    if (num_idx == 0) return 1;
                    if (to_head) *head = atoi(num);
                    else *tail = atoi(num);
                }
                else return 1;
            }
        }
    }
    return 0;
}