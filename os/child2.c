#include <stdio.h>
#include <stdlib.h>

int binary_search(int ar[], int start, int end, int key)
{
    if (start <= end)
    {
        int mid = (start + end) / 2;

        if (key == ar[mid])
            return mid;

        else if (key < ar[mid])
            return binary_search(ar, start, mid - 1, key);

        else
            return binary_search(ar, mid + 1, end, key);
    }

    return -1;
}

int main(int argc, char *argv[])
{
    int arr[20], size = 0, result, key;

    printf("==== Binary Search by Child Process ====\n");

    for (int i = 0; i < argc - 1; i++)
    {
        arr[i] = atoi(argv[i + 1]);
        size++;
    }

    printf("Sorted Array:\n");

    for (int i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }

    printf("\nNumber to search: ");
    scanf("%d", &key);

    result = binary_search(arr, 0, size - 1, key);

    if (result == -1)
    {
        printf("Number not found\n");
    }
    else
    {
        printf("Element found at %d location\n", result + 1);
    }

    return 0;
}
