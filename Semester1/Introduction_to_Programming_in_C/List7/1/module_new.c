#include "module.h"

void to_lowercase(char *word)
{
    for (int i = 0; word[i] != '\0'; i++) word[i] = tolower(word[i]);
}

void to_a_letters(char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z') word[i] = 'a';
        else word[i] = 'A';
    }
}

void memory_error()
{
    printf("MEMORY ALLOCATION ERROR\n");
}

int *calculate_stats(int n, char *words[], int which_fun)
{
    bool *visited = (bool *)malloc(sizeof(bool) * n);
    if (visited == NULL)
    {
        memory_error();
        return NULL;
    }
    int *cnt = (int *)malloc(sizeof(int) * n);
    if (cnt == NULL)
    {
        memory_error();
        free(cnt);
    	return NULL;
    }
    for (int i = 0; i < n; i++) 
    {
        cnt[i] = -1;
        visited[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[i]) continue;
        char *curr_word = (char *)malloc(sizeof(char) * MAX_WORD_LEN + 1);
        if (curr_word == NULL)
        {
            memory_error();
            free(curr_word);
            return NULL;
        }
        strcpy(curr_word, words[i]);
        which_fun == 1 ? to_lowercase(curr_word) : to_a_letters(curr_word);
        int curr_cnt = 1;
        for (int j = i + 1; j < n; j++)
        {
            char *tmp = (char *)malloc(sizeof(char) * MAX_WORD_LEN + 1);
            if (tmp == NULL)
            {
                memory_error();
                free(tmp);
                free(curr_word);
                return NULL;
            }
            strcpy(tmp, words[j]);
            which_fun == 1 ? to_lowercase(tmp) : to_a_letters(tmp);
            if (strcmp(curr_word, tmp) == 0) 
            {
                visited[j] = true;
                curr_cnt++;
            }
            free(tmp);
        }
        cnt[i] = curr_cnt;
        visited[i] = true;
        free(curr_word);
    }
    free(visited);
    return cnt;
}

void print_stats(int n, char *words[], int *cnt, int which_fun)
{
    if (which_fun == 1) printf("Statistics ignoring the case of letters:\n");
    else printf("Statistics considering the case of letters:\n");
    for (int i = 0; i < n; i++)
    {
        if (cnt[i] < 0) continue;
        char *curr_word = (char *)malloc(sizeof(char) * MAX_WORD_LEN + 1);
        if (curr_word == NULL)
        {
            memory_error();
            free(curr_word);
            return;
        }
        strcpy(curr_word, words[i]);
        which_fun == 1 ? to_lowercase(curr_word) : to_a_letters(curr_word);
        printf("%s %d\n", curr_word, cnt[i]);
        free(curr_word);
    }
    for (int i = 0; i < n; i++) cnt[i] = 0;
    free(cnt);
}