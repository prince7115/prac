
#include <stdio.h>

int main()
{
    int n, m;

    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Arrays based on n and m
    int allocation[n][m];
    int maxNeed[n][m];
    int need[n][m];

    int available[m];
    int work[m];
    int finish[n];
    int safeSequence[n];

    // Initialize finish array
    for(int i = 0; i < n; i++)
    {
        finish[i] = 0;
    }

    // Input Allocation Matrix
    printf("\nEnter Allocation Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &allocation[i][j]);
        }
    }

    // Input Maximum Matrix
    printf("\nEnter Maximum Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            scanf("%d", &maxNeed[i][j]);
        }
    }

    // Calculate Need Matrix
    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            need[i][j] = maxNeed[i][j] - allocation[i][j];

            if(need[i][j] < 0)
            {
                printf("Invalid input!");
                return 0;
            }
        }
    }

    // Input Available Resources
    printf("\nEnter Available Resources:\n");

    for(int j = 0; j < m; j++)
    {
        scanf("%d", &available[j]);
        work[j] = available[j];
    }

    int count = 0;

    // Find Safe Sequence
    while(count < n)
    {
        int found = 0;

        for(int i = 0; i < n; i++)
        {
            if(finish[i] == 0)
            {
                int possible = 1;

                for(int j = 0; j < m; j++)
                {
                    if(need[i][j] > work[j])
                    {
                        possible = 0;
                        break;
                    }
                }

                if(possible)
                {
                    // Release allocated resources
                    for(int j = 0; j < m; j++)
                    {
                        work[j] += allocation[i][j];
                    }

                    safeSequence[count] = i;
                    finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }

        if(found == 0)
        {
            break;
        }
    }

    // Display Need Matrix
    printf("\nNeed Matrix:\n");

    for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m; j++)
        {
            printf("%d ", need[i][j]);
        }

        printf("\n");
    }

    // Check Safe State
    if(count == n)
    {
        printf("\nSystem is in SAFE state.\n");

        printf("Safe Sequence: ");

        for(int i = 0; i < n; i++)
        {
            printf("P%d", safeSequence[i]);

            if(i != n - 1)
                printf(" -> ");
        }

        printf("\n");
    }
    else
    {
        printf("\nSystem is NOT in a safe state.\n");
    }

    return 0;
}



// 5
// 3
// 0 1 0
// 2 0 0
// 3 0 2
// 2 1 1
// 0 0 2
// 7 5 3
// 3 2 2
// 9 0 2
// 2 2 2
// 4 3 3
// 3 3 2
















