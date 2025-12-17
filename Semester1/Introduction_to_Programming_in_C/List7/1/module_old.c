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

int *calculate_stats(int n, char *words[], int which_fun)
{
    int *cnt = (int *)malloc(sizeof(int) * n);
    if (cnt == NULL)
    {
    	printf("MEMORY ALLOCATION ERROR\n");
    	free(cnt);
    	return NULL;
    }
    bool visited[n];
    for (int i = 0; i < n; i++) 
    {
        cnt[i] = -1;
        visited[i] = false;
    }
    for (int i = 0; i < n; i++)
    {
        if (visited[i]) continue;
        char curr_word[MAX_WORD_LEN + 1];
        strcpy(curr_word, words[i]);
        which_fun == 1 ? to_lowercase(curr_word) : to_a_letters(curr_word);
        int curr_cnt = 1;
        for (int j = i + 1; j < n; j++)
        {
            char tmp[MAX_WORD_LEN + 1];
            strcpy(tmp, words[j]);
            which_fun == 1 ? to_lowercase(tmp) : to_a_letters(tmp);
            if (strcmp(curr_word, tmp) == 0) 
            {
                visited[j] = true;
                curr_cnt++;
            }
        }
        cnt[i] = curr_cnt;
        visited[i] = true;
    }
    return cnt;
}

void print_stats(int n, char *words[], int *cnt, int which_fun)
{
    if (which_fun == 1) printf("Statistics ignoring the case of letters:\n");
    else printf("Statistics considering the case of letters:\n");
    for (int i = 0; i < n; i++)
    {
        if (cnt[i] < 0) continue;
        char curr_word[MAX_WORD_LEN + 1];
        strcpy(curr_word, words[i]);
        which_fun == 1 ? to_lowercase(curr_word) : to_a_letters(curr_word);
        printf("%s %d\n", curr_word, cnt[i]);
    }
    for (int i = 0; i < n; i++) cnt[i] = 0;
}