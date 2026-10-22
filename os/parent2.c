#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

void merge(int arr[], int l, int m, int r)
{
    int i, j, k;

    int n1 = m - l + 1;
    int n2 = r - m;

    int L[n1], R[n2];

    for (i = 0; i < n1; i++)
        L[i] = arr[l + i];

    for (j = 0; j < n2; j++)
        R[j] = arr[m + 1 + j];

    i = 0;
    j = 0;
    k = l;

    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2)
    {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void merge_sort(int arr[], int l, int r)
{
    if (l < r)
    {
        int m = (l + r) / 2;

        merge_sort(arr, l, m);
        merge_sort(arr, m + 1, r);

        merge(arr, l, m, r);
    }
}

int main()
{
    int arr[20];
    int size;
    int i;

    printf("==== Merge Sort by Parent Process ====\n");

    printf("Enter number of elements: ");
    scanf("%d", &size);

    printf("Enter %d integers:\n", size);

    for (i = 0; i < size; i++)
    {
        scanf("%d", &arr[i]);
    }

    merge_sort(arr, 0, size - 1);

    printf("\nSorted Array by Parent:\n");

    for (i = 0; i < size; i++)
    {
        printf("%d\t", arr[i]);
    }

    printf("\n");

    char *args[22];

    args[0] = "./childprocess";

    for (i = 0; i < size; i++)
    {
        args[i + 1] = malloc(10 * sizeof(char));
        sprintf(args[i + 1], "%d", arr[i]);
    }

    args[size + 1] = NULL;

    pid_t pid = fork();

    if (pid < 0)
    {
        printf("Fork failed\n");
        return 1;
    }

    if (pid == 0)
    {
        printf("\nChild Process Created\n");

        execv("./childprocess", args);

        perror("execv failed");
        exit(1);
    }
    else
    {
        printf("Parent waiting for child...\n");

        wait(NULL);

        printf("Child process completed.\n");
    }

    for (i = 1; i <= size; i++)
    {
        free(args[i]);
    }

    return 0;
}