/*
==========================================================
        ASSIGNMENT 5: BANKER'S ALGORITHM
==========================================================

AIM:
To implement Banker's Algorithm in C to check whether
the system is in a safe state and find a safe sequence
of processes.

----------------------------------------------------------
1. WHAT IS BANKER'S ALGORITHM?
----------------------------------------------------------

Banker's Algorithm is a deadlock avoidance algorithm
used in operating systems.

It checks whether allocating resources to processes
will keep the system in a safe state.

Before allowing a process to execute, the algorithm
checks whether sufficient resources are available
to satisfy its remaining requirements.

If all processes can finish in some order, the system
is in a SAFE STATE.

If no such order exists, the system is NOT in a safe
state.

----------------------------------------------------------
2. IMPORTANT TERMS
----------------------------------------------------------

1. Process:
   A program currently being executed.

2. Resource:
   A system component required by a process, such as
   memory, printers, or other devices.

3. Allocation Matrix:
   Represents the resources currently allocated to
   each process.

4. Maximum Matrix:
   Represents the maximum resources each process may
   require during execution.

5. Need Matrix:
   Represents the remaining resources required by
   each process.

   Formula:
   Need = Maximum - Allocation

6. Available:
   Represents the number of currently available
   instances of each resource type.

7. Work:
   A temporary array used to track the resources
   currently available during the safety algorithm.

8. Finish:
   An array that indicates whether a process has
   completed successfully in the safety check.

9. Safe Sequence:
   An order in which all processes can execute and
   release their allocated resources without causing
   deadlock.

----------------------------------------------------------
3. HEADER FILE
----------------------------------------------------------

#include <stdio.h>

Used for input and output operations such as
printf() and scanf().

----------------------------------------------------------
4. INPUT: NUMBER OF PROCESSES AND RESOURCES
----------------------------------------------------------

int n, m;

n represents the number of processes.
m represents the number of resource types.

The user enters these values using scanf().

----------------------------------------------------------
5. DECLARING ARRAYS
----------------------------------------------------------

int allocation[n][m];
int maxNeed[n][m];
int need[n][m];

int available[m];
int work[m];
int finish[n];
int safeSequence[n];

These arrays are declared according to the number
of processes and resource types entered by the user.

ALLOCATION:
Stores the resources currently allocated to each
process.

MAXNEED:
Stores the maximum resource requirements of each
process.

NEED:
Stores the remaining resources required by each
process.

AVAILABLE:
Stores the currently available resources.

WORK:
A temporary copy of Available, updated during
the safety algorithm.

FINISH:
Indicates whether a process has completed.

SAFESEQUENCE:
Stores the order in which processes can safely
complete.

----------------------------------------------------------
6. INITIALIZING FINISH ARRAY
----------------------------------------------------------

for(int i = 0; i < n; i++)
{
    finish[i] = 0;
}

Initially, no process has completed.

0 means the process is unfinished.
1 means the process has completed in the safety check.

----------------------------------------------------------
7. INPUT ALLOCATION MATRIX
----------------------------------------------------------

The program accepts the Allocation Matrix using
nested loops.

The outer loop represents processes.
The inner loop represents resource types.

For example, allocation[1][2] represents the
number of instances of resource type 2 allocated
to process P1 (using zero-based indexing).

----------------------------------------------------------
8. INPUT MAXIMUM MATRIX
----------------------------------------------------------

The program accepts the Maximum Matrix using
nested loops.

It represents the maximum number of instances
of each resource type that a process may require.

----------------------------------------------------------
9. CALCULATING NEED MATRIX
----------------------------------------------------------

Formula:

Need[i][j] = MaxNeed[i][j] - Allocation[i][j]

The program calculates the remaining resource
requirement of every process.

If Need becomes negative, the input is invalid
because the allocated resources cannot exceed
the declared maximum requirement.

----------------------------------------------------------
10. INPUT AVAILABLE RESOURCES
----------------------------------------------------------

The user enters the currently available instances
of each resource type.

The program also copies Available into Work.

work[j] = available[j];

Work is used to simulate resource availability
as processes complete.

----------------------------------------------------------
11. FINDING THE SAFE SEQUENCE
----------------------------------------------------------

The algorithm uses a while loop:

while(count < n)

count represents the number of processes that
have successfully completed in the safety check.

The algorithm searches for an unfinished process
whose remaining resource requirements can be
satisfied using the currently available Work array.

----------------------------------------------------------
12. CHECKING PROCESS REQUIREMENTS
----------------------------------------------------------

if(finish[i] == 0)

Checks whether the process has not already
completed.

The variable possible is initially set to 1.

The program checks every resource type:

if(need[i][j] > work[j])

If the required resources exceed the currently
available resources, the process cannot execute.

In that case:

possible = 0;

The loop stops checking that process.

If all resource requirements can be satisfied,
possible remains 1.

----------------------------------------------------------
13. RELEASING ALLOCATED RESOURCES
----------------------------------------------------------

If a process can complete, its allocated resources
are returned to the system.

work[j] += allocation[i][j];

This simulates the process finishing its execution
and releasing all the resources it was holding.

The process is then added to the safe sequence.

safeSequence[count] = i;

Its Finish value becomes 1.

finish[i] = 1;

The completed process count is increased.

count++;

----------------------------------------------------------
14. CHECKING WHETHER A PROCESS WAS FOUND
----------------------------------------------------------

The variable found indicates whether at least
one process could complete during the current
iteration.

If no process can complete:

if(found == 0)
{
    break;
}

The loop terminates because the algorithm cannot
find another process that can safely finish using
the currently available resources.

----------------------------------------------------------
15. DISPLAYING NEED MATRIX
----------------------------------------------------------

The program displays the calculated Need Matrix.

This helps the user understand the remaining
resource requirements of every process.

----------------------------------------------------------
16. CHECKING SAFE OR UNSAFE STATE
----------------------------------------------------------

if(count == n)

If all processes have completed successfully
in the safety check, the system is in a SAFE state.

The program displays the safe sequence.

Otherwise, the system is NOT in a safe state.

IMPORTANT:
An unsafe state does not necessarily mean that
deadlock has already occurred. It means the
algorithm cannot guarantee a safe completion
sequence with the given resource information.

----------------------------------------------------------
17. EXAMPLE INPUT
----------------------------------------------------------

Number of processes: 5
Number of resources: 3

Allocation Matrix:
0 1 0
2 0 0
3 0 2
2 1 1
0 0 2

Maximum Matrix:
7 5 3
3 2 2
9 0 2
2 2 2
4 3 3

Available Resources:
3 3 2

Calculated Need Matrix:

7 4 3
1 2 2
6 0 0
0 1 1
4 3 1

One possible safe sequence:

P1 -> P3 -> P4 -> P0 -> P2

Therefore, the system is in a SAFE state.

----------------------------------------------------------
18. CONCLUSION
----------------------------------------------------------

Thus, Banker's Algorithm was successfully
implemented in C.

The program accepts Allocation, Maximum and
Available resource information, calculates the
Need Matrix, checks whether processes can complete,
and displays the safe sequence if one exists.

==========================================================
*/
