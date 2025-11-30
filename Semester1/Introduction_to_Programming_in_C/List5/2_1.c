// This program demonstrates a traditional merge sort technique
// using top-down recursion
#include <stdio.h>

void merge(int *arr, int left, int mid, int right)
{
    int temp[right - left + 1];
    int idx_temp = 0, idx_left = left, idx_right = mid + 1;
    while (idx_left <= mid && idx_right <= right)
    {
        if (arr[idx_left] <= arr[idx_right])
        {
            temp[idx_temp] = arr[idx_left];
            idx_left++;
        }
        else 
        {
            temp[idx_temp] = arr[idx_right];
            idx_right++;
        }
        idx_temp++;
    }
    while (idx_left <= mid)
    {
        temp[idx_temp] = arr[idx_left];
        idx_temp++;
        idx_left++;
    }
    while (idx_right <= right)
    {
        temp[idx_temp] = arr[idx_right];
        idx_temp++;
        idx_right++;
    }
    for (int i = 0; i < idx_temp; i++) arr[left + i] = temp[i];
}

void merge_sort(int *arr, int left, int right)
{
    if (left < right)
    {
        int mid = (left + right) / 2;
        merge_sort(arr, left, mid);
        merge_sort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
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

    merge_sort(arr, 0, n - 1);
    printf("Sorted array:\n");
    for (int i = 0; i < n; i++) printf("%d ", arr[i]);
    printf("\n");
    return 0;
}