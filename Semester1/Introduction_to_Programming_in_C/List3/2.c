#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORD_LEN 50

// Converts all letters in a word to lowercase
// Used when 'which_fun' = 1
void to_lowercase(char *word)
{
    for (int i = 0; word[i] != '\0'; i++) word[i] = tolower(word[i]);
}

// Converts every letter into 'a' or 'A' while keeping the case 
// Used when 'which_fun' = 2
void to_a_letters(char *word)
{
    for (int i = 0; word[i] != '\0'; i++)
    {
        if (word[i] >= 'a' && word[i] <= 'z') word[i] = 'a';
        else word[i] = 'A';
    }
}

// The 'which_fun' parameter indicates how the words will be compared: 
// 1 - ignores the case of the letters
// 2 - considers the case of the letters
void calculate_stats(int n, char *words[], int which_fun)
{
    int cnt[n];
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
}

int main(int argc, char *argv[])
{
    if (argc <= 1)
    {
        printf("NO ARGUMENTS PROVIDED!\n");
        return 1;
    }
    int n = atoi(argv[1]);
    if (n < 0)
    {
        printf("THE NUMBER OF WORDS SHOULD BE GREATER THAN OR EQUAL TO ZERO!\n");
        return 1;
    }
    if (argc - 2 != n)
    {
        printf("THE NUMBER OF WORDS DOES NOT MATCH THE SPECIFIED VALUE!\n");
        return 1;
    }
    if (n == 0)
    {
        printf("NO WORDS TO ANALYZE\n");
        return 0;
    }
    calculate_stats(n, argv + 2, 1);
    calculate_stats(n, argv + 2, 2);
    return 0;
}