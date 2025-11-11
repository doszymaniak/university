#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#define MAX_LINE_LEN 100
#define MAX_NUM_LEN 9

int read_line(char buffer[])
{
    fgets(buffer, MAX_LINE_LEN + 1, stdin);
    int len = strlen(buffer);
    if (len > 0 && buffer[len - 1] == '\n')
    {
        buffer[len - 1] = '\0';
        len--;
    }
    return len;
}

void num_to_string(char buffer[], int len, char num_str[])
{
    int curr_idx = 0;
    for (int i = 0; i < len; i++)
    {
        if (isdigit(buffer[i]))
        {
            num_str[curr_idx] = buffer[i];
            curr_idx++;
        }
    }
    num_str[curr_idx] = '\0';
}

bool check_if_square(int num)
{
    int sqr = sqrt(num);
    if (sqr * sqr == num) return true;
    return false;
}

int main()
{
    char buffer[MAX_LINE_LEN + 1];
    int len = read_line(buffer);
    char num_str[MAX_NUM_LEN + 1];
    num_to_string(buffer, len, num_str);
    if (num_str[0] == '\0')
    {
        printf("NO DIGITS IN THE BUFFER\n");
        return 0;
    }
    int num = atoi(num_str);
    printf("THE NUMBER CHECKED IS: %d\n", num);
    if (check_if_square(num)) printf("THE NUMBER IS A PERFECT SQUARE\n");
    else printf("THE NUMBER IS NOT A PERFECT SQUARE\n");
    return 0;
}