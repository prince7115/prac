
#include <stdio.h>
#include <stdlib.h>

void SSTF(int arr[], int n, int head)
{
    int visited[100] = {0};
    int total = 0, current = head;

    printf("\nSSTF Seek Sequence: %d", head);

    for (int i = 0; i < n; i++)
    {
        int min = 9999, index = -1;

        // Find the nearest unvisited request
        for (int j = 0; j < n; j++)
        {
            if (!visited[j])
            {
                int diff = abs(current - arr[j]);

                if (diff < min)
                {
                    min = diff;
                    index = j;
                }
            }
        }

        visited[index] = 1;
        total += abs(current - arr[index]);
        current = arr[index];

        printf(" -> %d", current);
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void SCAN(int arr[], int n, int head, int diskSize)
{
    int a[100], total = 0;
    int current = head;

    // Copy requests into another array
    for (int i = 0; i < n; i++)
        a[i] = arr[i];

    // Sort requests in ascending order
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nSCAN Seek Sequence: %d", head);

    // Move towards higher cylinders (away from spindle)
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= head)
        {
            total += abs(current - a[i]);
            current = a[i];
            printf(" -> %d", current);
        }
    }

    // Move to the last cylinder
    if (current != diskSize - 1)
    {
        total += abs(current - (diskSize - 1));
        current = diskSize - 1;
        printf(" -> %d", current);
    }

    // Reverse direction and service remaining requests
    for (int i = n - 1; i >= 0; i--)
    {
        if (a[i] < head)
        {
            total += abs(current - a[i]);
            current = a[i];
            printf(" -> %d", current);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

void CLOOK(int arr[], int n, int head)
{
    int a[100], total = 0;
    int current = head;

    // Copy requests
    for (int i = 0; i < n; i++)
        a[i] = arr[i];

    // Sort in ascending order
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = 0; j < n - i - 1; j++)
        {
            if (a[j] > a[j + 1])
            {
                int temp = a[j];
                a[j] = a[j + 1];
                a[j + 1] = temp;
            }
        }
    }

    printf("\nC-LOOK Seek Sequence: %d", head);

    // First service requests towards higher cylinders
    for (int i = 0; i < n; i++)
    {
        if (a[i] >= head)
        {
            total += abs(current - a[i]);
            current = a[i];
            printf(" -> %d", current);
        }
    }

    // Jump to the lowest request
    for (int i = 0; i < n; i++)
    {
        if (a[i] < head)
        {
            total += abs(current - a[i]);
            current = a[i];
            printf(" -> %d", current);
        }
    }

    printf("\nTotal Head Movement = %d\n", total);
}

int main()
{
    int n, head, diskSize;
    int arr[100];

    printf("Enter number of requests: ");
    scanf("%d", &n);

    printf("Enter request queue:\n");
    for (int i = 0; i < n; i++)
        scanf("%d", &arr[i]);

    printf("Enter initial head position: ");
    scanf("%d", &head);

    printf("Enter disk size: ");
    scanf("%d", &diskSize);

    SSTF(arr, n, head);
    SCAN(arr, n, head, diskSize);
    CLOOK(arr, n, head);

    return 0;
}



























/*
==========================================================
       ASSIGNMENT 8: DISK SCHEDULING ALGORITHMS
==========================================================

AIM:
To implement SSTF, SCAN and C-LOOK disk scheduling
algorithms in C and calculate the total head movement.

----------------------------------------------------------
1. WHAT IS DISK SCHEDULING?
----------------------------------------------------------

Disk scheduling is an operating system technique used
to decide the order in which disk I/O requests are served.

Multiple processes may request data from different
locations on a disk.

The disk scheduling algorithm decides the order in
which the disk head visits these locations.

The main objective is to reduce disk head movement
and improve performance.

----------------------------------------------------------
2. IMPORTANT TERMINOLOGY
----------------------------------------------------------

1. Disk Head:
   The component that reads and writes data on a disk.

2. Request Queue:
   Contains the cylinder numbers requested by processes.

3. Head Position:
   The current position of the disk head.

4. Seek Time:
   The time required for the disk head to move to
   the required cylinder.

5. Head Movement:
   The distance travelled by the disk head between
   two cylinder positions.

6. Total Head Movement:
   The sum of all movements made by the disk head.

----------------------------------------------------------
3. HEADER FILES
----------------------------------------------------------

#include <stdio.h>

Provides printf() and scanf() for input and output.

#include <stdlib.h>

Provides abs() to calculate the absolute difference
between two cylinder positions.

----------------------------------------------------------
4. SSTF: SHORTEST SEEK TIME FIRST
----------------------------------------------------------

SSTF selects the request that is closest to the
current disk head position.

It minimizes the immediate movement of the head.

FUNCTION:

void SSTF(int arr[], int n, int head)

arr[]  = Request queue.
n      = Number of requests.
head   = Initial head position.

----------------------------------------------------------
5. SSTF VARIABLES
----------------------------------------------------------

int visited[100] = {0};

Tracks which requests have already been serviced.

0 = Not visited.
1 = Visited.

int total = 0, current = head;

total stores the total head movement.

current stores the current disk head position.

----------------------------------------------------------
6. SSTF WORKING
----------------------------------------------------------

The program starts from the initial head position.

It repeats the following steps:

1. Set minimum distance to a large value.
2. Set index to -1.
3. Check all unvisited requests.
4. Calculate distance using:

   abs(current - arr[j])

5. Find the request with the smallest distance.
6. Mark that request as visited.
7. Add the distance to total movement.
8. Update the current head position.
9. Repeat until all requests are serviced.

The program displays the seek sequence and
total head movement.

----------------------------------------------------------
7. SCAN: ELEVATOR ALGORITHM
----------------------------------------------------------

SCAN is also known as the Elevator Algorithm.

The disk head moves in one direction and services
all requests along its path.

It continues towards the end of the disk.

After reaching the end, it reverses direction
and services the remaining requests.

FUNCTION:

void SCAN(int arr[], int n, int head, int diskSize)

diskSize represents the total number of cylinders.

Valid cylinder numbers range from:

0 to diskSize - 1

----------------------------------------------------------
8. SCAN VARIABLES
----------------------------------------------------------

int a[100], total = 0;

a[] stores a copy of the request queue.

total stores the total head movement.

int current = head;

Stores the current head position.

----------------------------------------------------------
9. SORTING REQUESTS
----------------------------------------------------------

The program copies the original request queue
into another array.

It then sorts the copied array in ascending order
using Bubble Sort.

Bubble Sort compares adjacent elements and swaps
them when they are in the wrong order.

The sorted array makes it easier to service
requests in the required direction.

----------------------------------------------------------
10. SCAN WORKING
----------------------------------------------------------

STEP 1:
Start from the initial head position.

STEP 2:
Move towards higher cylinder numbers.

STEP 3:
Service all requests greater than or equal
to the initial head position.

STEP 4:
Calculate the movement for every request.

STEP 5:
Move the head to the last cylinder:

diskSize - 1

STEP 6:
Reverse direction.

STEP 7:
Service all remaining requests that are
smaller than the initial head position.

STEP 8:
Display the total head movement.

IMPORTANT:
This implementation always moves towards the
higher cylinder numbers first.

It also counts movement to the last cylinder
even when there is no request there.

----------------------------------------------------------
11. C-LOOK: CIRCULAR LOOK
----------------------------------------------------------

C-LOOK is a circular disk scheduling algorithm.

The head moves in one direction and services
requests in ascending order.

After servicing the highest request, it jumps
to the lowest pending request and continues.

Unlike SCAN, C-LOOK does not travel to the physical
end of the disk unless a request is present there.

FUNCTION:

void CLOOK(int arr[], int n, int head)

----------------------------------------------------------
12. C-LOOK WORKING
----------------------------------------------------------

STEP 1:
Copy the original request queue into another array.

STEP 2:
Sort the copied array using Bubble Sort.

STEP 3:
Start from the initial head position.

STEP 4:
Service all requests greater than or equal
to the initial head position.

STEP 5:
Move to the lowest remaining request.

STEP 6:
Continue servicing requests in ascending order.

STEP 7:
Calculate and display total head movement.

IMPORTANT:
This implementation counts the circular jump
from the highest serviced request to the lowest
remaining request as head movement.

----------------------------------------------------------
13. MAIN FUNCTION
----------------------------------------------------------

int main()

The main function controls the complete program.

It declares:

int n, head, diskSize;
int arr[100];

n        = Number of requests.
head     = Initial disk head position.
diskSize = Total number of cylinders.
arr[]    = Request queue.

----------------------------------------------------------
14. ACCEPTING INPUT
----------------------------------------------------------

The program accepts:

1. Number of requests.
2. Request queue.
3. Initial head position.
4. Disk size.

scanf() is used to accept all values.

----------------------------------------------------------
15. FUNCTION CALLS
----------------------------------------------------------

SSTF(arr, n, head);

Executes the SSTF algorithm.

SCAN(arr, n, head, diskSize);

Executes the SCAN algorithm.

CLOOK(arr, n, head);

Executes the C-LOOK algorithm.

All three algorithms use the same original
request queue.

----------------------------------------------------------
16. COMPARISON OF ALGORITHMS
----------------------------------------------------------

SSTF:
Selects the closest request to the current head.

SCAN:
Moves towards one end of the disk, then reverses.

C-LOOK:
Services requests in one direction and jumps
to the lowest pending request.

----------------------------------------------------------
17. CONCLUSION
----------------------------------------------------------

Thus, three disk scheduling algorithms were
implemented in C.

The program calculates and displays the seek
sequence and total head movement for SSTF,
SCAN and C-LOOK.

==========================================================
*/
