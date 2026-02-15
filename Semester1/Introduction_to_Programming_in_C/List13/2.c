#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

int courses[300007];
bool solved[300007];
int *positions[300007];
int positions_size[300007];
int courses_solved[300007];
int next_pos[300007];

int main()
{
    int n, q;
    scanf("%d %d", &n, &q);
    int total = 0, unsolved = 0, solved_globally = 0;
    while (q--)
    {
        int command;
        scanf(" %d", &command);
        if (command == 1)
        {
            int k;
            scanf(" %d", &k);
            courses[total] = k;
            unsolved++;
            int *tmp = realloc(positions[k], (positions_size[k] + 1) * sizeof(int));
            if (!tmp) return 1;
            positions[k] = tmp;
            positions[k][positions_size[k]] = total;
            positions_size[k]++;
            total++;
        }
        else if (command == 2)
        {
            int k, x;
            scanf(" %d %d", &k, &x);
            int curr_pos = next_pos[k];
            while (courses_solved[k] < x && curr_pos < positions_size[k])
            {
                if (!solved[positions[k][curr_pos]])
                {
                    solved[positions[k][curr_pos]] = 1;
                    unsolved--;
                    courses_solved[k]++;
                }
                curr_pos++;
            }
            next_pos[k] = curr_pos;
        }
        else
        {
            int x;
            scanf(" %d", &x);
            int curr_pos = 0;
            if (x < solved_globally) x = 0;
            else 
            {
                curr_pos = solved_globally;
                x -= curr_pos;
            }
            while (x && curr_pos < total)
            {
                if (!solved[curr_pos])
                {
                    solved[curr_pos] = 1;
                    unsolved--;
                    courses_solved[courses[curr_pos]]++;
                    solved_globally++;
                }
                x--;
                curr_pos++;
            }
        }
        printf("%d\n", unsolved);
    }
    return 0;
}