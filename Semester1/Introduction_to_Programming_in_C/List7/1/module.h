#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_WORD_LEN 50

// Converts all letters in a word to lowercase
// Used when 'which_fun' = 1
void to_lowercase(char *word);

// Converts every letter into 'a' or 'A' while keeping the case 
// Used when 'which_fun' = 2
void to_a_letters(char *word);

// The 'which_fun' parameter indicates how the words will be compared: 
// 1 - ignores the case of the letters
// 2 - considers the case of the letters
int *calculate_stats(int n, char *words[], int which_fun);

void print_stats(int n, char *words[], int *cnt, int which_fun);