#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>

char name[262145];

struct stand {
    int chairs;
    int q_size;
    int head;
    char **queue;
};

void new_client(int num, struct stand *stands)
{
    struct stand *curr_stand = stands + num;
    puts(curr_stand->queue[curr_stand->head]);
    free(curr_stand->queue[curr_stand->head]);
    curr_stand->queue[curr_stand->head] = NULL;
    curr_stand->head = (curr_stand->head + 1) % curr_stand->chairs;
    curr_stand->q_size--;
}

void new_to_queue(int num, char *name, int name_len, struct stand *stands)
{
    struct stand *curr_stand = stands + num;
    if (curr_stand->q_size == curr_stand->chairs) return;
    int new_idx = (curr_stand->head + curr_stand->q_size) % (curr_stand->chairs);
    curr_stand->queue[new_idx] = malloc((name_len + 1) * sizeof(char));
    strcpy(curr_stand->queue[new_idx], name);
    curr_stand->q_size++;
}

int main()
{
    int k;
    scanf("%d", &k);
    struct stand stands[k];
    for (int i = 0; i < k; i++) 
    {
        scanf("%d", &stands[i].chairs);
        stands[i].queue = calloc(stands[i].chairs, sizeof(char *));
        stands[i].q_size = 0;
        stands[i].head = 0;
    }

    char command;
    while (1)
    {
        scanf(" %c", &command);
        if (command == 'K') break;
        if (command == 'Z')
        {
            int num;
            scanf("%d", &num);
            new_client(num - 1, stands);
        }
        else
        {
            int num;
            scanf("%s %d", name, &num);
            new_to_queue(num - 1, name, strlen(name), stands);
        }
    }

    for (int i = 0; i < k; i++)
    {
        for (int j = 0; j < stands[i].chairs; j++) 
        {
            if (stands[i].queue[j] != NULL)
                free(stands[i].queue[j]);
        }
        free(stands[i].queue);
    }
}