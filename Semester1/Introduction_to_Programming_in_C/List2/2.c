#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>

#define MAX_LINE_LEN 80

// Checks if a character is in the ignored characters array
bool is_ignored(int ch, char ignored[], int n)
{
    ch = tolower(ch);
    for (int i = 0; i < n; i++)
    {
        if (ch == ignored[i]) return true;
    }
    return false;
}

// Prints the line from the buffer in reverse order
void print_line(char buffer[], int idx)
{
    for (int i = idx - 1; i >= 0; i--) printf("%c", buffer[i]);
    printf("\n");
}

// Encrypts a character using the Caesar cipher while skipping ignored characters
// The key may be positive or negative
char encrypt_char(char ch, int key, char ignored[], int n)
{
    char curr_char = tolower(ch);
    int dir = key >= 0 ? 1 : -1;
    int steps = key >= 0 ? key : -key;
    while (steps > 0)
    {
        curr_char += dir;
        if (curr_char < 'a') curr_char = 'z';
        else if (curr_char > 'z') curr_char = 'a';
        if (!is_ignored(curr_char, ignored, n)) steps--;
    }
    return islower(ch) ? curr_char : toupper(curr_char);
}

int main()
{
    int key = 3, n = 3;
    char ignored[] = {'a', 'b', 'd'}; // Characters to ignore must be lowercase
    char buffer[MAX_LINE_LEN + 1];
    int ch, idx = 0;
    while ((ch = getchar()) != EOF)
    {
        if (ch == '\n')
        {
            print_line(buffer, idx);
            idx = 0;
            continue;
        }
        if (!isalpha(ch) || is_ignored(tolower(ch), ignored, n))
        {
            buffer[idx++] = ch;
            continue;
        }
        char curr_char = encrypt_char(ch, key, ignored, n);
        buffer[idx++] = curr_char;
        if (idx == MAX_LINE_LEN - 1)
        {
            print_line(buffer, idx);
            idx = 0;
        }
    }
    if (idx > 0) print_line(buffer, idx);
    return 0;
}