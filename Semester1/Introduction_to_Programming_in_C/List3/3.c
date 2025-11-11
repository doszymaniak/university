#include <stdio.h>
#include <stdbool.h>

#define N 1000

char a[N][N];
int heights[N];
int n, m;

void place_brick()
{
    int col = 1;
    while (col < m - 1 && heights[col + 1] >= heights[col]) col++;
    while (col > 0 && heights[col - 1] >= heights[col]) col--;
    if (heights[col] < 0) return;
    a[heights[col]][col] = '*';
    heights[col]--;
}

int main()
{
    int bricks = 0, to_fill = 0;
    scanf("%d%d%d", &m, &n, &bricks);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) 
        {
            scanf(" %c", &a[i][j]);
            if (a[i][j] == '.') to_fill++;
        }
    }
    if (to_fill <= bricks)
    {
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                if (a[i][j] == '.') printf("%c", '*');
                else printf("%c", a[i][j]);
            }
            printf("\n");
        }
        return 0;
    }
    for (int j = 0; j < m; j++)
    {
        int i = 0;
        while (i < n && a[i][j] == '.') i++;
        heights[j] = i - 1;
    }
    while (bricks--) place_brick();
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++) printf("%c", a[i][j]);
        printf("\n");
    }
    return 0;
}