// This program demonstrates a double-buffered merge sort
#include <stdio.h>

void merge_sort(int *curr, int *res, int len)
{
    if (len == 1)
    {
        *res = *curr;
        return;
    }
    int mid = len / 2;

    // In this call, we save the result in 'res', and so in lower-level calls
    // 'res' must be the source of data, while 'curr' becomes the output buffer
    // Otherwise, merging would read data from unsorted fragments
    // The idea is that 'curr' should contain two sorted halves ready to be merged
    // in the final step
    merge_sort(res, curr, mid);
    merge_sort(res + mid, curr + mid, len - mid);

    // Merge the two sorted halves
    int idx1 = 0, idx2 = mid, idx_res = 0;
    while (idx1 < mid && idx2 < len)
    {
        if (curr[idx1] <= curr[idx2]) res[idx_res++] = curr[idx1++];
        else res[idx_res++] = curr[idx2++];
    }

    // If any elements remain in either half, append them to the result
    while (idx1 < mid) res[idx_res++] = curr[idx1++];
    while (idx2 < len) res[idx_res++] = curr[idx2++];
}

void merge_sort_aux(int len, int *arr)
{
    int buffer[len];
    for (int i = 0; i < len; i++) buffer[i] = arr[i];
    merge_sort(buffer, arr, len);
}

int main()
{
    int n;
    printf("Enter the number of elements:\n");
    if (scanf("%d", &n) != 1 || n < 0)
    {
        printf("Invalid number of elements!\n");
        return 1;
    }
    if (n == 0)
    {
        printf("No elements to sort\n");
        return 0;
    }
    int arr[n];
    printf("Enter the elements:\n");
    for (int i = 0; i < n; i++) 
    {
        if (scanf("%d", &arr[i]) != 1)
        {
            printf("Invalid element!\n");
            return 1;
        }
    }

    merge_sort_aux(n, arr);
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}