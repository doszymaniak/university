#include <stdio.h>
#include <string.h>

unsigned int charToInt(char c)
{
    if (c >= 'a' && c <= 'z') return c - 'a';
    else if (c >= 'A' && c <= 'Z') return c - 'A' + 26;
    else if (c >= '0' && c <= '9') return c - '0' + 52;
    else if (c == ' ') return 62;
    return 63;
}

char intToChar(unsigned int nr)
{
    if (nr <= 25) return nr + 'a';
    else if (nr >= 26 && nr <= 51) return nr + 'A' - 26;
    else if (nr >= 52 && nr <= 61) return nr + '0' - 52;
    else if (nr == 62) return ' ';
    return '.';
}

void encode(char *from, unsigned int *to)
{
    char *ptr = from;
    int group_cnt = 0, to_idx = 0;
    unsigned int curr_value = 0;
    while (*ptr != '\0')
    {
        unsigned int curr_ch = charToInt(*ptr);
        curr_value += (curr_ch << 6 * group_cnt);
        group_cnt++;
        if (group_cnt == 5)
        {
            to[to_idx] = curr_value;
            to_idx++;
            curr_value = 0;
            group_cnt = 0;
        }
        ptr++;
    }
    if (group_cnt > 0) to[to_idx] = curr_value;
}

void decode(int n, const unsigned int *from, char *to)
{
    int to_idx = 0;
    for (int i = 0; i < n; i++)
    {
        unsigned int curr_num = from[i];
        for (int j = 0; j < 5; j++)
        {
            char ch = intToChar(curr_num & 63);
            curr_num >>= 6;
            to[to_idx] = ch;
            to_idx++;
        }
    }
    to[to_idx] = '\0';
}

int main()
{
    printf("TEST WITH A LENGTH NOT DIVISIBLE BY 5:\n");
    char str1[] = "Ala ma 3 koty.";
    int n = (strlen(str1) + 4) / 5;
    unsigned int encoded1[n];
    encode(str1, encoded1);
    for (int i = 0; i < n; i++) printf("%u ", encoded1[i]);
    printf("\n");
    char decoded1[strlen(str1) + 5];
    decode(n, encoded1, decoded1);
    puts(decoded1);

    printf("\nTEST WITH A LENGTH DIVISIBLE BY 5:\n");
    char str2[] = "Test drugi";
    n = (strlen(str2) + 4) / 5;
    unsigned int encoded2[n];
    encode(str2, encoded2);
    for (int i = 0; i < n; i++) printf("%u ", encoded2[i]);
    printf("\n");
    char decoded2[strlen(str2) + 5];
    decode(n, encoded2, decoded2);
    puts(decoded2);
    return 0;
}