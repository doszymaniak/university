#include <stdio.h>
#include <ctype.h>

void copy(const char *from, char *to)
{
    while (*from) *to++ = *from++;
    *to = '\0';
}

void set(char *sequence, char character)
{
    while (*sequence) *sequence++ = character;
}

int length(const char *sequence)
{
    int len = 0;
    while (*sequence) 
    {
        len++;
        sequence++;
    }
    return len;
}

void swapcase(char *sequence)
{
    while (*sequence)
    {
        if (!isalpha(*sequence))
        {
            sequence++;
            continue;
        }
        if (islower(*sequence)) *sequence = toupper(*sequence);
        else *sequence = tolower(*sequence);
        sequence++;
    }
}

// Returns the value depending on the comparison:
// -1 - the first sequence is smaller
// 0 - both sequences are equal
// 1 - the second sequence is smaller
int compare(const char *seq1, const char *seq2)
{
    while (*seq1 && *seq2)
    {
        if (*seq1 < *seq2) return -1;
        else if (*seq1 > *seq2) return 1;
        seq1++;
        seq2++;
    }
    if (!*seq1 && !*seq2) return 0;
    if (!*seq1) return -1;
    return 1;
}

int main()
{
    printf("SAMPLE SEQUENCE:\n");
    char test_seq[] = "aBcdeFghijKLmnop";
    puts(test_seq);
    
    printf("\nTEST OF 'COPY'\n");
    char test_cp[100];
    copy(test_seq, test_cp);
    printf("Copied into another array:\n");
    puts(test_cp);
    
    printf("\nTEST OF 'SET'\n");
    char test_set[100];
    copy(test_seq, test_set);
    printf("After setting all characters to 'a': ");
    set(test_set, 'a');
    puts(test_set);
    
    printf("\nTEST OF 'LENGTH'\n");
    printf("Length: %d\n", length(test_seq));
    
    printf("\nTEST OF 'SWAPCASE'\n");
    char test_swap[100];
    copy(test_seq, test_swap);
    swapcase(test_swap);
    printf("After swapping the letter cases: ");
    puts(test_swap);
    
    printf("\nTEST OF 'COMPARE'\n");
    printf("Second sequence to compare: ");
    char test_comp[] = "ghjhjujgr";
    puts(test_comp);
    printf("Result of 'compare': %d\n", compare(test_seq, test_comp));
    return 0;
}