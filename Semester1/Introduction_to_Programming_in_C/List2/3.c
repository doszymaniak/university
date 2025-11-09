#include <stdio.h>
#include <stdbool.h>

int main()
{
    int n, q;
    scanf("%d", &n);
    int a[n], cycle_num[n], cycle_size[n], cycle_start[n], cycles[n], pos_in_cycle[n];
    bool visited[n];
    for (int i = 0; i < n; i++) 
    {
        scanf("%d", &a[i]);
        visited[i] = false;
    }
    int cycle_idx = 0, curr_cycle_num = 0;
    for (int i = 0; i < n; i++)
    {
        int curr_el_idx = i, curr_size = 0;
        if (visited[curr_el_idx]) continue;
        cycle_start[curr_cycle_num] = cycle_idx;
        while (1)
        {
            if (visited[curr_el_idx])
            {
                cycle_size[curr_cycle_num] = curr_size;
                curr_cycle_num++;
                break;
            }
            visited[curr_el_idx] = true;
            cycle_num[curr_el_idx] = curr_cycle_num;
            cycles[cycle_idx] = a[curr_el_idx];
            pos_in_cycle[curr_el_idx] = curr_size;
            curr_el_idx = a[curr_el_idx] - 1;
            cycle_idx++;
            curr_size++;
        }
    }
    int idx_of_val[n + 1];
    for (int i = 0; i < n; i++) idx_of_val[a[i]] = i;
    scanf("%d", &q);
    while (q--)
    {
        int val, k;
        scanf("%d %d", &val, &k);
        int idx = idx_of_val[val];
        int cnum = cycle_num[idx];
        int start = cycle_start[cnum];
        int pos = pos_in_cycle[idx];
        int csize = cycle_size[cnum];
        int new_pos = ((pos + k) % csize + csize) % csize;
        printf("%d\n", cycles[start + new_pos]);
    }
    return 0;
}